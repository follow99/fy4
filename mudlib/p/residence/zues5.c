#include <ansi.h>
#define X_COOR -20
#define Y_COOR 2040
#define Z_COOR 50
#define R_FLAG 18
#define OWNER "zues"
#define CLASS "财神庙"
inherit ROOM;
string cliff();
void create()
{
set("short", WHT"海滨"NOR);
set("long", @LONG
东南方是一片广阔的沙滩，海水(water)拍打着白色地沙滩(sand)，阳光照得
碧蓝的海水泛起了金光。海鸥在天上尽情地飞翔，鱼儿在碧波中欢快地跳跃，和
煦的海风吹得人软绵绵地，只想尽情享受这阳光、碧海、蓝天和沙滩。西北方是
一处断崖(cliff)，山上有一遗址，在金色的阳光下显得特别灿烂。时断时续的钟
声见证了这里无数个世纪的兴衰。
LONG
);
        set("exits", ([
	"east" : __DIR__"zues3",
]));
	set("objects", ([
       	]) );
       
          set("item_desc", ([
                "cliff" : (: cliff :),
                "断崖"  : (: cliff :),
                "sand"  : "白白的沙子下面似乎有些东西，可以搜寻(search)一下。\n",
                "沙滩"  : "白白的沙子下面似乎有些东西，可以搜寻(search)一下。\n",
                "water" : "眼前碧蓝的海水让你止不住想畅游(swim)一番。\n",
                "海水"  : "眼前碧蓝的海水让你止不住想畅游(swim)一番。\n",
        ]) );
        set("coor/x",X_COOR);
        set("coor/y",Y_COOR);
        set("coor/z",Z_COOR);
        set("room_flag",R_FLAG);
        set("owner", OWNER);
        set("class", CLASS);
        set("outdoors","residence");
        setup();
}
void init()
{
    add_action("do_swim", "swim");
    add_action("do_search","search");
}

string cliff(){
        object me;
        me = this_player();
        tell_object(me, "你注意到崖边的海水似乎比较浅，似乎可以下潜(dive)。\n");
        add_action("do_dive", "dive");
        return "";
} 
int do_dive(string arg){
        object me, room;
   	me = this_player();
        if(!arg || (arg != "down" && arg != "断崖"&& arg !="cliff")){
                return notify_fail("你要往哪里下潜？\n");
        }
        message_vision("$N看准了断崖下海水的深浅，”扑通“一声，扎进了水中。\n", me);
        room = find_object("/p/residence/zues6");
        if(!objectp(room)){
            room = load_object("/p/residence/zues6");
                }
                me->move("/p/residence/zues6");
        return 1;       
} 
int do_swim()
{
        object me;
        int wait;
        me = this_player();
        wait = 15;
        message_vision("$N看着蔚蓝的海水，禁不住脱光衣服，跳进水中畅游起来。\n",me);
        tell_object(me,"咸咸的海水让你全身异常舒坦。\n");
        remove_call_out("curehimup");
   call_out("curehimup", wait, me);
return 1;
}  

void curehimup(object me)
{
        int gin,kee,sen;
        if(!me) return;
        gin=(int)me->query("max_gin");
        kee=(int)me->query("max_kee");
        sen=(int)me->query("max_sen");
if( me && environment(me) == this_object())
        {
        message_vision("海水让$N的精气神恢复了。\n", me);
        me->set("eff_gin",gin);
        me->set("eff_kee",kee);
        me->set("eff_sen",sen);
        me->set("gin", gin);
        me->set("kee", kee);
        me->set("sen", sen);
        }
return;
}   

int do_search(string arg)
{
        object me, obj;
        me = this_player();
        if(!arg) {
            write("你要在哪里找东西？\n");
            return 1;
        }
        if( me->is_busy() ) {
            return notify_fail("你上一个动作还没有完成，不能搜索。\n");
        }
        if( arg == "sand" || arg == "沙滩"  ){
            if ( query("littlething") > 0 && !random(3) ) {
                        message_vision("$N蹲下身子，在沙滩里搜寻着，突然从沙里挖出个小玩意。\n",me);
                        obj = new("/d/baiyun/obj/littlething");
                        obj->move(environment(me));
                        add("littlething", -1);
            } else {
            message_vision("$N不耐烦的翻了半天，但什么都没有找到。\n",me);
            me->start_busy(2);
            }
        }
        return 1;
}

void reset()
{
        ::reset();
        set("littlething", 25);
} 