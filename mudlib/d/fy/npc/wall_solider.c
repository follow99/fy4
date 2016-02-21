#include <ansi.h>
inherit NPC; 
void create()
{
        set_name("ֵ�ڱ�", ({ "fengyun garrison", "garrison" }) );
        set("long",
"���Ǹ�����ִ���س������ֵ�ڱ�����Ȼ���������������������ֵ�ڱ��ǵ��书\n"
"ʵ��ƽ����������������֯���м��ɵ�սʿ��˭Ҳ�����׵��������ǡ�\n"
"�����Ҳ��Ҫ�������ǡ� \n");
        set("attitude", "heroism");
        set("str", 27);
        set("vendetta", "authority");
        set("cor", 26);
        set("cps", 25);
        set("combat_exp", 100000);  
        set("chat_chance_combat", 45);
        set("chat_msg_combat", ({
                "ֵ�ڱ��ȵ�������������������־͸���\n",
                "ֵ�ڱ��ȵ����󵨵��񾹸Ҿܲ������ˣ����ˣ�\n",
                (: perform_action, "spear.suomengpanhun" :),
        }) ); 
        set_skill("unarmed", 70+random(100));
        set_skill("spear", 10+random(50));
        set_skill("parry", 70+random(100));
        set_skill("dodge", 70+random(100));
        set_skill("move", 100+random(100));
        set_skill("duanhun-spear",151);
        map_skill("spear","duanhun-spear");
        set_temp("apply/attack", 70);
        set_temp("apply/dodge", 70);
        set_temp("apply/parry", 70);
        set_temp("apply/damage", 30);
        set_temp("apply/armor", 70);
        set_temp("apply/move", 100); 
        setup(); 
        carry_object(__DIR__"obj/kiujia")->wear();
        carry_object(__DIR__"obj/spear")->wield();
}
void init()
{
        object ob;
        object *inv;
        int i;
        if( interactive(ob = this_player()) ) {
                inv = all_inventory(ob);
                for(i=0; i<sizeof(inv); i++)
                {
                        if((string)(inv[i]->name() == "����ս��") && inv[i]->query("equipped"))
                                return;
                }       
                message_vision("$N�ȵ�������˽������Ҫ�أ�ɱ��\n",this_object());
                kill_ob(ob);
                return;
        }
}        