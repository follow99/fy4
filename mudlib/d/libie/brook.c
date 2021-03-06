 // Room: brook.c --- by MapMaker
#include <ansi.h> 
inherit ROOM; 
void create()
{
        set("short", "梅林竹溪"); 
        set("long", @LONG
青梅子、黄竹马，赤脚溪里捉鱼虾，手拉手儿打滚滚。走在这遍地
落叶小溪的梅林，一幕幕儿时的快乐似乎浮上眼前。不禁使你伫立良久，
一到晚上，小溪在星光下看来，就象是条镶满宝石的蓝色天带。但眼前
溪流似血，尸骸遍地，就只有一个断腿老人斜靠在树边微微呻吟。
LONG); 
        set("type","forest");
        set("exits",([
        "north":__DIR__"woods1",
    "southwest":__DIR__"stoneroad4",
        ]) ); 
        set("objects", ([
                __DIR__"npc/master": 1,
        ]) );
        set("outdoors", "libie");
        set("coor/x",70);
        set("coor/y",210);
        set("coor/z",0); 
        setup();
} 
int valid_leave(object me, string dir)
{
        object env, ob; 
        env = this_object();
        ob = present("master yichen", env);
        if(!objectp(ob)) return 1;
        if(!living(ob)) return 1;
        if(me->query_temp("libie/离别钩_准备送饭")) return 1;
        if(me->query("libie/离别钩二")) return 1;
        if(me->query("libie/离别钩_送饭"))
        {
                me->set("libie/离别钩二",1);
        return notify_fail(HIY "蓝一尘叹道：杨夫人有志如此，令人叹服，如今须尽快寻回杨铮才是。
"+ RANK_D->query_respect(me) +"，此地有蓝某照看，料无大碍，你可速去寻觅杨铮，看能否助其一臂\n之力，找回劫镖案的真凶。\n"NOR);
   }
        
                
        if(me->query_temp("libie/离别钩_送信成功")&&dir=="north")
        {
        if(!present("hot rice",me))
        if(present("cold rice",me))
            return notify_fail(YEL "蓝一尘皱一皱眉毛：残羹冷觯如何下咽？\n"NOR);
        else return notify_fail(HIY"蓝一尘皱一皱眉毛：没有饭怎么成？\n"NOR);
        if(!present("hot greens",me))
        if(present("cold greens",me))
                return notify_fail(YEL "蓝一尘皱一皱眉毛：残羹冷觯如何下咽？\n"NOR);
        else return notify_fail(YEL "蓝一尘皱一皱眉毛：没有菜怎么成？\n"NOR);
        if(!present("hot soup",me))
        if(present("cold soup",me))
            return notify_fail(YEL "蓝一尘皱一皱眉毛：残羹冷觯如何下咽？\n"NOR);
        else return notify_fail(YEL "蓝一尘皱一皱眉毛：没有汤怎么成？\n"NOR);
        me->set_temp("libie/离别钩_准备送饭",1);
        return notify_fail(HIY "蓝一尘打量了一下你提着的饭菜，颔首微微笑道：好孩子，去罢。\n"NOR);
        } 
    if( !me->query_temp("libie/离别钩_回头")){
        if( !(me->query("libie/离别钩_送信")) && (dir == "north")){ 
                me->set_temp("libie/离别钩_回头", 1);
                message_vision( HIR "\n蓝一尘从血泊中挣扎着拦住$N的去路，弹剑狂笑道：
蓝某人但有一口气在，绝不让尔等贼子从此而过！\n"NOR, me); 
                        return notify_fail("");
                }
    } else {
        if( !(me->query("libie/离别钩_送信")) && (dir == "north")){
        add_action("do_answer", "answer");
        message_vision(HIR "\n蓝一尘挡在路中，冷冷地盯着$N，一字一字道：滚，还是不滚？(answer yes or no)\n"NOR, me);
        return notify_fail("");
        }
        }
        return 1;
}  
                 
int do_answer(string arg)
{
    object ob, me;
    ob = present("master yichen", environment(this_player()));
    me = this_player();
    if(objectp(ob))
    if(living(ob))
    if( arg == "yes" )
    {
        message_vision(YEL "蓝一尘点了点头，说道：是非之地，你还是滚得越远越好。\n"NOR, this_player());
        return 1;
    }
    else if( arg == "no" )
    {
        message_vision(HIR "蓝一尘哼了一声，说道：不滚？那就受死吧！\n"NOR, this_player());
        ob->kill_ob(this_player());
        me->set_temp("libie/离别钩一", 0);
        return 1;
    }
    else
    return 0;
}   
