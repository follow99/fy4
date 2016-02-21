 inherit ROOM;
void create()
{
        set("short", "经楼");
        set("long", @LONG
上了楼来, 首先你看到一幅张天师的画像挂在对面的墙上, 画像
的下方摆著一张覆著红布的桌子, 桌上整齐地放著茅山的镇教秘籍。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "down" : __DIR__"book_room1",
]));
        set("objects", ([
        __DIR__"npc/taolord" : 1,
        __DIR__"npc/up_taoist" : 2,
        __DIR__"obj/desk" : 1,

 ]) ); 
        set("coor/x",-40);
        set("coor/y",2140);
        set("coor/z",90);
        setup();
        replace_program(ROOM);
} 
void reset()
{
        object *inv;
        object con, item;
        ::reset();
        con = present("desk", this_object());
        inv = all_inventory(con);
        if( !sizeof(inv) ) {
        item = new(__DIR__"obj/specialbook");
        item->move(con);
        item = new("/questobj/daoqiao");
        item->move(con);
        }
}       
