 inherit ROOM;
void create()
{
        set("short", "太平镇小街");
        set("long", @LONG
小街的两旁是一排平房，西北最普通，最常见的砖土四合院，住在这里的大多
数是靠手艺吃饭的，有开小杂货铺的，理发的，打铁的，伐木的，也有的是常年奔
波于塞外和中原的生意人。
LONG
        );
        set("exits", ([ 
                "north": __DIR__"mroad5",
                "south": __DIR__"mroad7",
                "west": __DIR__"house6",
                
        ]));
        set("outdoors", "taiping");
        set("item_desc", ([
                    
        ]));
        set("coor/x",0);
        set("coor/y",0);
        set("coor/z",0);
        setup();
        replace_program(ROOM);
}       
