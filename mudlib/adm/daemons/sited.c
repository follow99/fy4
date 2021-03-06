#include <ansi.h>
inherit F_DBASE;

mapping valid_login = ([
                "hxsd":         ({ "61.", "171.", "12.", "5." }),
                "keinxin":      ({ "218.", "211.", "210.", "202.", "10.","219" }),
                "wuye":         ({ "219.", "218.", "61." }),
                "haoren":       ({ "127.0.1.9" }),
                "sunyf":        ({ "127.0.1.9" }),
                "robber":       ({ "127.0.1.9" }),
                "winter":       ({ "127.0.1.9" }),
                "chk":          ({ "61.", "211.", "202.", "10.", "218." }),
                "tanggw":       ({ "127.0.1.9" }),
                "huoying":      ({ "127.0.1.9" }),
                "king":         ({ "127.0.1.9" }),
                "yao":          ({ "127.0.1.9" }),
                "ahunter":      ({ "127.0.1.9" }),
                "bbb":          ({ "127.0.1.9" }),
                "bobo":         ({ "127.0.1.9" }),
                "cht":          ({ "127.0.1.9" }),
                "cool":         ({ "127.0.1.9" }),
                "darken":       ({ "127.0.1.9" }),
                "emnil":        ({ "127.0.1.9" }),
                "hunthu":       ({ "127.0.1.9" }),
                "iceland":      ({ "127.0.1.9" }),
                "mingy":        ({ "127.0.1.9" }),
                "jpei":         ({ "127.0.1.9" }),
                "keepon":       ({ "127.0.1.9" }),
                "lius":         ({ "127.0.1.9" }),
                "lmoon":        ({ "127.0.1.9" }),
                "look":         ({ "127.0.1.9" }),
                "lxue":         ({ "127.0.1.9" }),
                "numa":         ({ "127.0.1.9" }),
                "river":        ({ "127.0.1.9" }),
                "snowman":      ({ "127.0.1.9" }),
                "tiantian":     ({ "127.0.1.9" }),
                "tomy":         ({ "127.0.1.9" }),
                "shaer":        ({ "127.0.1.9" }),
                "xiaolee":      ({ "127.0.1.9" }),
                "xiaoyao":      ({ "127.0.1.9" }),
                "guoo":         ({ "127.0.1.9" }),
                "yuj":          ({ "127.0.1.9" }),
                //河北巫师
                "ldf":          ({ "127.0.1.9" }),
                "night":        ({ "127.0.1.9" }),
                //秦皇岛
                "lanxin":       ({ "127.0.1.9" }),
                //山东泰安
                "ziqing":       ({ "127.0.1.9" }),
                "godhelpu":     ({ "127.0.1.9" }),
                //山东烟台
                "can":          ({ "127.0.1.9" }),
                "mouse":        ({ "127.0.1.9" }),
                //浙江
                "short":        ({ "127.0.1.9" }),
                "bluesky":      ({ "127.0.1.9" }),
                //贵州
                "jackyang":     ({ "127.0.1.9" }),
                "star":         ({ "127.0.1.9" }),
                ]);

int is_valid(string id, string ip)
{
        int i;

        if (ip == "127.0.0.1" || ip == "localhost") {
                if (wiz_level(id)) return 1;
                return 0;
        }
        if (undefinedp(valid_login[id])) {
                if (!wiz_level(id)) return 1;
                write("巫师必须有地址限制，请用 guest 登录通知天神。\n");
                destruct(this_object());
                return 0;
        }
        i = sizeof(valid_login[id]);
        while (i--) if (sscanf(ip, valid_login[id][i] + "%*s")) return 1;
        destruct(this_object());        // 自动摧毁自己，方便YUJIP改变刷新
        return 0;
}

mapping valid_multi = ([
                "":             0
                ]);

int is_multi(string id, string ip, string port)
{
        object *usr = filter_array(objects(), (: interactive :));
        string *site = keys(valid_multi);
        int i, login_cnt = 0;

        if (query(ip)) {
                write("您的地址刚有人登录，请等会再试。\n");
                return 1;
        }
        set(ip, 1);
        call_out("delete", 10, ip);
        usr = filter_array(usr, (: environment :));
        i = sizeof(usr);
        while (i--) if (usr[i]->query("id") != id && query_ip_number(usr[i]) == ip) login_cnt++;
        write("您的 IP 是：" HIW + ip + ":" + port + NOR "，此地址另有" + chinese_number(login_cnt)+"位玩家在线。\n");
        if (!login_cnt) return 0;
        i = sizeof(valid_multi);
        while (i--) if (sscanf(ip, site[i] + "%*s")) break;
        if (i < 0) {
                write("对不起，您目前的地址禁止多重登录，请与巫师联系。\n");
                return 1;
        }
        if (!(i = valid_multi[site[i]])) return 0;
        if (login_cnt < i) return 0;
        write("对不起，您目前的地址已到达人数限制，请与巫师联系。\n");
        return 1;
}
