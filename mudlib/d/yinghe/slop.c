 // Room: slop.c --- by MapMaker
inherit ROOM; 
void create()
{
        set("short", "蓝色草坡"); 
        set("long", @LONG
这是一片奇异的草地，它不是青青的，而是象极了一洼蔚蓝天空下的湖泊。
空气中漂浮着的淡淡的青草香，以及这一洼蓝色给这诡异苍白的空间带来些许的
宁静。仔细看，蓝色里似乎盘织着神秘的紫色。这里向北一切笼罩在蒙蒙云气中，
南边却是一片浩瀚的沙海，一条走廊绵延于流沙之上。
LONG); 
        //{{ --- by MapMaker
        set("type","street");
        set("exits",([
        "west":__DIR__"garden",
        "south":__DIR__"woodroad",
        "north":__DIR__"dragon_den",
        ]) );
        //}}
        set("item_desc", ([
                "草地" : "茂密的草地里生长着一种奇怪的紫藤。（ｃｈｏｐ　ｖｉｎｅ）\n",
                "grass" : "茂密的草地里生长着一种奇怪的紫藤。（ｃｈｏｐ　ｖｉｎｅ）\n",
        ]));
        set("vine", 1);
        set("indoors", "yinghe");
        setup();
} 
void init(){
        add_action("do_chop", "chop");
} 
int do_chop(string arg){
    object obj;
    object me; 
    if(arg && (arg=="vine" || arg=="紫藤")){
        me = this_player();
        obj = me->query_temp("weapon");
        if( !obj ) {
            write("你空着手，怎么砍？\n");
            return 1;
        }
        if( obj->query("flag") == 4){
            if(query("vine")) {
                object ob;
                message_vision(sprintf(
                    "$N挥动%s，砍下了一条长长的藤萝。\n",obj->name()),me);
                delete("vine");
                ob=new(__DIR__"obj/vine");
                ob->move(me);
            } else {
            message_vision(sprintf(
            "$N用手中的%s向蓝色的草丛。\n",obj->name()), me);
                }
        } else {
                message_vision(sprintf(
            "$N用手中的%s向丛生的藤萝一顿乱砍．\n",obj->name()), me);
        }
    }
    else write("你要砍什么？\n");
    return 1;
} 
void reset(){
        ::reset();
        set("vine", 1);
}   
