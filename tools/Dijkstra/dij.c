#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#define V 516  // 假设每条地铁线有10个站

const char line_names[][10] = {
    "1号线",
    "2号线",
    "3号线",
    "4号线",
    "5号线",
    "6号线",
    "7号线",
    "8号线",
    "9号线",
    "10号线",
    "11号线",
    "12号线",
    "13号线",
    "14号线",
    "15号线",
    "16号线",
    "17号线",
    "18号线",
    "浦江线",
};

const uint8_t line_station_nums[] = {
    28, 30, 29, 26, 19, 28, 33, 29, 35, 37, 40, 32, 32, 30, 30, 13, 13, 26, 6};

const uint16_t line_station_start[] = {
    0, 28, 58, 87, 113, 132, 160, 193, 222, 257, 294, 334, 366, 398, 428, 458, 471, 484, 510};

const char lines[][45] = {
    "莘庄",
    "外环路",
    "莲花路",
    "锦江乐园",
    "上海南站",
    "漕宝路",
    "上海体育馆",
    "徐家汇",
    "衡山路",
    "常熟路",
    "陕西南路",
    "一大会址·黄陂南路",
    "人民广场",
    "新闸路",
    "汉中路",
    "上海火车站",
    "中山北路",
    "延长路",
    "上海马戏城",
    "汶水路",
    "彭浦新村",
    "共康路",
    "通河新村",
    "呼兰路",
    "共富新村",
    "宝安公路",
    "友谊西路",
    "富锦路",

    "徐泾东",
    "虹桥火车站",
    "虹桥2号航站楼",
    "淞虹路",
    "北新泾",
    "威宁路",
    "娄山关路",
    "中山公园",
    "江苏路",
    "静安寺",
    "南京西路",
    "人民广场",
    "南京东路",
    "陆家嘴",
    "东昌路",
    "世纪大道",
    "上海科技馆",
    "世纪公园",
    "龙阳路",
    "张江高科",
    "金科路",
    "广兰路",
    "唐镇",
    "创新中路",
    "华夏东路",
    "川沙",
    "凌空路",
    "远东大道",
    "海天三路",
    "浦东国际机场",

    "上海南站",
    "石龙路",
    "龙漕路",
    "漕溪路",
    "宜山路",
    "虹桥路",
    "延安西路",
    "中山公园",
    "金沙江路",
    "曹杨路",
    "镇坪路",
    "中潭路",
    "上海火车站",
    "宝山路",
    "东宝兴路",
    "虹口足球场",
    "赤峰路",
    "大柏树",
    "江湾镇",
    "殷高西路",
    "长江南路",
    "淞发路",
    "张华浜",
    "淞滨路",
    "水产路",
    "宝杨路",
    "友谊路",
    "铁力路",
    "江杨北路",

    "上海体育馆",
    "宜山路",
    "虹桥路",
    "延安西路",
    "中山公园",
    "金沙江路",
    "曹杨路",
    "镇坪路",
    "中潭路",
    "上海火车站",
    "宝山路",
    "海伦路",
    "临平路",
    "大连路",
    "杨树浦路",
    "浦东大道",
    "世纪大道",
    "浦电路",
    "蓝村路",
    "塘桥",
    "南浦大桥",
    "西藏南路",
    "鲁班路",
    "大木桥路",
    "东安路",
    "上海体育场",

    "莘庄",
    "春申路",
    "银都路",
    "颛桥",
    "北桥",
    "剑川路",
    "东川路",
    "金平路",
    "华宁路",
    "文井路",
    "闵行开发区",
    "江川路",
    "西渡",
    "萧塘",
    "奉浦大道",
    "环城东路",
    "望园路",
    "金海湖",
    "奉贤新城",

    "东方体育中心",
    "灵岩南路",
    "上南路",
    "华夏西路",
    "高青路",
    "东明路",
    "高科西路",
    "临沂新村",
    "上海儿童医学中心",
    "蓝村路",
    "浦电路",
    "世纪大道",
    "源深体育中心",
    "民生路",
    "北洋泾路",
    "德平路",
    "云山路",
    "金桥路",
    "博兴路",
    "五莲路",
    "巨峰路",
    "东靖路",
    "五洲大道",
    "洲海路",
    "外高桥保税区南站",
    "航津路",
    "外高桥保税区北站",
    "港城路",

    "美兰湖",
    "罗南新村",
    "潘广路",
    "刘行",
    "顾村公园",
    "祁华路",
    "上海大学",
    "南陈路",
    "上大路",
    "场中路",
    "大场镇",
    "行知路",
    "大华三路",
    "新村路",
    "岚皋路",
    "镇坪路",
    "长寿路",
    "昌平路",
    "静安寺",
    "常熟路",
    "肇嘉浜路",
    "东安路",
    "龙华中路",
    "后滩",
    "长清路",
    "耀华路",
    "云台路",
    "高科西路",
    "杨高南路",
    "锦绣路",
    "芳华路",
    "龙阳路",
    "花木路",

    "沈杜公路",
    "联航路",
    "江月路",
    "浦江镇",
    "芦恒路",
    "凌兆新村",
    "东方体育中心",
    "杨思成山路",
    "耀华路",
    "中华艺术宫",
    "西藏南路",
    "陆家浜路",
    "老西门",
    "大世界",
    "人民广场",
    "曲阜路",
    "中兴路",
    "西藏北路",
    "虹口足球场",
    "曲阳路",
    "四平路",
    "鞍山新村",
    "江浦路",
    "黄兴路",
    "延吉中路",
    "黄兴公园",
    "翔殷路",
    "嫩江路",
    "市光路",

    "松江南站",
    "醉白池",
    "松江体育中心",
    "松江新城",
    "松江大学城",
    "洞泾",
    "佘山",
    "泗泾",
    "九亭",
    "中春路",
    "七宝",
    "星中路",
    "合川路",
    "漕河泾开发区",
    "桂林路",
    "宜山路",
    "徐家汇",
    "肇嘉浜路",
    "嘉善路",
    "打浦桥",
    "马当路",
    "陆家浜路",
    "小南门",
    "商城路",
    "世纪大道",
    "杨高中路",
    "芳甸路",
    "蓝天路",
    "台儿庄路",
    "金桥",
    "金吉路",
    "金海路",
    "顾唐路",
    "民雷路",
    "曹路",

    "航中路",
    "紫藤路",
    "龙柏新村",
    "虹桥火车站",
    "虹桥2号航站楼",
    "虹桥1号航站楼",
    "上海动物园",
    "龙溪路",
    "水城路",
    "伊犁路",
    "宋园路",
    "虹桥路",
    "交通大学",
    "上海图书馆",
    "陕西南路",
    "一大会址·新天地",
    "老西门",
    "豫园",
    "南京东路",
    "天潼路",
    "四川北路",
    "海伦路",
    "邮电新村",
    "四平路",
    "同济大学",
    "国权路",
    "五角场",
    "江湾体育场",
    "三门路",
    "殷高东路",
    "新江湾城",
    "国帆路",
    "双江路",
    "高桥西",
    "高桥",
    "港城路",
    "基隆路",

    "花桥",
    "光明路",
    "兆丰路",
    "安亭",
    "上海汽车城",
    "昌吉东路",
    "上海赛车场",
    "嘉定北",
    "嘉定西",
    "白银路",
    "嘉定新城",
    "马陆",
    "陈翔公路",
    "南翔",
    "桃浦新村",
    "武威路",
    "祁连山路",
    "李子园",
    "上海西站",
    "真如",
    "枫桥路",
    "曹杨路",
    "隆德路",
    "江苏路",
    "交通大学",
    "徐家汇",
    "上海游泳馆",
    "龙华",
    "云锦路",
    "龙耀路",
    "东方体育中心",
    "三林",
    "三林东",
    "浦三路",
    "（预留车站）",
    "御桥",
    "罗山路",
    "秀沿路",
    "康新公路",
    "迪士尼",

    "七莘路",
    "虹莘路",
    "顾戴路",
    "东兰路",
    "虹梅路",
    "虹漕路",
    "桂林公园",
    "漕宝路",
    "龙漕路",
    "龙华",
    "龙华中路",
    "大木桥路",
    "嘉善路",
    "陕西南路",
    "南京西路",
    "汉中路",
    "曲阜路",
    "天潼路",
    "国际客运中心",
    "提篮桥",
    "大连路",
    "江浦公园",
    "宁国路",
    "隆昌路",
    "爱国路",
    "复兴岛",
    "东陆路",
    "巨峰路",
    "杨高北路",
    "金京路",
    "申江路",
    "金海路",

    "金运路",
    "金沙",
    "江西路",
    "丰庄",
    "祁连山南路",
    "真北路",
    "大渡河路",
    "金沙江路",
    "隆德路",
    "武宁路",
    "长寿路",
    "江宁路",
    "汉中路",
    "自然博物馆",
    "南京西路",
    "淮海中路",
    "一大会址·新天地",
    "马当路",
    "世博会博物馆",
    "世博大道",
    "长清路",
    "成山路",
    "东明路",
    "华鹏路",
    "下南路",
    "北蔡",
    "陈春路",
    "莲溪路",
    "华夏中路",
    "中科路",
    "学林路",
    "张江路",

    "封浜",
    "乐秀路",
    "临洮路",
    "嘉怡路",
    "定边路",
    "真新新村",
    "真光路",
    "铜川路",
    "真如",
    "中宁路",
    "曹杨路",
    "武宁路",
    "武定路",
    "静安寺",
    "一大会址•黄陂南路",
    "大世界",
    "豫园",
    "陆家嘴",
    "浦东南路",
    "浦东大道",
    "源深路",
    "昌邑路",
    "歇浦路",
    "云山路",
    "蓝天路",
    "黄杨路",
    "云顺路",
    "浦东足球场",
    "金粤路",
    "桂桥路",

    "紫竹高新区",
    "永德路",
    "元江路",
    "双柏路",
    "曙建路",
    "景西路",
    "虹梅南路",
    "华泾西",
    "朱梅路",
    "罗秀路",
    "华东理工大学",
    "上海南站",
    "桂林公园",
    "桂林路",
    "吴中路",
    "姚虹路",
    "红宝石路",
    "娄山关路",
    "长风公园",
    "大渡河路",
    "梅岭北路",
    "铜川路",
    "上海西站",
    "武威东路",
    "古浪路",
    "祁安路",
    "南大路",
    "丰翔路",
    "锦秋路",
    "顾村公园",

    "龙阳路",
    "华夏中路",
    "罗山路",
    "周浦东",
    "鹤沙航城",
    "航头东",
    "新场",
    "野生动物园",
    "惠南",
    "惠南东",
    "书院",
    "临港大道",
    "滴水湖",

    "虹桥火车站",
    "诸光路",
    "蟠龙路",
    "徐盈路",
    "徐泾北城",
    "嘉松中路",
    "赵巷",
    "汇金路",
    "青浦新城",
    "漕盈路",
    "淀山湖大道",
    "朱家角",
    "东方绿舟",

    "航头",
    "下沙",
    "鹤涛路",
    "沈梅路",
    "繁荣路",
    "周浦",
    "康桥",
    "御桥",
    "莲溪路",
    "北中路",
    "芳芯路",
    "龙阳路",
    "迎春路",
    "杨高中路",
    "民生路",
    "昌邑路",
    "丹阳路",
    "平凉路",
    "江浦公园",
    "江浦路",
    "抚顺路",
    "国权路",
    "复旦大学",
    "上海财经大学",
    "殷高路",
    "长江南路",

    "沈杜公路",
    "三鲁公路",
    "闵瑞路",
    "浦航路",
    "东城一路",
    "汇臻路",
};

const uint16_t edges[][3] = 
{
    {0, 1, 3},          // 莘庄, 外环路
    {1, 2, 3},          // 外环路, 莲花路
    {2, 3, 3},          // 莲花路, 锦江乐园
    {3, 4, 3},          // 锦江乐园, 上海南站
    {4, 5, 3},          // 上海南站, 漕宝路
    {5, 6, 3},          // 漕宝路, 上海体育馆
    {6, 7, 3},          // 上海体育馆, 徐家汇
    {7, 8, 3},          // 徐家汇, 衡山路
    {8, 9, 3},          // 衡山路, 常熟路
    {9, 10, 3},         // 常熟路, 陕西南路
    {10, 11, 3},        // 陕西南路, 一大会址·黄陂南路
    {11, 12, 3},        // 一大会址·黄陂南路, 人民广场
    {12, 13, 3},        // 人民广场, 新闸路
    {13, 14, 3},        // 新闸路, 汉中路
    {14, 15, 3},        // 汉中路, 上海火车站
    {15, 16, 3},        // 上海火车站, 中山北路
    {16, 17, 3},        // 中山北路, 延长路
    {17, 18, 3},        // 延长路, 上海马戏城
    {18, 19, 3},        // 上海马戏城, 汶水路
    {19, 20, 3},        // 汶水路, 彭浦新村
    {20, 21, 3},        // 彭浦新村, 共康路
    {21, 22, 3},        // 共康路, 通河新村
    {22, 23, 3},        // 通河新村, 呼兰路
    {23, 24, 3},        // 呼兰路, 共富新村
    {24, 25, 3},        // 共富新村, 宝安公路
    {25, 26, 3},        // 宝安公路, 友谊西路
    {26, 27, 3},        // 友谊西路, 富锦路

    {28, 29, 3},        // 徐泾东, 虹桥火车站
    {29, 30, 3},        // 虹桥火车站, 虹桥2号航站楼
    {30, 31, 3},        // 虹桥2号航站楼, 淞虹路
    {31, 32, 3},        // 淞虹路, 北新泾
    {32, 33, 3},        // 北新泾, 威宁路
    {33, 34, 3},        // 威宁路, 娄山关路
    {34, 35, 3},        // 娄山关路, 中山公园
    {35, 36, 3},        // 中山公园, 江苏路
    {36, 37, 3},        // 江苏路, 静安寺
    {37, 38, 3},        // 静安寺, 南京西路
    {38, 39, 3},        // 南京西路, 人民广场
    {39, 40, 3},        // 人民广场, 南京东路
    {12, 39, 3},        // 人民广场, 人民广场
    {40, 41, 3},        // 南京东路, 陆家嘴
    {41, 42, 3},        // 陆家嘴, 东昌路
    {42, 43, 3},        // 东昌路, 世纪大道
    {43, 44, 3},        // 世纪大道, 上海科技馆
    {44, 45, 3},        // 上海科技馆, 世纪公园
    {45, 46, 3},        // 世纪公园, 龙阳路
    {46, 47, 3},        // 龙阳路, 张江高科
    {47, 48, 3},        // 张江高科, 金科路
    {48, 49, 3},        // 金科路, 广兰路
    {49, 50, 3},        // 广兰路, 唐镇
    {50, 51, 3},        // 唐镇, 创新中路
    {51, 52, 3},        // 创新中路, 华夏东路
    {52, 53, 3},        // 华夏东路, 川沙
    {53, 54, 3},        // 川沙, 凌空路
    {54, 55, 3},        // 凌空路, 远东大道
    {55, 56, 3},        // 远东大道, 海天三路
    {56, 57, 3},        // 海天三路, 浦东国际机场
    {58, 59, 3},        // 上海南站, 石龙路
    {4, 58, 3},         // 上海南站, 上海南站
    {59, 60, 3},        // 石龙路, 龙漕路
    {60, 61, 3},        // 龙漕路, 漕溪路
    {61, 62, 3},        // 漕溪路, 宜山路
    {62, 63, 3},        // 宜山路, 虹桥路
    {63, 64, 3},        // 虹桥路, 延安西路
    {64, 65, 3},        // 延安西路, 中山公园
    {65, 66, 3},        // 中山公园, 金沙江路
    {35, 65, 3},        // 中山公园, 中山公园
    {66, 67, 3},        // 金沙江路, 曹杨路
    {67, 68, 3},        // 曹杨路, 镇坪路
    {68, 69, 3},        // 镇坪路, 中潭路
    {69, 70, 3},        // 中潭路, 上海火车站
    {70, 71, 3},        // 上海火车站, 宝山路
    {15, 70, 3},        // 上海火车站, 上海火车站
    {71, 72, 3},        // 宝山路, 东宝兴路
    {72, 73, 3},        // 东宝兴路, 虹口足球场
    {73, 74, 3},        // 虹口足球场, 赤峰路
    {74, 75, 3},        // 赤峰路, 大柏树
    {75, 76, 3},        // 大柏树, 江湾镇
    {76, 77, 3},        // 江湾镇, 殷高西路
    {77, 78, 3},        // 殷高西路, 长江南路
    {78, 79, 3},        // 长江南路, 淞发路
    {79, 80, 3},        // 淞发路, 张华浜
    {80, 81, 3},        // 张华浜, 淞滨路
    {81, 82, 3},        // 淞滨路, 水产路
    {82, 83, 3},        // 水产路, 宝杨路
    {83, 84, 3},        // 宝杨路, 友谊路
    {84, 85, 3},        // 友谊路, 铁力路
    {85, 86, 3},        // 铁力路, 江杨北路
    {87, 88, 3},        // 上海体育馆, 宜山路
    {6, 87, 3}, // 上海体育馆, 上海体育馆
    {88, 89, 3},        // 宜山路, 虹桥路
    {62, 88, 3},        // 宜山路, 宜山路
    {89, 90, 3},        // 虹桥路, 延安西路
    {63, 89, 3},        // 虹桥路, 虹桥路
    {90, 91, 3},        // 延安西路, 中山公园
    {64, 90, 3},        // 延安西路, 延安西路
    {91, 92, 3},        // 中山公园, 金沙江路
    {35, 91, 3},        // 中山公园, 中山公园
    {65, 91, 3},        // 中山公园, 中山公园
    {92, 93, 3},        // 金沙江路, 曹杨路
    {66, 92, 3},        // 金沙江路, 金沙江路
    {93, 94, 3},        // 曹杨路, 镇坪路
    {67, 93, 3},        // 曹杨路, 曹杨路
    {94, 95, 3},        // 镇坪路, 中潭路
    {68, 94, 3},        // 镇坪路, 镇坪路
    {95, 96, 3},        // 中潭路, 上海火车站
    {69, 95, 3},        // 中潭路, 中潭路
    {96, 97, 3},        // 上海火车站, 宝山路
    {15, 96, 3},        // 上海火车站, 上海火车站
    {70, 96, 3},        // 上海火车站, 上海火车站
    {97, 98, 3},        // 宝山路, 海伦路
    {71, 97, 3},        // 宝山路, 宝山路
    {98, 99, 3},        // 海伦路, 临平路
    {99, 100, 3},       // 临平路, 大连路
    {100, 101, 3},      // 大连路, 杨树浦路
    {101, 102, 3},      // 杨树浦路, 浦东大道
    {102, 103, 3},      // 浦东大道, 世纪大道
    {103, 104, 3},      // 世纪大道, 浦电路
    {43, 103, 3},       // 世纪大道, 世纪大道
    {104, 105, 3},      // 浦电路, 蓝村路
    {105, 106, 3},      // 蓝村路, 塘桥
    {106, 107, 3},      // 塘桥, 南浦大桥
    {107, 108, 3},      // 南浦大桥, 西藏南路
    {108, 109, 3},      // 西藏南路, 鲁班路
    {109, 110, 3},      // 鲁班路, 大木桥路
    {110, 111, 3},      // 大木桥路, 东安路
    {111, 112, 3},      // 东安路, 上海体育场
    {113, 114, 3},      // 莘庄, 春申路
    {0, 113, 3},        // 莘庄, 莘庄
    {114, 115, 3},      // 春申路, 银都路
    {115, 116, 3},      // 银都路, 颛桥
    {116, 117, 3},      // 颛桥, 北桥
    {117, 118, 3},      // 北桥, 剑川路
    {118, 119, 3},      // 剑川路, 东川路
    {119, 120, 3},      // 东川路, 金平路
    {120, 121, 3},      // 金平路, 华宁路
    {121, 122, 3},      // 华宁路, 文井路
    {122, 123, 3},      // 文井路, 闵行开发区
    {123, 124, 3},      // 闵行开发区, 江川路
    {124, 125, 3},      // 江川路, 西渡
    {125, 126, 3},      // 西渡, 萧塘
    {126, 127, 3},      // 萧塘, 奉浦大道
    {127, 128, 3},      // 奉浦大道, 环城东路
    {128, 129, 3},      // 环城东路, 望园路
    {129, 130, 3},      // 望园路, 金海湖
    {130, 131, 3},      // 金海湖, 奉贤新城
    {132, 133, 3},      // 东方体育中心, 灵岩南路
    {133, 134, 3},      // 灵岩南路, 上南路
    {134, 135, 3},      // 上南路, 华夏西路
    {135, 136, 3},      // 华夏西路, 高青路
    {136, 137, 3},      // 高青路, 东明路
    {137, 138, 3},      // 东明路, 高科西路
    {138, 139, 3},      // 高科西路, 临沂新村
    {139, 140, 3},      // 临沂新村, 上海儿童医学中心
    {140, 141, 3},      // 上海儿童医学中心, 蓝村路
    {141, 142, 3},      // 蓝村路, 浦电路
    {105, 141, 3},      // 蓝村路, 蓝村路
    {142, 143, 3},      // 浦电路, 世纪大道
    {104, 142, 3},      // 浦电路, 浦电路
    {143, 144, 3},      // 世纪大道, 源深体育中心
    {43, 143, 3},       // 世纪大道, 世纪大道
    {103, 143, 3},      // 世纪大道, 世纪大道
    {144, 145, 3},      // 源深体育中心, 民生路
    {145, 146, 3},      // 民生路, 北洋泾路
    {146, 147, 3},      // 北洋泾路, 德平路
    {147, 148, 3},      // 德平路, 云山路
    {148, 149, 3},      // 云山路, 金桥路
    {149, 150, 3},      // 金桥路, 博兴路
    {150, 151, 3},      // 博兴路, 五莲路
    {151, 152, 3},      // 五莲路, 巨峰路
    {152, 153, 3},      // 巨峰路, 东靖路
    {153, 154, 3},      // 东靖路, 五洲大道
    {154, 155, 3},      // 五洲大道, 洲海路
    {155, 156, 3},      // 洲海路, 外高桥保税区南站
    {156, 157, 3},      // 外高桥保税区南站, 航津路
    {157, 158, 3},      // 航津路, 外高桥保税区北站
    {158, 159, 3},      // 外高桥保税区北站, 港城路
    {160, 161, 3},      // 美兰湖, 罗南新村
    {161, 162, 3},      // 罗南新村, 潘广路
    {162, 163, 3},      // 潘广路, 刘行
    {163, 164, 3},      // 刘行, 顾村公园
    {164, 165, 3},      // 顾村公园, 祁华路
    {165, 166, 3},      // 祁华路, 上海大学
    {166, 167, 3},      // 上海大学, 南陈路
    {167, 168, 3},      // 南陈路, 上大路
    {168, 169, 3},      // 上大路, 场中路
    {169, 170, 3},      // 场中路, 大场镇
    {170, 171, 3},      // 大场镇, 行知路
    {171, 172, 3},      // 行知路, 大华三路
    {172, 173, 3},      // 大华三路, 新村路
    {173, 174, 3},      // 新村路, 岚皋路
    {174, 175, 3},      // 岚皋路, 镇坪路
    {175, 176, 3},      // 镇坪路, 长寿路
    {68, 175, 3},       // 镇坪路, 镇坪路
    {94, 175, 3},       // 镇坪路, 镇坪路
    {176, 177, 3},      // 长寿路, 昌平路
    {177, 178, 3},      // 昌平路, 静安寺
    {178, 179, 3},      // 静安寺, 常熟路
    {37, 178, 3},       // 静安寺, 静安寺
    {179, 180, 3},      // 常熟路, 肇嘉浜路
    {9, 179, 3},        // 常熟路, 常熟路
    {180, 181, 3},      // 肇嘉浜路, 东安路
    {181, 182, 3},      // 东安路, 龙华中路
    {111, 181, 3},      // 东安路, 东安路
    {182, 183, 3},      // 龙华中路, 后滩
    {183, 184, 3},      // 后滩, 长清路
    {184, 185, 3},      // 长清路, 耀华路
    {185, 186, 3},      // 耀华路, 云台路
    {186, 187, 3},      // 云台路, 高科西路
    {187, 188, 3},      // 高科西路, 杨高南路
    {138, 187, 3},      // 高科西路, 高科西路
    {188, 189, 3},      // 杨高南路, 锦绣路
    {189, 190, 3},      // 锦绣路, 芳华路
    {190, 191, 3},      // 芳华路, 龙阳路
    {191, 192, 3},      // 龙阳路, 花木路
    {46, 191, 3},       // 龙阳路, 龙阳路
    {193, 194, 3},      // 沈杜公路, 联航路
    {194, 195, 3},      // 联航路, 江月路
    {195, 196, 3},      // 江月路, 浦江镇
    {196, 197, 3},      // 浦江镇, 芦恒路
    {197, 198, 3},      // 芦恒路, 凌兆新村
    {198, 199, 3},      // 凌兆新村, 东方体育中心
    {199, 200, 3},      // 东方体育中心, 杨思成山路
    {132, 199, 3},      // 东方体育中心, 东方体育中心
    {200, 201, 3},      // 杨思成山路, 耀华路
    {201, 202, 3},      // 耀华路, 中华艺术宫
    {185, 201, 3},      // 耀华路, 耀华路
    {202, 203, 3},      // 中华艺术宫, 西藏南路
    {203, 204, 3},      // 西藏南路, 陆家浜路
    {108, 203, 3},      // 西藏南路, 西藏南路
    {204, 205, 3},      // 陆家浜路, 老西门
    {205, 206, 3},      // 老西门, 大世界
    {206, 207, 3},      // 大世界, 人民广场
    {207, 208, 3},      // 人民广场, 曲阜路
    {12, 207, 3},       // 人民广场, 人民广场
    {39, 207, 3},       // 人民广场, 人民广场
    {208, 209, 3},      // 曲阜路, 中兴路
    {209, 210, 3},      // 中兴路, 西藏北路
    {210, 211, 3},      // 西藏北路, 虹口足球场
    {211, 212, 3},      // 虹口足球场, 曲阳路
    {73, 211, 3},       // 虹口足球场, 虹口足球场
    {212, 213, 3},      // 曲阳路, 四平路
    {213, 214, 3},      // 四平路, 鞍山新村
    {214, 215, 3},      // 鞍山新村, 江浦路
    {215, 216, 3},      // 江浦路, 黄兴路
    {216, 217, 3},      // 黄兴路, 延吉中路
    {217, 218, 3},      // 延吉中路, 黄兴公园
    {218, 219, 3},      // 黄兴公园, 翔殷路
    {219, 220, 3},      // 翔殷路, 嫩江路
    {220, 221, 3},      // 嫩江路, 市光路
    {222, 223, 3},      // 松江南站, 醉白池
    {223, 224, 3},      // 醉白池, 松江体育中心
    {224, 225, 3},      // 松江体育中心, 松江新城
    {225, 226, 3},      // 松江新城, 松江大学城
    {226, 227, 3},      // 松江大学城, 洞泾
    {227, 228, 3},      // 洞泾, 佘山
    {228, 229, 3},      // 佘山, 泗泾
    {229, 230, 3},      // 泗泾, 九亭
    {230, 231, 3},      // 九亭, 中春路
    {231, 232, 3},      // 中春路, 七宝
    {232, 233, 3},      // 七宝, 星中路
    {233, 234, 3},      // 星中路, 合川路
    {234, 235, 3},      // 合川路, 漕河泾开发区
    {235, 236, 3},      // 漕河泾开发区, 桂林路
    {236, 237, 3},      // 桂林路, 宜山路
    {237, 238, 3},      // 宜山路, 徐家汇
    {62, 237, 3},       // 宜山路, 宜山路
    {88, 237, 3},       // 宜山路, 宜山路
    {238, 239, 3},      // 徐家汇, 肇嘉浜路
    {7, 238, 3},        // 徐家汇, 徐家汇
    {239, 240, 3},      // 肇嘉浜路, 嘉善路
    {180, 239, 3},      // 肇嘉浜路, 肇嘉浜路
    {240, 241, 3},      // 嘉善路, 打浦桥
    {241, 242, 3},      // 打浦桥, 马当路
    {242, 243, 3},      // 马当路, 陆家浜路
    {243, 244, 3},      // 陆家浜路, 小南门
    {204, 243, 3},      // 陆家浜路, 陆家浜路
    {244, 245, 3},      // 小南门, 商城路
    {245, 246, 3},      // 商城路, 世纪大道
    {246, 247, 3},      // 世纪大道, 杨高中路
    {43, 246, 3},       // 世纪大道, 世纪大道
    {103, 246, 3},      // 世纪大道, 世纪大道
    {143, 246, 3},      // 世纪大道, 世纪大道
    {247, 248, 3},      // 杨高中路, 芳甸路
    {248, 249, 3},      // 芳甸路, 蓝天路
    {249, 250, 3},      // 蓝天路, 台儿庄路
    {250, 251, 3},      // 台儿庄路, 金桥
    {251, 252, 3},      // 金桥, 金吉路
    {252, 253, 3},      // 金吉路, 金海路
    {253, 254, 3},      // 金海路, 顾唐路
    {254, 255, 3},      // 顾唐路, 民雷路
    {255, 256, 3},      // 民雷路, 曹路
    {257, 258, 3},      // 航中路, 紫藤路
    {258, 259, 3},      // 紫藤路, 龙柏新村
    {259, 260, 3},      // 龙柏新村, 虹桥火车站
    {260, 261, 3},      // 虹桥火车站, 虹桥2号航站楼
    {29, 260, 3},       // 虹桥火车站, 虹桥火车站
    {261, 262, 3},      // 虹桥2号航站楼, 虹桥1号航站楼
    {30, 261, 3},       // 虹桥2号航站楼, 虹桥2号航站楼
    {262, 263, 3},      // 虹桥1号航站楼, 上海动物园
    {263, 264, 3},      // 上海动物园, 龙溪路
    {264, 265, 3},      // 龙溪路, 水城路
    {265, 266, 3},      // 水城路, 伊犁路
    {266, 267, 3},      // 伊犁路, 宋园路
    {267, 268, 3},      // 宋园路, 虹桥路
    {268, 269, 3},      // 虹桥路, 交通大学
    {63, 268, 3},       // 虹桥路, 虹桥路
    {89, 268, 3},       // 虹桥路, 虹桥路
    {269, 270, 3},      // 交通大学, 上海图书馆
    {270, 271, 3},      // 上海图书馆, 陕西南路
    {271, 272, 3},      // 陕西南路, 一大会址·新天地
    {10, 271, 3},       // 陕西南路, 陕西南路
    {272, 273, 3},      // 一大会址·新天地, 老西门
    {273, 274, 3},      // 老西门, 豫园
    {205, 273, 3},      // 老西门, 老西门
    {274, 275, 3},      // 豫园, 南京东路
    {275, 276, 3},      // 南京东路, 天潼路
    {40, 275, 3},       // 南京东路, 南京东路
    {276, 277, 3},      // 天潼路, 四川北路
    {277, 278, 3},      // 四川北路, 海伦路
    {278, 279, 3},      // 海伦路, 邮电新村
    {98, 278, 3},       // 海伦路, 海伦路
    {279, 280, 3},      // 邮电新村, 四平路
    {280, 281, 3},      // 四平路, 同济大学
    {213, 280, 3},      // 四平路, 四平路
    {281, 282, 3},      // 同济大学, 国权路
    {282, 283, 3},      // 国权路, 五角场
    {283, 284, 3},      // 五角场, 江湾体育场
    {284, 285, 3},      // 江湾体育场, 三门路
    {285, 286, 3},      // 三门路, 殷高东路
    {286, 287, 3},      // 殷高东路, 新江湾城
    {287, 288, 3},      // 新江湾城, 国帆路
    {288, 289, 3},      // 国帆路, 双江路
    {289, 290, 3},      // 双江路, 高桥西
    {290, 291, 3},      // 高桥西, 高桥
    {291, 292, 3},      // 高桥, 港城路
    {292, 293, 3},      // 港城路, 基隆路
    {159, 292, 3},      // 港城路, 港城路
    {294, 295, 3},      // 花桥, 光明路
    {295, 296, 3},      // 光明路, 兆丰路
    {296, 297, 3},      // 兆丰路, 安亭
    {297, 298, 3},      // 安亭, 上海汽车城
    {298, 299, 3},      // 上海汽车城, 昌吉东路
    {299, 300, 3},      // 昌吉东路, 上海赛车场
    {300, 301, 3},      // 上海赛车场, 嘉定北
    {301, 302, 3},      // 嘉定北, 嘉定西
    {302, 303, 3},      // 嘉定西, 白银路
    {303, 304, 3},      // 白银路, 嘉定新城
    {304, 305, 3},      // 嘉定新城, 马陆
    {305, 306, 3},      // 马陆, 陈翔公路
    {306, 307, 3},      // 陈翔公路, 南翔
    {307, 308, 3},      // 南翔, 桃浦新村
    {308, 309, 3},      // 桃浦新村, 武威路
    {309, 310, 3},      // 武威路, 祁连山路
    {310, 311, 3},      // 祁连山路, 李子园
    {311, 312, 3},      // 李子园, 上海西站
    {312, 313, 3},      // 上海西站, 真如
    {313, 314, 3},      // 真如, 枫桥路
    {314, 315, 3},      // 枫桥路, 曹杨路
    {315, 316, 3},      // 曹杨路, 隆德路
    {67, 315, 3},       // 曹杨路, 曹杨路
    {93, 315, 3},       // 曹杨路, 曹杨路
    {316, 317, 3},      // 隆德路, 江苏路
    {317, 318, 3},      // 江苏路, 交通大学
    {36, 317, 3},       // 江苏路, 江苏路
    {318, 319, 3},      // 交通大学, 徐家汇
    {269, 318, 3},      // 交通大学, 交通大学
    {319, 320, 3},      // 徐家汇, 上海游泳馆
    {7, 319, 3},        // 徐家汇, 徐家汇
    {238, 319, 3},      // 徐家汇, 徐家汇
    {320, 321, 3},      // 上海游泳馆, 龙华
    {321, 322, 3},      // 龙华, 云锦路
    {322, 323, 3},      // 云锦路, 龙耀路
    {323, 324, 3},      // 龙耀路, 东方体育中心
    {324, 325, 3},      // 东方体育中心, 三林
    {132, 324, 3},      // 东方体育中心, 东方体育中心
    {199, 324, 3},      // 东方体育中心, 东方体育中心
    {325, 326, 3},      // 三林, 三林东
    {326, 327, 3},      // 三林东, 浦三路
    {327, 328, 3},      // 浦三路, （预留车站）
    {328, 329, 3},      // （预留车站）, 御桥
    {329, 330, 3},      // 御桥, 罗山路
    {330, 331, 3},      // 罗山路, 秀沿路
    {331, 332, 3},      // 秀沿路, 康新公路
    {332, 333, 3},      // 康新公路, 迪士尼
    {334, 335, 3},      // 七莘路, 虹莘路
    {335, 336, 3},      // 虹莘路, 顾戴路
    {336, 337, 3},      // 顾戴路, 东兰路
    {337, 338, 3},      // 东兰路, 虹梅路
    {338, 339, 3},      // 虹梅路, 虹漕路
    {339, 340, 3},      // 虹漕路, 桂林公园
    {340, 341, 3},      // 桂林公园, 漕宝路
    {341, 342, 3},      // 漕宝路, 龙漕路
    {5, 341, 3},        // 漕宝路, 漕宝路
    {342, 343, 3},      // 龙漕路, 龙华
    {60, 342, 3},       // 龙漕路, 龙漕路
    {343, 344, 3},      // 龙华, 龙华中路
    {321, 343, 3},      // 龙华, 龙华
    {344, 345, 3},      // 龙华中路, 大木桥路
    {182, 344, 3},      // 龙华中路, 龙华中路
    {345, 346, 3},      // 大木桥路, 嘉善路
    {110, 345, 3},      // 大木桥路, 大木桥路
    {346, 347, 3},      // 嘉善路, 陕西南路
    {240, 346, 3},      // 嘉善路, 嘉善路
    {347, 348, 3},      // 陕西南路, 南京西路
    {10, 347, 3},       // 陕西南路, 陕西南路
    {271, 347, 3},      // 陕西南路, 陕西南路
    {348, 349, 3},      // 南京西路, 汉中路
    {38, 348, 3},       // 南京西路, 南京西路
    {349, 350, 3},      // 汉中路, 曲阜路
    {14, 349, 3},       // 汉中路, 汉中路
    {350, 351, 3},      // 曲阜路, 天潼路
    {208, 350, 3},      // 曲阜路, 曲阜路
    {351, 352, 3},      // 天潼路, 国际客运中心
    {276, 351, 3},      // 天潼路, 天潼路
    {352, 353, 3},      // 国际客运中心, 提篮桥
    {353, 354, 3},      // 提篮桥, 大连路
    {354, 355, 3},      // 大连路, 江浦公园
    {100, 354, 3},      // 大连路, 大连路
    {355, 356, 3},      // 江浦公园, 宁国路
    {356, 357, 3},      // 宁国路, 隆昌路
    {357, 358, 3},      // 隆昌路, 爱国路
    {358, 359, 3},      // 爱国路, 复兴岛
    {359, 360, 3},      // 复兴岛, 东陆路
    {360, 361, 3},      // 东陆路, 巨峰路
    {361, 362, 3},      // 巨峰路, 杨高北路
    {152, 361, 3},      // 巨峰路, 巨峰路
    {362, 363, 3},      // 杨高北路, 金京路
    {363, 364, 3},      // 金京路, 申江路
    {364, 365, 3},      // 申江路, 金海路
    {253, 365, 3},      // 金海路, 金海路
    {366, 367, 3},      // 金运路, 金沙
    {367, 368, 3},      // 金沙, 江西路
    {368, 369, 3},      // 江西路, 丰庄
    {369, 370, 3},      // 丰庄, 祁连山南路
    {370, 371, 3},      // 祁连山南路, 真北路
    {371, 372, 3},      // 真北路, 大渡河路
    {372, 373, 3},      // 大渡河路, 金沙江路
    {373, 374, 3},      // 金沙江路, 隆德路
    {66, 373, 3},       // 金沙江路, 金沙江路
    {92, 373, 3},       // 金沙江路, 金沙江路
    {374, 375, 3},      // 隆德路, 武宁路
    {316, 374, 3},      // 隆德路, 隆德路
    {375, 376, 3},      // 武宁路, 长寿路
    {376, 377, 3},      // 长寿路, 江宁路
    {176, 376, 3},      // 长寿路, 长寿路
    {377, 378, 3},      // 江宁路, 汉中路
    {378, 379, 3},      // 汉中路, 自然博物馆
    {14, 378, 3},       // 汉中路, 汉中路
    {349, 378, 3},      // 汉中路, 汉中路
    {379, 380, 3},      // 自然博物馆, 南京西路
    {380, 381, 3},      // 南京西路, 淮海中路
    {38, 380, 3},       // 南京西路, 南京西路
    {348, 380, 3},      // 南京西路, 南京西路
    {381, 382, 3},      // 淮海中路, 一大会址·新天地
    {382, 383, 3},      // 一大会址·新天地, 马当路
    {272, 382, 3},      // 一大会址·新天地, 一大会址·新天地
    {383, 384, 3},      // 马当路, 世博会博物馆
    {242, 383, 3},      // 马当路, 马当路
    {384, 385, 3},      // 世博会博物馆, 世博大道
    {385, 386, 3},      // 世博大道, 长清路
    {386, 387, 3},      // 长清路, 成山路
    {184, 386, 3},      // 长清路, 长清路
    {387, 388, 3},      // 成山路, 东明路
    {388, 389, 3},      // 东明路, 华鹏路
    {137, 388, 3},      // 东明路, 东明路
    {389, 390, 3},      // 华鹏路, 下南路
    {390, 391, 3},      // 下南路, 北蔡
    {391, 392, 3},      // 北蔡, 陈春路
    {392, 393, 3},      // 陈春路, 莲溪路
    {393, 394, 3},      // 莲溪路, 华夏中路
    {394, 395, 3},      // 华夏中路, 中科路
    {395, 396, 3},      // 中科路, 学林路
    {396, 397, 3},      // 学林路, 张江路
    {398, 399, 3},      // 封浜, 乐秀路
    {399, 400, 3},      // 乐秀路, 临洮路
    {400, 401, 3},      // 临洮路, 嘉怡路
    {401, 402, 3},      // 嘉怡路, 定边路
    {402, 403, 3},      // 定边路, 真新新村
    {403, 404, 3},      // 真新新村, 真光路
    {404, 405, 3},      // 真光路, 铜川路
    {405, 406, 3},      // 铜川路, 真如
    {406, 407, 3},      // 真如, 中宁路
    {313, 406, 3},      // 真如, 真如
    {407, 408, 3},      // 中宁路, 曹杨路
    {408, 409, 3},      // 曹杨路, 武宁路
    {67, 408, 3},       // 曹杨路, 曹杨路
    {93, 408, 3},       // 曹杨路, 曹杨路
    {315, 408, 3},      // 曹杨路, 曹杨路
    {409, 410, 3},      // 武宁路, 武定路
    {375, 409, 3},      // 武宁路, 武宁路
    {410, 411, 3},      // 武定路, 静安寺
    {411, 412, 3},      // 静安寺, 一大会址•黄陂南路
    {37, 411, 3},       // 静安寺, 静安寺
    {178, 411, 3},      // 静安寺, 静安寺
    {412, 413, 3},      // 一大会址•黄陂南路, 大世界
    {413, 414, 3},      // 大世界, 豫园
    {206, 413, 3},      // 大世界, 大世界
    {414, 415, 3},      // 豫园, 陆家嘴
    {274, 414, 3},      // 豫园, 豫园
    {415, 416, 3},      // 陆家嘴, 浦东南路
    {41, 415, 3},       // 陆家嘴, 陆家嘴
    {416, 417, 3},      // 浦东南路, 浦东大道
    {417, 418, 3},      // 浦东大道, 源深路
    {102, 417, 3},      // 浦东大道, 浦东大道
    {418, 419, 3},      // 源深路, 昌邑路
    {419, 420, 3},      // 昌邑路, 歇浦路
    {420, 421, 3},      // 歇浦路, 云山路
    {421, 422, 3},      // 云山路, 蓝天路
    {148, 421, 3},      // 云山路, 云山路
    {422, 423, 3},      // 蓝天路, 黄杨路
    {249, 422, 3},      // 蓝天路, 蓝天路
    {423, 424, 3},      // 黄杨路, 云顺路
    {424, 425, 3},      // 云顺路, 浦东足球场
    {425, 426, 3},      // 浦东足球场, 金粤路
    {426, 427, 3},      // 金粤路, 桂桥路
    {428, 429, 3},      // 紫竹高新区, 永德路
    {429, 430, 3},      // 永德路, 元江路
    {430, 431, 3},      // 元江路, 双柏路
    {431, 432, 3},      // 双柏路, 曙建路
    {432, 433, 3},      // 曙建路, 景西路
    {433, 434, 3},      // 景西路, 虹梅南路
    {434, 435, 3},      // 虹梅南路, 华泾西
    {435, 436, 3},      // 华泾西, 朱梅路
    {436, 437, 3},      // 朱梅路, 罗秀路
    {437, 438, 3},      // 罗秀路, 华东理工大学
    {438, 439, 3},      // 华东理工大学, 上海南站
    {439, 440, 3},      // 上海南站, 桂林公园
    {4, 439, 3},        // 上海南站, 上海南站
    {58, 439, 3},       // 上海南站, 上海南站
    {440, 441, 3},      // 桂林公园, 桂林路
    {340, 440, 3},      // 桂林公园, 桂林公园
    {441, 442, 3},      // 桂林路, 吴中路
    {236, 441, 3},      // 桂林路, 桂林路
    {442, 443, 3},      // 吴中路, 姚虹路
    {443, 444, 3},      // 姚虹路, 红宝石路
    {444, 445, 3},      // 红宝石路, 娄山关路
    {445, 446, 3},      // 娄山关路, 长风公园
    {34, 445, 3},       // 娄山关路, 娄山关路
    {446, 447, 3},      // 长风公园, 大渡河路
    {447, 448, 3},      // 大渡河路, 梅岭北路
    {372, 447, 3},      // 大渡河路, 大渡河路
    {448, 449, 3},      // 梅岭北路, 铜川路
    {449, 450, 3},      // 铜川路, 上海西站
    {405, 449, 3},      // 铜川路, 铜川路
    {450, 451, 3},      // 上海西站, 武威东路
    {312, 450, 3},      // 上海西站, 上海西站
    {451, 452, 3},      // 武威东路, 古浪路
    {452, 453, 3},      // 古浪路, 祁安路
    {453, 454, 3},      // 祁安路, 南大路
    {454, 455, 3},      // 南大路, 丰翔路
    {455, 456, 3},      // 丰翔路, 锦秋路
    {456, 457, 3},      // 锦秋路, 顾村公园
    {164, 457, 3},      // 顾村公园, 顾村公园
    {458, 459, 3},      // 龙阳路, 华夏中路
    {46, 458, 3},       // 龙阳路, 龙阳路
    {191, 458, 3},      // 龙阳路, 龙阳路
    {459, 460, 3},      // 华夏中路, 罗山路
    {394, 459, 3},      // 华夏中路, 华夏中路
    {460, 461, 3},      // 罗山路, 周浦东
    {330, 460, 3},      // 罗山路, 罗山路
    {461, 462, 3},      // 周浦东, 鹤沙航城
    {462, 463, 3},      // 鹤沙航城, 航头东
    {463, 464, 3},      // 航头东, 新场
    {464, 465, 3},      // 新场, 野生动物园
    {465, 466, 3},      // 野生动物园, 惠南
    {466, 467, 3},      // 惠南, 惠南东
    {467, 468, 3},      // 惠南东, 书院
    {468, 469, 3},      // 书院, 临港大道
    {469, 470, 3},      // 临港大道, 滴水湖
    {471, 472, 3},      // 虹桥火车站, 诸光路
    {29, 471, 3},       // 虹桥火车站, 虹桥火车站
    {260, 471, 3},      // 虹桥火车站, 虹桥火车站
    {472, 473, 3},      // 诸光路, 蟠龙路
    {473, 474, 3},      // 蟠龙路, 徐盈路
    {474, 475, 3},      // 徐盈路, 徐泾北城
    {475, 476, 3},      // 徐泾北城, 嘉松中路
    {476, 477, 3},      // 嘉松中路, 赵巷
    {477, 478, 3},      // 赵巷, 汇金路
    {478, 479, 3},      // 汇金路, 青浦新城
    {479, 480, 3},      // 青浦新城, 漕盈路
    {480, 481, 3},      // 漕盈路, 淀山湖大道
    {481, 482, 3},      // 淀山湖大道, 朱家角
    {482, 483, 3},      // 朱家角, 东方绿舟
    {484, 485, 3},      // 航头, 下沙
    {485, 486, 3},      // 下沙, 鹤涛路
    {486, 487, 3},      // 鹤涛路, 沈梅路
    {487, 488, 3},      // 沈梅路, 繁荣路
    {488, 489, 3},      // 繁荣路, 周浦
    {489, 490, 3},      // 周浦, 康桥
    {490, 491, 3},      // 康桥, 御桥
    {491, 492, 3},      // 御桥, 莲溪路
    {329, 491, 3},      // 御桥, 御桥
    {492, 493, 3},      // 莲溪路, 北中路
    {393, 492, 3},      // 莲溪路, 莲溪路
    {493, 494, 3},      // 北中路, 芳芯路
    {494, 495, 3},      // 芳芯路, 龙阳路
    {495, 496, 3},      // 龙阳路, 迎春路
    {46, 495, 3},       // 龙阳路, 龙阳路
    {191, 495, 3},      // 龙阳路, 龙阳路
    {458, 495, 3},      // 龙阳路, 龙阳路
    {496, 497, 3},      // 迎春路, 杨高中路
    {497, 498, 3},      // 杨高中路, 民生路
    {247, 497, 3},      // 杨高中路, 杨高中路
    {498, 499, 3},      // 民生路, 昌邑路
    {145, 498, 3},      // 民生路, 民生路
    {499, 500, 3},      // 昌邑路, 丹阳路
    {419, 499, 3},      // 昌邑路, 昌邑路
    {500, 501, 3},      // 丹阳路, 平凉路
    {501, 502, 3},      // 平凉路, 江浦公园
    {502, 503, 3},      // 江浦公园, 江浦路
    {355, 502, 3},      // 江浦公园, 江浦公园
    {503, 504, 3},      // 江浦路, 抚顺路
    {215, 503, 3},      // 江浦路, 江浦路
    {504, 505, 3},      // 抚顺路, 国权路
    {505, 506, 3},      // 国权路, 复旦大学
    {282, 505, 3},      // 国权路, 国权路
    {506, 507, 3},      // 复旦大学, 上海财经大学
    {507, 508, 3},      // 上海财经大学, 殷高路
    {508, 509, 3},      // 殷高路, 长江南路
    {78, 509, 3},       // 长江南路, 长江南路
    {510, 511, 3},      // 沈杜公路, 三鲁公路
    {193, 510, 3},      // 沈杜公路, 沈杜公路
    {511, 512, 3},      // 三鲁公路, 闵瑞路
    {512, 513, 3},      // 闵瑞路, 浦航路
    {513, 514, 3},      // 浦航路, 东城一路
    {514, 515, 3},      // 东城一路, 汇臻路
};

// 结构体定义节点
struct Node {
    int dest;
    int weight;
    struct Node* next;
};

// 结构体定义邻接列表
struct List {
    struct Node* head;
};

int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void printPath(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%s", lines[j]);
        return;
    }
    printPath(parent, parent[j]);
    printf("->%s", lines[j]);
}

void dijkstra(struct List* adjList, int src, int dest) {
    int dist[V];
    bool sptSet[V];
    int parent[V];

    for (int i = 0; i < V; i++) {
        parent[src] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        struct Node* neighbor = adjList[u].head;
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
        printf("No path from %d to %d\n", src, dest);
    } else {
        printf("Shortest path from %d to %d with distance %d: ", src, dest, dist[dest]);
        printPath(parent, dest);
        printf("\n");
    }
}

// 添加边到邻接列表
void addEdge(struct List* adjList, int src, int dest, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = adjList[src].head;
    adjList[src].head = newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = src;
    newNode->weight = weight;
    newNode->next = adjList[dest].head;
    adjList[dest].head = newNode;
}

int main() {
    struct List adjList[V];

    // 初始化每个邻接列表
    for (int i = 0; i < V; i++) {
        adjList[i].head = NULL;
    }

    for(int i = 0; i < 627; i++){
        addEdge(adjList, edges[i][0], edges[i][1], edges[i][2]);
    }


    dijkstra(adjList, 0, 229);  // 从第0个地铁站到第4个地铁站的最短路径

    return 0;
}
