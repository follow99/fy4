#include <weapon.h>
inherit THROWING; 
void create()
{
    set_name("羽毛", ({ "feather" , "羽毛"}) );
    if( clonep() )
        set_default_object(__FILE__);
    else {
        set("unit", "个");
        set("long", "一个色泽艳丽的公鸡尾巴上的毛。\n");
        set("base_unit", "个");
        set("base_value", 1);
        set("base_weight", 1);
    }
    set_amount(1);
    ::init_throwing(2);
}         
