 inherit ROOM;
void create()
{
        set("short", "野狼坡"); 
        set("long", @LONG
山势渐缓，眼前坡地是一处开阔所在。山岩高高在上，隐约有人影浮动，你刚
放下的心不禁马上又悬了起来，在这里鬼地方上可连个挡箭的岩石都没有。西首的
山壁上杂草从生，隐约可看见有个数尺宽窄的山洞。
LONG);
        set("type","mountain");
        set("item_desc", ([
                "山洞": "一个只有数尺宽窄的洞口，可以蹲着身爬上去（ｃｒａｗｌ）。\n",
                "cave": "一个只有数尺宽窄的洞口，可以蹲着身爬上去（ｃｒａｗｌ）。\n",
        ]) );
        set("coor/x",-690);
        set("coor/y",-700);
        set("coor/z",50);
        set("objects", ([
        __DIR__"obj/grass" : 1,
                        ]) );
       set("outdoors", "wolfmount");
        set("exits",([
                "southup":__DIR__"gully",
                "northeast":__DIR__"wolfhill2",
        ]) );
        setup();
}
void reset()
{
        object *inv;
        object con, item;
        ::reset();
        con = present("grass", this_object());
        inv = all_inventory(con);
        if( !sizeof(inv)) {
        item = new(__DIR__"obj/yeguo");
        item->move(con);
        }
} 
void init()
{
        add_action("do_crawl", "crawl");
} 
int do_crawl(string arg)
{
        object  me; 
        if(!arg) 
        {
                write("你要爬向哪里？\n");
                return 1;
        }
        
        if( arg == "up" || arg == "山洞" )
        {
                me = this_player();
                message_vision("$N抓着山壁上的杂草，慢慢的爬向山洞。\n", me);
                me->start_busy(2);
                call_out("fliping",2,me);
                me->stop_busy();
                return 1;
        }
        else
        {
                write("你不可以爬"+arg+"。\n");
                return 1;
        }
} 
int fliping(object me)
{
        object room;
        if( !me->is_ghost()) 
        {
                message_vision("$N慢慢爬到山洞里。\n", me);
                room = find_object(__DIR__"wolfcave");
                if(!objectp(room)) room= load_object(__DIR__"wolfcave");
                me->move(room);       
        }
        return 1;
} 
