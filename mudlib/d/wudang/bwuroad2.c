 inherit ROOM;
void create()
{
        set("short", "泥土路");
        set("long", @LONG
路的左右两边都是一望无际的庄稼地。顺此路再往前走，就是武
当山。顺眼望去，武当山并不高，也不是很雄伟。但满山松树，绿油
油的不时露出几个黄色的屋顶。给人一种宁静的感觉。
LONG
        );
        set("exits", ([ 
                "south" : __DIR__"xiaozhen",
                "north" : __DIR__"bwuroad1",
        ]));
        set("outdoors", "wudang");
        set("coor/x",100);
        set("coor/y",-20);
        set("coor/z",0);
        setup();
}
void init()
{
        add_action("do_go","go"); 
} 
int do_go()
{
if(random(2)){
this_player()->move(this_object());
return 1;
}
} 
