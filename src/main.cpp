#include <Arduino.h>
#include <OneButton.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <stdlib.h>
#include <string.h>

#include <cmath>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "../include/cyber24.h"
#include "../include/cyber28.h"
#include "../include/rm67162.h"
#include "../include/stations.h"
#include "../include/welcome.h"
#include "../include/xie14.h"
#include "../include/xie20.h"
#include "../include/xie24.h"
#include "../include/xie28.h"

using namespace std;

#define min(x, y) (x > y ? y : x)
#define max(x, y) (x < y ? y : x)
#define LINE_NUM 19          // 线路总数
#define METRO_STATION_NUM 12 // 每页站点总数
#define RIGHT_BUTTON 21      // 右键
#define LEFT_BUTTON 0        // 左键
#define CYBER_YELLOW 0xFF69
#define CYBER_BLUE 0x6F7F
/* UI清单 */
enum UI {
    WELCOME,             // 欢迎
    SEARCH_START,        // 搜索起点
    SEARCH_START_SELECT, // 选择起点
    SEARCH_END,          // 搜索终点
    SEARCH_END_SELECT,   // 选择终点
    SHOW_METRO_LINES,    // 显示所有站点
    LINE_RESULT,         // 路线结果
    USER_GUIDE,          // 使用说明
};

/* 站点节点 */
struct station_node {
    int dest;   // 目的地
    int weight; // 权重
    struct station_node *next;
};

/* 邻接列表 */
struct station_node_list {
    struct station_node *head;
};

OneButton button_right(RIGHT_BUTTON, true);
OneButton button_left(LEFT_BUTTON, true);

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite metro_spr = TFT_eSprite(&tft);
TFT_eSprite welcome_spr = TFT_eSprite(&tft);
TFT_eSprite result_spr = TFT_eSprite(&tft);
TFT_eSprite search_start_spr = TFT_eSprite(&tft);
TFT_eSprite search_end_spr = TFT_eSprite(&tft);
TFT_eSprite user_guide_spr = TFT_eSprite(&tft);

uint8_t cur_ui = WELCOME;                           // 当前UI
uint8_t pre_ui = WELCOME;                           // 上一个UI
int8_t welcome_cur_select = 0;                      // 欢迎页选择的序号
std::map<string, vector<int>> transitions;          // 换乘站点，站点名:线路列表，如，徐家汇:1,9,11
int16_t cur_line = 0;                               // Metro页当前线路
int16_t cur_station_idx = 0;                        // Metro页当前站点序号
int16_t start_station = -1;                         // 起点站序号
int16_t end_station = -1;                           // 终点站序号
int16_t node_cnt = 0;                               // 起点 or 站点
struct station_node_list station_list[SH_STATIONS]; // 邻接列表
vector<int> path_result;                            // 检索的路径结果
int32_t result_start_y = 0;                         // 结果页的起始纵坐标，单位40
int16_t cur_alpha_idx = 0;
char start_str[45] = {'\0'};
char end_str[45] = {'\0'};
int16_t cur_start_station_idx = 0;
int16_t cur_end_station_idx = 0;
int16_t cur_start_select = 0;
int16_t cur_end_select = 0;
vector<int> start_ret;
vector<int> end_ret;

std::set<int> dark_lines = {0, 3, 4, 5, 6, 7, 10, 11, 13, 16, 18}; // 暗色地铁线路列表
const char alpha[][2] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
                         "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"}; // 字母输入条

// 删除路径中的重复的开头和结尾
vector<int> delete_path_head_tail(vector<int> path) {
    vector<int> ret;
    if (path.size() >= 2 && strcmp(stations[path[0]], stations[path[1]]) != 0) {
        ret.push_back(path[0]);
    }

    for (int i = 1; i < path.size() - 1; i++) {
        ret.push_back(path[i]);
    }

    if (path.size() >= 2 && strcmp(stations[path[path.size() - 2]], stations[path[path.size() - 1]]) != 0) {
        ret.push_back(path[path.size() - 1]);
    }
    return ret;
}

// 从站点编号获取线路
int16_t get_line_idx(int16_t station) {
    for (int i = 0; i < LINE_NUM; i++) {
        if (line_station_start[i] > station) {
            return i - 1;
        }
    }

    return LINE_NUM - 1;
}

// 初始化所有换乘站点map映射
void get_transition_stations() {
    for (int i = 0; i < SH_STATIONS; i++) {
        if (transitions.find(stations[i]) == transitions.end()) {
            vector<int> tmp;
            tmp.push_back(get_line_idx(i));
            transitions[string(stations[i])] = tmp;
        } else {
            transitions[string(stations[i])].push_back(get_line_idx(i));
        }
    }
}

// 获取站点的换乘路线
vector<int> get_transition_lines(int16_t station) {
    vector<int> ret;
    if (transitions[stations[station]].size() > 1) {
        for (int i = 0; i < transitions[stations[station]].size(); i++) {
            if (transitions[stations[station]][i] != get_line_idx(station)) {
                ret.push_back(transitions[stations[station]][i]);
            }
        }
    }

    return ret;
}

int min_distance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < SH_STATIONS; v++) {
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// 获取路径
void get_path(int parent[], int j, vector<int> &path) {
    if (parent[j] == -1) {
        path.push_back(j);
        return;
    }
    get_path(parent, parent[j], path);
    path.push_back(j);
}

// Dijkstra算法搜索路径
void dijkstra(struct station_node_list *station_list, int src, int dest) {
    int dist[SH_STATIONS];
    bool sptSet[SH_STATIONS];
    int parent[SH_STATIONS];

    for (int i = 0; i < SH_STATIONS; i++) {
        parent[src] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < SH_STATIONS - 1; count++) {
        int u = min_distance(dist, sptSet);
        sptSet[u] = true;

        struct station_node *neighbor = station_list[u].head;
        while (neighbor != NULL) {
            int v = neighbor->dest;
            int weight = neighbor->weight;
            if (!sptSet[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + weight;
            }
            neighbor = neighbor->next;
        }
    }

    if (dist[dest] == INT_MAX) {
        Serial.printf("No path from %d to %d\n", src, dest);
    } else {
        // 处理路线结果
        vector<int> path;
        get_path(parent, dest, path);
        path_result = delete_path_head_tail(path);
    }
}

// 在邻接列表中加入边
void add_edge(struct station_node_list *station_list, int src, int dest, int weight) {
    struct station_node *new_node = (struct station_node *)malloc(sizeof(struct station_node));
    new_node->dest = dest;
    new_node->weight = weight;
    new_node->next = station_list[src].head;
    station_list[src].head = new_node;

    new_node = (struct station_node *)malloc(sizeof(struct station_node));
    new_node->dest = src;
    new_node->weight = weight;
    new_node->next = station_list[dest].head;
    station_list[dest].head = new_node;
}

// 初始化每个邻接列表
void init_lists() {
    for (int i = 0; i < SH_STATIONS; i++) {
        station_list[i].head = NULL;
    }

    for (int i = 0; i < 626; i++) {
        add_edge(station_list, edges[i][0], edges[i][1], edges[i][2]);
    }
}

// 进入欢迎页
void draw_welcome_page() {
    welcome_spr.createSprite(240, 536);
    welcome_spr.setSwapBytes(true);
    welcome_spr.loadFont(cyber28);
    welcome_spr.pushImage(0, 0, 240, 536, welcome_page[welcome_cur_select]);

    lcd_PushColors(0, 0, 240, 536, (uint16_t *)welcome_spr.getPointer());
}

// 进入地铁线路页
void draw_metro_line_page() {
    button_left.setLongPressIntervalMs(150);
    button_right.setLongPressIntervalMs(150);

    metro_spr.createSprite(240, 536);
    metro_spr.setSwapBytes(true);
    metro_spr.fillSprite(CYBER_YELLOW);
    metro_spr.pushImage(35, 10, 21, 30, ditieicon);

    /* 画线路 */
    metro_spr.fillRect(40, 60, 8, 40 * (min(line_station_nums[cur_line], METRO_STATION_NUM) - 1),
                       line_colors[cur_line]);

    uint16_t start_idx = line_station_start[cur_line] +
                         (cur_station_idx < METRO_STATION_NUM ? 0 : (cur_station_idx - (METRO_STATION_NUM - 1)));
    for (int j = 0; j < min(METRO_STATION_NUM, line_station_nums[cur_line]); j++) {
        metro_spr.loadFont(xie20);
        metro_spr.setTextColor(TFT_BLACK, CYBER_YELLOW);
        metro_spr.drawString(line_names[cur_line], 60, 17);
        metro_spr.drawString(stations[j + start_idx], 60, 50 + j * 40);
        metro_spr.fillCircle(44, 60 + j * 40, 10, line_colors[cur_line]);
        metro_spr.fillCircle(44, 60 + j * 40, 4, CYBER_YELLOW);

        // 画换乘线路
        vector<int> trans = get_transition_lines(j + start_idx);
        for (int i = 0; i < trans.size(); i++) {
            metro_spr.fillSmoothRoundRect(60 + 56 * i, 70 + j * 40, 50, 16, 5, line_colors[trans[i]]);
            metro_spr.loadFont(xie14);
            metro_spr.setTextColor(dark_lines.find(trans[i]) != dark_lines.end() ? CYBER_YELLOW
                                                                                 : TFT_BLACK, // 深色线改变字体显示颜色
                                   line_colors[trans[i]]);
            metro_spr.drawCentreString(line_names[trans[i]], 85 + 56 * i, 72 + j * 40, 12);
        }
    }

    // 画左侧箭头
    uint16_t arrow_y = cur_station_idx >= METRO_STATION_NUM ? (METRO_STATION_NUM - 1) : cur_station_idx;
    metro_spr.fillTriangle(3, 52 + arrow_y * 40, 3, 68 + arrow_y * 40, 28, 60 + arrow_y * 40, TFT_BLACK);

    // 画右上角起点站
    if (start_station != -1) {
        metro_spr.loadFont(xie14);
        metro_spr.setTextColor(TFT_BLACK, CYBER_YELLOW);
        metro_spr.drawCentreString("起点", 175, 13, 14);
        metro_spr.drawCentreString(stations[start_station], 175, 27, 14);
    }

    lcd_PushColors(0, 0, 240, 536, (uint16_t *)metro_spr.getPointer());
}

// 判断目标中是否有不连续子串，首字母需一致
bool search_target(const char *src, char *target) {
    int idx = 0;
    int m = strlen(src), n = strlen(target);

    if (n == 0 || m == 0 || n > m || (m > 0 && n > 0 && src[0] != target[0])) {
        return false;
    }

    for (int i = 0; i < m; i++) {
        if (src[i] == target[idx]) {
            idx += 1;
        }
    }

    if (idx == n) {
        return true;
    }

    return false;
}

// 进入搜索起始站点
void draw_search_start() {
    button_left.setLongPressIntervalMs(300);
    button_right.setLongPressIntervalMs(300);

    search_start_spr.createSprite(240, 536);
    search_start_spr.setSwapBytes(true);
    search_start_spr.fillSprite(CYBER_YELLOW);
    search_start_spr.loadFont(xie28);
    search_start_spr.setTextColor(TFT_BLACK, CYBER_YELLOW);
    search_start_spr.drawCentreString("请输入起点：", 120, 20, 28);
    search_start_spr.fillRect(3, 78, 234, 39, TFT_BLACK);
    search_start_spr.fillRect(5, 80, 230, 35, CYBER_YELLOW);
    search_start_spr.fillTriangle(112, 150, 128, 150, 120, 120, TFT_BLACK);

    // 显示当前已输入字符
    if (strlen(start_str) > 0) {
        search_start_spr.drawCentreString(start_str, 120, 50, 28);
    }

    // 显示字母框
    int16_t front = cur_alpha_idx - 3, rear = cur_alpha_idx + 3;
    for (int16_t i = front; i <= rear; i++) {
        int16_t j = i - front, idx = i;

        if (idx < 0) {
            idx = idx + 26;
        } else {
            idx %= 26;
        }

        search_start_spr.drawCentreString(alpha[idx], 30 + 30 * j, 85, 28);
    }

    // 设置结果框和字体颜色，表示未起效
    search_start_spr.fillRect(3, 153, 234, 364, TFT_DARKGREY);
    search_start_spr.fillRect(5, 155, 230, 360, CYBER_YELLOW);
    search_start_spr.setTextColor(TFT_DARKGREY, CYBER_YELLOW);
    search_start_spr.loadFont(xie20);
    start_ret.clear();

    // 寻找满足条件的地铁站名，存入编号并显示
    if (strlen(start_str) > 0) {
        for (int i = 0; i < 407; i++) {
            if (search_target(station_pinyin[i][0], start_str)) {
                start_ret.push_back(i);
            }
        }

        for (int i = 0; i < min(12, start_ret.size()); i++) {
            search_start_spr.drawString(station_pinyin[start_ret[i]][1], 16, 160 + 30 * i);
        }
    }

    lcd_PushColors(0, 0, 240, 536, (uint16_t *)search_start_spr.getPointer());
}

// 进入起点站结果选择
void draw_search_start_select() {
    button_left.setLongPressIntervalMs(10);
    button_right.setLongPressIntervalMs(10);
    search_start_spr.fillRect(3, 153, 234, 364, TFT_BLACK);
    search_start_spr.fillRect(5, 155, 230, 360, CYBER_YELLOW);
    search_start_spr.setTextColor(TFT_BLACK, CYBER_YELLOW);

    int n = start_ret.size(), start_idx = 0;

    if (cur_start_select < 12) {
        start_idx = 0;
    } else {
        start_idx = cur_start_select - 11;
    }

    for (int i = start_idx; i < start_idx + min(12, start_ret.size()); i++) {
        // 选中色块为黑底白字
        search_start_spr.fillRect(5, 155 + 30 * (i - start_idx), 230, 30,
                                  i == cur_start_select ? CYBER_BLUE : CYBER_YELLOW);
        search_start_spr.setTextColor(TFT_BLACK, i == cur_start_select ? CYBER_BLUE : CYBER_YELLOW);
        search_start_spr.drawString(station_pinyin[start_ret[i]][1], 16, 160 + 30 * (i - start_idx));
    }

    lcd_PushColors(0, 0, 240, 536, (uint16_t *)search_start_spr.getPointer());
}

// 进入搜索终点站
void draw_search_end() {
    button_left.setLongPressIntervalMs(300);
    button_right.setLongPressIntervalMs(300);

    search_end_spr.createSprite(240, 536);
    search_end_spr.setSwapBytes(true);
    search_end_spr.fillSprite(CYBER_YELLOW);
    search_end_spr.loadFont(xie28);
    search_end_spr.setTextColor(TFT_BLACK, CYBER_YELLOW);
    search_end_spr.drawCentreString("请输入终点：", 120, 20, 28);
    search_end_spr.fillRect(3, 78, 234, 39, TFT_BLACK);
    search_end_spr.fillRect(5, 80, 230, 35, CYBER_YELLOW);
    search_end_spr.fillTriangle(112, 150, 128, 150, 120, 120, TFT_BLACK);

    // 显示当前已输入字符
    if (strlen(end_str) > 0) {
        search_end_spr.drawCentreString(end_str, 120, 50, 28);
    }

    // 显示字母框
    int16_t front = cur_alpha_idx - 3, rear = cur_alpha_idx + 3;
    for (int16_t i = front; i <= rear; i++) {
        int16_t j = i - front, idx = i;

        if (idx < 0) {
            idx = idx + 26;
        } else {
            idx %= 26;
        }

        search_end_spr.drawCentreString(alpha[idx], 30 + 30 * j, 85, 28);
    }

    // 设置结果框和字体颜色，表示未起效
    search_end_spr.fillRect(3, 153, 234, 364, TFT_DARKGREY);
    search_end_spr.fillRect(5, 155, 230, 360, CYBER_YELLOW);
    search_end_spr.setTextColor(TFT_DARKGREY, CYBER_YELLOW);
    search_end_spr.loadFont(xie20);
    end_ret.clear();

    // 寻找满足条件的地铁站名，存入编号并显示
    if (strlen(end_str) > 0) {
        for (int i = 0; i < 407; i++) {
            if (search_target(station_pinyin[i][0], end_str)) {
                end_ret.push_back(i);
            }
        }

        for (int i = 0; i < min(12, end_ret.size()); i++) {
            search_end_spr.drawString(station_pinyin[end_ret[i]][1], 16, 160 + 30 * i);
        }
    }

    lcd_PushColors(0, 0, 240, 536, (uint16_t *)search_end_spr.getPointer());
}

void draw_search_end_select() {
    button_left.setLongPressIntervalMs(10);
    button_right.setLongPressIntervalMs(10);
    search_end_spr.fillRect(3, 153, 234, 364, TFT_BLACK);
    search_end_spr.fillRect(5, 155, 230, 360, CYBER_YELLOW);
    search_end_spr.setTextColor(TFT_BLACK, CYBER_YELLOW);

    int n = end_ret.size(), start_idx = 0;

    if (cur_end_select < 12) {
        start_idx = 0;
    } else {
        start_idx = cur_end_select - 11;
    }

    for (int i = start_idx; i < start_idx + min(12, end_ret.size()); i++) {
        // 选中色块为黑底白字
        search_end_spr.fillRect(5, 155 + 30 * (i - start_idx), 230, 30,
                                i == cur_end_select ? CYBER_BLUE : CYBER_YELLOW);
        search_end_spr.setTextColor(TFT_BLACK, i == cur_end_select ? CYBER_BLUE : CYBER_YELLOW);
        search_end_spr.drawString(station_pinyin[end_ret[i]][1], 16, 160 + 30 * (i - start_idx));
    }

    lcd_PushColors(0, 0, 240, 536, (uint16_t *)search_end_spr.getPointer());
}

// 进入结果页
void draw_result_page() {
    button_left.setLongPressIntervalMs(10);
    button_right.setLongPressIntervalMs(10);

    int n = path_result.size();

    /* Limit rollbar start y address */
    if (n > 13 && (result_start_y < 13 - n)) {
        result_start_y = 13 - n;
    } else if (n <= 13 || result_start_y > 0) {
        result_start_y = 0;
    }

    result_spr.createSprite(240, 536);
    result_spr.setSwapBytes(true);
    result_spr.fillSprite(CYBER_YELLOW);
    result_spr.loadFont(xie20);
    result_spr.setTextColor(TFT_BLACK, CYBER_YELLOW);

    if (n >= 2) {
        uint16_t l_color, node, node_pre;

        for (int j = 0; j < n - 1; j++) {
            int y = 40 * (j + result_start_y);

            // 获取站点颜色和线路颜色，通过前后站是否一致判断，一致为同一条线，否则为换乘站
            if (get_line_idx(path_result[j]) == get_line_idx(path_result[j + 1])) {
                l_color = line_colors[get_line_idx(path_result[j])];
                result_spr.fillRect(40, 40 + y, 8, 40, l_color);
                node = l_color;
                node_pre = node;
            } else {
                node = node_pre;
            }

            // 换乘站的线路信息
            if (j == 0 || (j >= 1 && get_line_idx(path_result[j]) != get_line_idx(path_result[j - 1]))) {
                result_spr.fillSmoothRoundRect(60, 40 + y, 50, 16, 5, l_color);
                result_spr.loadFont(xie14);

                // 深色线改变字体显示颜色
                result_spr.setTextColor(
                    dark_lines.find(get_line_idx(path_result[j])) != dark_lines.end() ? CYBER_YELLOW : TFT_BLACK, l_color);
                result_spr.drawCentreString(line_names[get_line_idx(path_result[j])], 85, 42 + y, 12);
            }

            // 画前n-1个站点
            result_spr.loadFont(xie20);
            result_spr.setTextColor(TFT_BLACK, CYBER_YELLOW);
            result_spr.drawString(stations[path_result[j]], 60, 20 + y);
            result_spr.fillCircle(44, 30 + y, 10, node);
            result_spr.fillCircle(44, 30 + y, 4, CYBER_YELLOW);
        }

        // 画最后一个站点
        result_spr.loadFont(xie20);
        result_spr.setTextColor(TFT_BLACK, CYBER_YELLOW);
        result_spr.drawString(stations[path_result[n - 1]], 60, 20 + (n - 1 + result_start_y) * 40);
        result_spr.fillCircle(44, 30 + (n - 1 + result_start_y) * 40, 10, node);
        result_spr.fillCircle(44, 30 + (n - 1 + result_start_y) * 40, 4, CYBER_YELLOW);
    } else {
        // 进入error页
        result_spr.fillSprite(CYBER_YELLOW);
        result_spr.setTextColor(TFT_BLACK, CYBER_YELLOW);
        result_spr.drawString("没有找到路线！", 10, 218);
        result_spr.drawString("你设置了相同的起点和终", 10, 258);
        result_spr.drawString("点，双击左键以返回上一", 10, 288);
        result_spr.drawString("级重新设置站点。", 10, 318);
    }

    lcd_PushColors(0, 0, 240, 536, (uint16_t *)result_spr.getPointer());
}

// 进入用户指引
void draw_user_guide() {
    user_guide_spr.createSprite(240, 536);
    user_guide_spr.setSwapBytes(true);
    user_guide_spr.fillSprite(CYBER_YELLOW);
    user_guide_spr.loadFont(xie24);
    user_guide_spr.setTextColor(TFT_BLACK, CYBER_YELLOW);

    user_guide_spr.drawCentreString("欢迎来到夜之城", 120, 10, 24);
    user_guide_spr.drawWideLine(40, 40, 200, 40, 4, TFT_BLACK);

    const char guide[][34] = {
        "功能1:",
        "查看线路，双击选择起点",
        "再次双击选择终点。",
        "",
        "功能2:",
        "搜索站点，按首拼音缩写",
        "匹配，双击进入站点选择",
        "完成后显示结果。",
        "",
        "按键说明:",
        "右键单击: 右翻页/输入",
        "右键双击: 确定/下一级",
        "右键长按: 向右/下滑动",
        "左键单击: 左翻页/删除",
        "左键双击: 返回上一级",
        "左键长按: 向上/左滑动",
    };

    for (int i = 0; i < 16; i++) {
        if ((i == 0) || (i == 4) || (i == 9)) {
            user_guide_spr.loadFont(xie24);
        } else {
            user_guide_spr.loadFont(xie20);
        }
        user_guide_spr.drawString(guide[i], 10, 50 + 30 * i);
    }
    lcd_PushColors(0, 0, 240, 536, (uint16_t *)user_guide_spr.getPointer());
}

// 绘制ui界面
void draw_ui() {
    switch (cur_ui) {
    case WELCOME:
        draw_welcome_page();
        break;
    case SEARCH_START:
        draw_search_start();
        break;
    case SEARCH_START_SELECT:
        draw_search_start_select();
        break;
    case SEARCH_END:
        draw_search_end();
        break;
    case SEARCH_END_SELECT:
        draw_search_end_select();
        break;
    case LINE_RESULT:
        draw_result_page();
        break;
    case SHOW_METRO_LINES:
        draw_metro_line_page();
        break;
    case USER_GUIDE:
        draw_user_guide();
        break;
    default:
        break;
    }
}

// 右键单击
void right_click() {
    if (cur_ui == WELCOME) {
        welcome_cur_select += 1;
        welcome_cur_select %= 3;
    } else if (cur_ui == SHOW_METRO_LINES) {
        cur_station_idx = 0;
        cur_line += 1;
        cur_line %= LINE_NUM;
    } else if (cur_ui == SEARCH_START) {
        start_str[cur_start_station_idx] = alpha[cur_alpha_idx][0];
        cur_start_station_idx += 1;
    } else if (cur_ui == SEARCH_START_SELECT) {
        cur_start_select += 1;
        if (cur_start_select == start_ret.size()) {
            cur_start_select = start_ret.size() - 1;
        }
    } else if (cur_ui == SEARCH_END) {
        end_str[cur_end_station_idx] = alpha[cur_alpha_idx][0];
        cur_end_station_idx += 1;
    } else if (cur_ui == SEARCH_END_SELECT) {
        cur_end_select += 1;
        if (cur_end_select == end_ret.size()) {
            cur_end_select = end_ret.size() - 1;
        }
    }
    draw_ui();
}

void right_doubleclick() {
    if (cur_ui == WELCOME) {
        if (welcome_cur_select == 0) {
            cur_ui = USER_GUIDE;
        } else if (welcome_cur_select == 1) {
            cur_ui = SEARCH_START;
        } else if (welcome_cur_select == 2) {
            cur_ui = SHOW_METRO_LINES;
        }
    } else if (cur_ui == SHOW_METRO_LINES) {
        if (node_cnt == 0) {
            start_station = cur_station_idx + line_station_start[cur_line];
            node_cnt += 1;
        } else {
            end_station = cur_station_idx + line_station_start[cur_line];
            node_cnt = 0;

            dijkstra(station_list, start_station, end_station);

            start_station = -1;
            end_station = -1;
            result_start_y = 0;

            cur_ui = LINE_RESULT;
            pre_ui = SHOW_METRO_LINES;
        }
    } else if (cur_ui == SEARCH_START) {
        cur_ui = SEARCH_START_SELECT;
        cur_start_select = 0;
    } else if (cur_ui == SEARCH_START_SELECT) {
        if (start_ret.size() > 0) {
            for (int i = 0; i < SH_STATIONS; i++) {
                if (strcmp(stations[i], station_pinyin[start_ret[cur_start_select]][1]) == 0) {
                    start_station = i;
                    break;
                }
            }
            cur_ui = SEARCH_END;
        }
    } else if (cur_ui == SEARCH_END) {
        cur_ui = SEARCH_END_SELECT;
        cur_end_select = 0;
    } else if (cur_ui == SEARCH_END_SELECT) {
        if (end_ret.size() > 0) {
            for (int i = 0; i < SH_STATIONS; i++) {
                if (strcmp(stations[i], station_pinyin[end_ret[cur_end_select]][1]) == 0) {
                    end_station = i;
                    break;
                }
            }

            dijkstra(station_list, start_station, end_station);

            start_station = -1;
            end_station = -1;
            result_start_y = 0;

            cur_ui = LINE_RESULT;
            pre_ui = SEARCH_END_SELECT;
        }
    }
    draw_ui();
}

void RightDuringLongPress() {
    if (cur_ui == SHOW_METRO_LINES) {
        cur_station_idx += 1;
        if (cur_station_idx == line_station_nums[cur_line]) {
            cur_station_idx = line_station_nums[cur_line] - 1;
        }
    } else if (cur_ui == LINE_RESULT) {
        result_start_y -= 1;
    } else if (cur_ui == SEARCH_START) {
        cur_alpha_idx += 1;
        cur_alpha_idx %= 26;
    } else if (cur_ui == SEARCH_START_SELECT) {
        cur_start_select += 1;
        if (cur_start_select == start_ret.size()) {
            cur_start_select = start_ret.size() - 1;
        }
    } else if (cur_ui == SEARCH_END) {
        cur_alpha_idx += 1;
        cur_alpha_idx %= 26;
    } else if (cur_ui == SEARCH_END_SELECT) {
        cur_end_select += 1;
        if (cur_end_select == end_ret.size()) {
            cur_end_select = end_ret.size() - 1;
        }
    }
    draw_ui();
}

void left_click() {
    if (cur_ui == WELCOME) {
        welcome_cur_select -= 1;
        if (welcome_cur_select < 0) {
            welcome_cur_select += 3;
        }
    } else if (cur_ui == SHOW_METRO_LINES) {
        cur_station_idx = 0;
        cur_line -= 1;
        if (cur_line < 0) {
            cur_line += LINE_NUM;
        }
    } else if (cur_ui == SEARCH_START) {
        cur_start_station_idx -= 1;
        cur_start_station_idx = max(cur_start_station_idx, 0);
        start_str[cur_start_station_idx] = '\0';
    } else if (cur_ui == SEARCH_START_SELECT) {
        cur_start_select -= 1;
        if (cur_start_select <= 0) {
            cur_start_select = 0;
        }
    } else if (cur_ui == SEARCH_END) {
        cur_end_station_idx -= 1;
        cur_end_station_idx = max(cur_end_station_idx, 0);
        end_str[cur_end_station_idx] = '\0';
    } else if (cur_ui == SEARCH_END_SELECT) {
        cur_end_select -= 1;
        if (cur_end_select <= 0) {
            cur_end_select = 0;
        }
    }
    draw_ui();
}

void LeftDuringLongPress() {
    if (cur_ui == SHOW_METRO_LINES) {
        cur_station_idx -= 1;
        if (cur_station_idx < 0) {
            cur_station_idx = 0;
        }
    } else if (cur_ui == LINE_RESULT) {
        result_start_y += 1;
    } else if (cur_ui == SEARCH_START) {
        cur_alpha_idx -= 1;
        if (cur_alpha_idx < 0) {
            cur_alpha_idx += 26;
        }
    } else if (cur_ui == SEARCH_START_SELECT) {
        cur_start_select -= 1;
        if (cur_start_select <= 0) {
            cur_start_select = 0;
        }
    } else if (cur_ui == SEARCH_END) {
        cur_alpha_idx -= 1;
        if (cur_alpha_idx < 0) {
            cur_alpha_idx += 26;
        }
    } else if (cur_ui == SEARCH_END_SELECT) {
        cur_end_select -= 1;
        if (cur_end_select <= 0) {
            cur_end_select = 0;
        }
    }
    draw_ui();
}

void left_doubleclick() {
    if (cur_ui == SHOW_METRO_LINES || cur_ui == SEARCH_START || cur_ui == USER_GUIDE) {
        cur_ui = WELCOME;
    } else if (cur_ui == LINE_RESULT) {
        if (pre_ui == SHOW_METRO_LINES) {
            cur_ui = SHOW_METRO_LINES;
        } else if (pre_ui == SEARCH_END_SELECT) {
            cur_ui = SEARCH_START;
        }
    } else if (cur_ui == SEARCH_START_SELECT) {
        cur_ui = SEARCH_START;
    } else if (cur_ui == SEARCH_END) {
        cur_ui = SEARCH_START_SELECT;
        cur_start_select = 0;
    } else if (cur_ui == SEARCH_END_SELECT) {
        cur_ui = SEARCH_END;
    }
    draw_ui();
}

void init_button() {
    pinMode(RIGHT_BUTTON, INPUT_PULLUP);
    pinMode(LEFT_BUTTON, INPUT_PULLUP);

    button_right.attachClick(right_click);
    button_right.attachDoubleClick(right_doubleclick);
    button_right.attachDuringLongPress(RightDuringLongPress);
    button_right.setLongPressIntervalMs(300);

    button_left.attachClick(left_click);
    button_left.attachDoubleClick(left_doubleclick);
    button_left.attachDuringLongPress(LeftDuringLongPress);
    button_left.setLongPressIntervalMs(300);
}

void loop_button() {
    button_right.tick();
    button_left.tick();
}

void setup() {
    /* Amoled lcd initialization. */
    rm67162_init();
    lcd_setRotation(0);
    lcd_brightness(150);

    init_button();
    Serial.begin(115200);

    init_lists();
    get_transition_stations();
    draw_ui();
}

void loop() { loop_button(); }
