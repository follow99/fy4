 // TIE@FY3 ALL RIGHTS RESERVED
inherit ROOM;
void create()
{
        set("short", "五乳峰");
        set("long", @LONG
过达摩洞，便可以到少室绝顶，这里是少室的西峰，山峰陡峭
许多少林僧人在此行功打座，山风阵阵，白云霭霭，对于修行之人
最是适合不过。
LONG
        );
        set("exits", ([ 
  "eastdown" : __DIR__"damo",
]));
        set("outdoors", "songshan");
        set("coor/x",-240);
        set("coor/y",420);
        set("coor/z",80);
        set("objects", ([
                __DIR__"npc/lama1" : 1,
       ]) );
        setup();
        replace_program(ROOM);
}
