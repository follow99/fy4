 inherit ITEM;
#include <ansi.h>
void create()
{
        set_name("不知名的小花", ({ "小花" , "不知名的小花","noflower"}) );
        set_weight(500);
        set_max_encumbrance(8000000);
        set("no_get", 1);
        set("no_shown", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "丛");
                set("long", "已经开始凋谢的花草。\n");
                set("value", 1);
        }
        ::init_item();
} 
int is_container() { return 1; }      
