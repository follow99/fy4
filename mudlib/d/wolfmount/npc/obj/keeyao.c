 // medicine.c
inherit ITEM;
#include <ansi.h> 
void create()
{
    set_name(WHT"�����ܵ���"NOR,({"baiyun wan","wan"}));
        set_weight(30);
        if( clonep() )
                set_default_object(__FILE__);
        else {
            set("long",
                "������ʢ��������ʥҩ�����۸񰺹���ͨ��ֻ��������̾��\n");
        set("unit","��");
        set("value", 150000);
        }
        ::init_item();
} 
void init()
{
  if(this_player()==environment())
        add_action("apply_medicine","yong");
} 
int apply_medicine()
{
        int value = 20;
        int diff; 
        if(this_player()->is_fighting())
            return notify_fail("ս���в�����ҩ����\n");
        if(this_player()->is_ghost()){
                return notify_fail("���겻������ҩ��\n");
        }
        diff = this_player()->query("max_kee")-this_player()->query("eff_kee");
        if(!(diff))    return notify_fail("��û�����ˣ�\n");
    if(value < diff) value = diff;
            
    message_vision("$N����һ�Ű����ܵ��裬�˿����������������������\n",this_player());
        this_player()->add("eff_kee",value);
        destruct(this_object());
        return 1;
}    