 // road0.c
// QCed and modified by TIE@FY2
inherit ROOM;
void create()
{
        set("short", "山中小路");
        set("long", @LONG
这里山色甚是凄凉，道路更本来已是苔藓土滑，崎岖难行到后来更是乱山峥
嵘，荒草没径。路边灌木丛生，每丛灌木上都长满了长达寸许的木刺，木刺上还
挂着各种颜色的布条。
LONG
        );
        set("exits", ([ 
  "eastup" : __DIR__"road1",
  "westdown" : __DIR__"road",
]));
        set("outdoors", "tieflag");
        set("coor/x",50);
        set("coor/y",2000);
        set("coor/z",10);
        setup();
        replace_program(ROOM);
}  
