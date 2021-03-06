 // garrison.c
#include <ansi.h> 
inherit NPC; 
void create()
{
        set_name("县城官兵", ({ "town garrison", "garrison" }) );
        set("long",
                
"这是个正在执行公务的县城官兵，虽然和许多武林人物比起来，官兵\n"
                
"们的武功实在稀松平常，但是他们是有组织、有纪律的战士，谁也不\n"
                "轻易地招惹他们。\n"); 
        set("attitude", "heroism");
        set("vendetta_mark", "authority");
        set("pursuer", 1); 
        set("str", 27);
        set("cor", 26);
        set("cps", 25); 
        set("combat_exp", 100000); 
        set("chat_chance", 10);
        set("chat_msg", ({
                (: random_move :),
        }) ); 
        set("chat_chance_combat", 15);
        set("chat_msg_combat", ({
                "县城官兵喝道：还不快放下武器束手就缚？\n",
                "县城官兵喝道：大胆刁民竟敢拒捕？反了！反了！\n"
        }) ); 
        set_skill("unarmed", 70+random(100));
        set_skill("sword", 70+random(100));
        set_skill("parry", 70+random(100));
        set_skill("dodge", 70+random(100));
        set_skill("move", 100+random(100)); 
        set_temp("apply/attack", 70);
        set_temp("apply/dodge", 70);
        set_temp("apply/parry", 70);
        set_temp("apply/damage", 30);
        set_temp("apply/armor", 70);
        set_temp("apply/move", 100); 
        setup(); 
        carry_object("/obj/armor/cloth")->wear();
        carry_object("/obj/weapon/sword")->wield();
} 
int accept_object(object who, object ob)
{
        if( who->query("vendetta/authority") ) {
                if( ob->value() >= 500000 ) {
                        say("官兵呵呵的笑道：好说，好说...\n");
                        who->set("vendetta/authority", 0);
                        who->remove_all_killer();
                        return 1;
                } else {
                    say("官兵说道：这点钱还不够大爷喝酒的呢！\n");
                        return 0;
                }
        }
        say("官兵说道：别来收买我！");
        return 0;
} 
