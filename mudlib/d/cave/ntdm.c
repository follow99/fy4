 // Copyright (C) FengYun Workshop
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
inherit ROOM;
#include <ansi.h> 
void create()
{
        set("short", "南天东门");
        set("long", @LONG
一人多高的紫蘑菇一大片，这种植物的表皮极硬，而且特别
的粗糙。这条路几乎就是从蘑林中砍出来的，路面虽然不宽，但
可以看出造这路一定花了很大的功夫。
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"ntdl",
  "south" : __DIR__"dnj",
]));
        set("indoors", "cave");
        set("coor/x",-30);
        set("coor/y",-22);
        set("coor/z",-20);
//        set("objects", ([
     //   __DIR__"npc/fishseller": 1,
//      __DIR__"npc/fishbuyer": 1,
//                        ]) );
        setup(); 
}  
int valid_leave(object obj, string dir){
        object another;
        seteuid(getuid());
        
        message_vision( HIM "路行至此，紫蘑林飘荡着淡而幽香的雾障。。。。\n\n"NOR,obj);
        if(!obj->query_condition("mag_mushroom") && random(obj->query_skill("perception",1))<50){
                obj->apply_condition("mag_mushroom",random(20)+10);
                message_vision(HIM"$N不由地深吸了一口气。\n"NOR,obj);
        } else  message_vision( HIW"$N意随心动，急忙屏住呼吸。\n"NOR,obj);
        if(dir == "north" && !obj->query("vendetta/authority")){
                if (present("killer m", this_object()))
                {
                   another = present("killer m", this_object());
                        return notify_fail(another->name()+"闪身挡住了你的路。\n");
                } else if (random(10)>7) {
                        another = new(__DIR__"npc/killer_m");
                        another->move(environment(obj));
                        message_vision(HIB"路边黑影一闪!\n"NOR, obj);   
                        return notify_fail(another->name()+"喝道，什么人敢私闯青龙会，拿命来！\n");
                }
        }       
        return 1;
} 
