 // Room: yushijie1.c --- by MapMaker
inherit ROOM; 
void create()
{
        set("short", "白玉石阶"); 
        set("long", @LONG
这是条通往无垢山庄的白玉石阶,虽然看上去已历经久远,玉石阶梯已被行人走
的棱角皆无,但仍显得格外的庄重而肃静,碧绿色的瓦，在秋阳下闪动着弱翠般的光，
白石长阶从黄金般的高墙间穿过去，整个山庄就象是完全用珠宝黄金砌成的。四周
山林幽幽,空山无语,灿烂的阳光下，远处有一片辉煌雄伟的庄院，看来就像是神话
中的宫殿一样。
LONG); 
        //{{ --- by MapMaker
        set("type","road");
        set("exits",([
    "southdown":__DIR__"yushijie2",
        "north":__DIR__"damen",
        ]) );
        //}}
        set("outdoors", "taishan");
        set("coor/x",310);
        set("coor/y",2420);
        set("coor/z",150); 
        setup();
        replace_program(ROOM);
}   
