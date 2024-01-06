#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

const char station_pinyin[407][2][45] = {
    {"AT", "安亭"},
    {"BC", "北蔡"},
    {"BQ", "北桥"},
    {"CL", "曹路"},
    {"CS", "川沙"},
    {"DJ", "洞泾"},
    {"FB", "封浜"},
    {"FZ", "丰庄"},
    {"GQ", "高桥"},
    {"HN", "惠南"},
    {"HQ", "花桥"},
    {"HT", "后滩"},
    {"HT", "航头"},
    {"JQ", "金桥"},
    {"JT", "九亭"},
    {"KQ", "康桥"},
    {"LH", "刘行"},
    {"LH", "龙华"},
    {"ML", "马陆"},
    {"NX", "南翔"},
    {"QB", "七宝"},
    {"SJ", "泗泾"},
    {"SL", "三林"},
    {"SS", "佘山"},
    {"SY", "书院"},
    {"TQ", "塘桥"},
    {"TZ", "唐镇"},
    {"XC", "新场"},
    {"XD", "西渡"},
    {"XS", "下沙"},
    {"XT", "萧塘"},
    {"XZ", "莘庄"},
    {"YQ", "御桥"},
    {"YY", "豫园"},
    {"ZP", "周浦"},
    {"ZQ", "颛桥"},
    {"ZR", "真如"},
    {"ZX", "赵巷"},
    {"AGL", "爱国路"},
    {"BSL", "宝山路"},
    {"BXJ", "北新泾"},
    {"BXL", "博兴路"},
    {"BYL", "宝杨路"},
    {"BYL", "白银路"},
    {"BZL", "北中路"},
    {"CBL", "漕宝路"},
    {"CCL", "陈春路"},
    {"CFL", "赤峰路"},
    {"CPL", "昌平路"},
    {"CQL", "长清路"},
    {"CSL", "常熟路"},
    {"CSL", "成山路"},
    {"CSL", "春申路"},
    {"CSL", "长寿路"},
    {"CXL", "漕溪路"},
    {"CYL", "昌邑路"},
    {"CYL", "曹杨路"},
    {"CYL", "漕盈路"},
    {"CZL", "场中路"},
    {"DAL", "东安路"},
    {"DBL", "定边路"},
    {"DBS", "大柏树"},
    {"DCL", "东川路"},
    {"DCL", "东昌路"},
    {"DCZ", "大场镇"},
    {"DJL", "东靖路"},
    {"DLL", "东兰路"},
    {"DLL", "东陆路"},
    {"DLL", "大连路"},
    {"DML", "东明路"},
    {"DPL", "德平路"},
    {"DPQ", "打浦桥"},
    {"DSH", "滴水湖"},
    {"DSJ", "大世界"},
    {"DSN", "迪士尼"},
    {"DYL", "丹阳路"},
    {"FDL", "芳甸路"},
    {"FHL", "芳华路"},
    {"FJL", "富锦路"},
    {"FQL", "枫桥路"},
    {"FRL", "繁荣路"},
    {"FSL", "抚顺路"},
    {"FXD", "复兴岛"},
    {"FXL", "丰翔路"},
    {"FXL", "芳芯路"},
    {"GCL", "港城路"},
    {"GDL", "顾戴路"},
    {"GFL", "国帆路"},
    {"GKL", "共康路"},
    {"GLL", "古浪路"},
    {"GLL", "广兰路"},
    {"GLL", "桂林路"},
    {"GML", "光明路"},
    {"GQL", "国权路"},
    {"GQL", "桂桥路"},
    {"GQL", "高青路"},
    {"GQX", "高桥西"},
    {"GTL", "顾唐路"},
    {"HCL", "合川路"},
    {"HCL", "虹漕路"},
    {"HJL", "汇金路"},
    {"HJL", "航津路"},
    {"HJX", "华泾西"},
    {"HLL", "呼兰路"},
    {"HLL", "海伦路"},
    {"HML", "花木路"},
    {"HML", "虹梅路"},
    {"HND", "惠南东"},
    {"HNL", "华宁路"},
    {"HPL", "华鹏路"},
    {"HQL", "虹桥路"},
    {"HSL", "虹莘路"},
    {"HSL", "衡山路"},
    {"HTD", "航头东"},
    {"HTL", "鹤涛路"},
    {"HXL", "黄兴路"},
    {"HYL", "黄杨路"},
    {"HZL", "汇臻路"},
    {"HZL", "汉中路"},
    {"HZL", "航中路"},
    {"JAS", "静安寺"},
    {"JCL", "剑川路"},
    {"JCL", "江川路"},
    {"JDB", "嘉定北"},
    {"JDX", "嘉定西"},
    {"JFL", "巨峰路"},
    {"JHH", "金海湖"},
    {"JHL", "金海路"},
    {"JJL", "金京路"},
    {"JJL", "金吉路"},
    {"JKL", "金科路"},
    {"JLL", "基隆路"},
    {"JNL", "江宁路"},
    {"JPL", "江浦路"},
    {"JPL", "金平路"},
    {"JQL", "金桥路"},
    {"JQL", "锦秋路"},
    {"JSL", "嘉善路"},
    {"JSL", "江苏路"},
    {"JWZ", "江湾镇"},
    {"JXL", "景西路"},
    {"JXL", "锦绣路"},
    {"JYL", "嘉怡路"},
    {"JYL", "江月路"},
    {"JYL", "金粤路"},
    {"JYL", "金运路"},
    {"LBL", "鲁班路"},
    {"LCL", "蓝村路"},
    {"LCL", "隆昌路"},
    {"LCL", "龙漕路"},
    {"LDL", "隆德路"},
    {"LGL", "岚皋路"},
    {"LHL", "联航路"},
    {"LHL", "芦恒路"},
    {"LHL", "莲花路"},
    {"LJZ", "陆家嘴"},
    {"LKL", "凌空路"},
    {"LPL", "临平路"},
    {"LSL", "罗山路"},
    {"LTL", "临洮路"},
    {"LTL", "蓝天路"},
    {"LXL", "乐秀路"},
    {"LXL", "罗秀路"},
    {"LXL", "莲溪路"},
    {"LXL", "龙溪路"},
    {"LXM", "老西门"},
    {"LYL", "龙耀路"},
    {"LYL", "龙阳路"},
    {"LZY", "李子园"},
    {"MDL", "马当路"},
    {"MLH", "美兰湖"},
    {"MLL", "民雷路"},
    {"MRL", "闵瑞路"},
    {"MSL", "民生路"},
    {"NCL", "南陈路"},
    {"NDL", "南大路"},
    {"NGL", "宁国路"},
    {"NJL", "嫩江路"},
    {"PDL", "浦电路"},
    {"PGL", "潘广路"},
    {"PHL", "浦航路"},
    {"PJZ", "浦江镇"},
    {"PLL", "平凉路"},
    {"PLL", "蟠龙路"},
    {"PSL", "浦三路"},
    {"QAL", "祁安路"},
    {"QFL", "曲阜路"},
    {"QHL", "祁华路"},
    {"QSL", "七莘路"},
    {"QYL", "曲阳路"},
    {"SBL", "双柏路"},
    {"SBL", "淞滨路"},
    {"SCL", "商城路"},
    {"SCL", "水产路"},
    {"SCL", "水城路"},
    {"SDL", "上大路"},
    {"SFL", "淞发路"},
    {"SGL", "市光路"},
    {"SHL", "淞虹路"},
    {"SJL", "双江路"},
    {"SJL", "曙建路"},
    {"SJL", "申江路"},
    {"SLD", "三林东"},
    {"SLL", "石龙路"},
    {"SML", "三门路"},
    {"SML", "沈梅路"},
    {"SNL", "上南路"},
    {"SPL", "四平路"},
    {"SYL", "宋园路"},
    {"TCL", "铜川路"},
    {"TLL", "铁力路"},
    {"TLQ", "提篮桥"},
    {"TTL", "天潼路"},
    {"WDL", "武定路"},
    {"WHL", "外环路"},
    {"WJC", "五角场"},
    {"WJL", "文井路"},
    {"WLL", "五莲路"},
    {"WNL", "威宁路"},
    {"WNL", "武宁路"},
    {"WSL", "汶水路"},
    {"WWL", "武威路"},
    {"WYL", "望园路"},
    {"WZL", "吴中路"},
    {"XCL", "新村路"},
    {"XJD", "徐泾东"},
    {"XJH", "徐家汇"},
    {"XLL", "学林路"},
    {"XNL", "下南路"},
    {"XNM", "小南门"},
    {"XPL", "歇浦路"},
    {"XYL", "徐盈路"},
    {"XYL", "秀沿路"},
    {"XYL", "翔殷路"},
    {"XZL", "新闸路"},
    {"XZL", "星中路"},
    {"XZL", "行知路"},
    {"YCL", "延长路"},
    {"YCL", "迎春路"},
    {"YDL", "永德路"},
    {"YDL", "银都路"},
    {"YGL", "殷高路"},
    {"YHL", "姚虹路"},
    {"YHL", "耀华路"},
    {"YJL", "云锦路"},
    {"YJL", "元江路"},
    {"YLL", "伊犁路"},
    {"YSL", "云山路"},
    {"YSL", "云顺路"},
    {"YSL", "宜山路"},
    {"YSL", "源深路"},
    {"YTL", "云台路"},
    {"YYL", "友谊路"},
    {"ZBC", "醉白池"},
    {"ZBL", "真北路"},
    {"ZCL", "中春路"},
    {"ZFL", "兆丰路"},
    {"ZGL", "真光路"},
    {"ZGL", "诸光路"},
    {"ZHB", "张华浜"},
    {"ZHL", "洲海路"},
    {"ZJJ", "朱家角"},
    {"ZJL", "张江路"},
    {"ZKL", "中科路"},
    {"ZML", "朱梅路"},
    {"ZNL", "中宁路"},
    {"ZPD", "周浦东"},
    {"ZPL", "镇坪路"},
    {"ZTL", "中潭路"},
    {"ZTL", "紫藤路"},
    {"ZXL", "中兴路"},
    {"ASXC", "鞍山新村"},
    {"BAGL", "宝安公路"},
    {"BYJL", "北洋泾路"},
    {"CFGY", "长风公园"},
    {"CJDL", "昌吉东路"},
    {"CJNL", "长江南路"},
    {"CXGL", "陈翔公路"},
    {"CXZL", "创新中路"},
    {"DBXL", "东宝兴路"},
    {"DCYL", "东城一路"},
    {"DDHL", "大渡河路"},
    {"DFLZ", "东方绿舟"},
    {"DHSL", "大华三路"},
    {"DMQL", "大木桥路"},
    {"FDDX", "复旦大学"},
    {"FPDD", "奉浦大道"},
    {"FXXC", "奉贤新城"},
    {"GCGY", "顾村公园"},
    {"GFXC", "共富新村"},
    {"GKXL", "高科西路"},
    {"GLGY", "桂林公园"},
    {"HBSL", "红宝石路"},
    {"HCDL", "环城东路"},
    {"HHZL", "淮海中路"},
    {"HMNL", "虹梅南路"},
    {"HSHC", "鹤沙航城"},
    {"HTSL", "海天三路"},
    {"HXDL", "华夏东路"},
    {"HXGY", "黄兴公园"},
    {"HXXL", "华夏西路"},
    {"HXZL", "华夏中路"},
    {"JDXC", "嘉定新城"},
    {"JJLY", "锦江乐园"},
    {"JPGY", "江浦公园"},
    {"JSJL", "金沙江路"},
    {"JSZL", "嘉松中路"},
    {"JTDX", "交通大学"},
    {"JYBL", "江杨北路"},
    {"KXGL", "康新公路"},
    {"LBXC", "龙柏新村"},
    {"LGDD", "临港大道"},
    {"LHZL", "龙华中路"},
    {"LJBL", "陆家浜路"},
    {"LNXC", "罗南新村"},
    {"LSGL", "娄山关路"},
    {"LYNL", "灵岩南路"},
    {"LYXC", "临沂新村"},
    {"LZXC", "凌兆新村"},
    {"MLBL", "梅岭北路"},
    {"NJDL", "南京东路"},
    {"NJXL", "南京西路"},
    {"NPDQ", "南浦大桥"},
    {"PDDD", "浦东大道"},
    {"PDNL", "浦东南路"},
    {"PPXC", "彭浦新村"},
    {"QLSL", "祁连山路"},
    {"QPXC", "青浦新城"},
    {"RMGC", "人民广场"},
    {"SBDD", "世博大道"},
    {"SCBL", "四川北路"},
    {"SDGL", "沈杜公路"},
    {"SHDX", "上海大学"},
    {"SHNZ", "上海南站"},
    {"SHXZ", "上海西站"},
    {"SJDD", "世纪大道"},
    {"SJGY", "世纪公园"},
    {"SJNZ", "松江南站"},
    {"SJXC", "松江新城"},
    {"SLGL", "三鲁公路"},
    {"SXNL", "陕西南路"},
    {"TEZL", "台儿庄路"},
    {"THXC", "通河新村"},
    {"TJDX", "同济大学"},
    {"TPXC", "桃浦新村"},
    {"WWDL", "武威东路"},
    {"WZDD", "五洲大道"},
    {"XJBC", "徐泾北城"},
    {"XJWC", "新江湾城"},
    {"XZBL", "西藏北路"},
    {"XZNL", "西藏南路"},
    {"YAXL", "延安西路"},
    {"YDDD", "远东大道"},
    {"YDXC", "邮电新村"},
    {"YGBL", "杨高北路"},
    {"YGDL", "殷高东路"},
    {"YGNL", "杨高南路"},
    {"YGXL", "殷高西路"},
    {"YGZL", "杨高中路"},
    {"YJZL", "延吉中路"},
    {"YSPL", "杨树浦路"},
    {"YYXL", "友谊西路"},
    {"ZJBL", "肇嘉浜路"},
    {"ZJGK", "张江高科"},
    {"ZSBL", "中山北路"},
    {"ZSGY", "中山公园"},
    {"ZXXC", "真新新村"},
    {"DSHDD", "淀山湖大道"},
    {"HKZQC", "虹口足球场"},
    {"HQHCZ", "虹桥火车站"},
    {"JSJXL", "金沙江西路"},
    {"JWTYC", "江湾体育场"},
    {"MHKFQ", "闵行开发区"},
    {"PDZQC", "浦东足球场"},
    {"QLSNL", "祁连山南路"},
    {"SHDWY", "上海动物园"},
    {"SHHCZ", "上海火车站"},
    {"SHKJG", "上海科技馆"},
    {"SHMXC", "上海马戏城"},
    {"SHQCC", "上海汽车城"},
    {"SHSCC", "上海赛车场"},
    {"SHTSG", "上海图书馆"},
    {"SHTYC", "上海体育场"},
    {"SHTYG", "上海体育馆"},
    {"SHYYG", "上海游泳馆"},
    {"SJDXC", "松江大学城"},
    {"YSCSL", "杨思成山路"},
    {"YSDWY", "野生动物园"},
    {"ZHYSG", "中华艺术宫"},
    {"ZRBWG", "自然博物馆"},
    {"ZZGXQ", "紫竹高新区"},
    {"CHJKFQ", "漕河泾开发区"},
    {"DFTYZX", "东方体育中心"},
    {"GJKYZX", "国际客运中心"},
    {"HDLGDX", "华东理工大学"},
    {"PDGJJC", "浦东国际机场"},
    {"SBHBWG", "世博会博物馆"},
    {"SHCJDX", "上海财经大学"},
    {"SJTYZX", "松江体育中心"},
    {"YSTYZX", "源深体育中心"},
    {"HQ1HHZL", "虹桥1号航站楼"},
    {"HQ2HHZL", "虹桥2号航站楼"},
    {"YDHZXTD", "一大会址·新天地"},
    {"SHETYXZX", "上海儿童医学中心"},
    {"WGQBSQBZ", "外高桥保税区北站"},
    {"WGQBSQNZ", "外高桥保税区南站"},
    {"YDHZHBNL", "一大会址·黄陂南路"},

};

bool pinyin(const char *src, char *target) {
    int idx = 0;

    int m = strlen(src), n = strlen(target);

    if (n == 0 || m == 0 || n > m) {
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

int main() {
    char input[10];

    memset(input, '\0', 10);
    char c;
    int cnt = 0;
    while (1) {
        c = cin.get();
        if (c != '\n') {
            input[cnt++] = c;

        } else {
            vector<int> ret;
            for (int i = 0; i < 407; i++) {
                if (pinyin(station_pinyin[i][0], input)) {
                    ret.push_back(i);
                }
            }

            for (int i = 0; i < ret.size(); i++) {
                cout << station_pinyin[ret[i]][1] << ", ";
            }
            cout << endl;

            memset(input, '\0', 10);
            cnt = 0;
        }
    }

    return 0;
}