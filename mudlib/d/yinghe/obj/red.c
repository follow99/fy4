 // Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors. 
inherit ITEM;
void create()
{
        set_name("红玉", ({ "red" , "红玉"}) );
        set_weight(500);
        set_max_encumbrance(1);
        set("no_get", 1);
        set("no_shown", 1);
        set("prep", "on");
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "个");
                set("long", "这是一个在中间成凹形的红色玉石。\n");
                set("value", 1);
        }
        ::init_item();
}
int is_container() { return 1; }       
