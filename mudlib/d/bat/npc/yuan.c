#include <ansi.h>
inherit NPC;
inherit F_MASTER;
void create()
{
    set_name("原随云", ({ "master yuan suiyun", "yuan suiyun","master"}));
    set("long",
        "
他笑容温柔而亲切，但一双眼睛里，却带着种说不出的空虚、寂寞、萧索
之意, 是个很秀气，很斯文的少年，穿着虽华丽，但却不过火。
\n"
        );
    set("title","无争山庄少主人");
    set("nickname", HIR "蝙蝠公子"NOR);
    set("gender", "男性");
    create_family("蝙蝠岛", 1, "岛主");
    set("student_title","弟子");
    
    set("class","bat");
    set("reward_npc", 1);
    set("difficulty", 25);
    set("fly_target",1);
    set("age", 26);
    set("int", 40);
    set("con", 20);
    set("per", 40);
    
    set("atman",1000);
    set("max_atman",1000);
    set("force", 2000);
    set("max_force", 2000);
    set("force_factor", 100);
    set("combat_exp", 80000000);
    set("attitude", "friendly");
    
    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
            (: perform_action, "dodge.huanyinqianchong" :),
            (: perform_action, "blade.shiwanshenmo" :),
            }) ); 
    set("chat_chance", 1);
    set("chat_msg", ({
        "原随云走到琴边，一首如行云流水般的曲子从他指间溢出。
世间己有很久没有过如此悦耳的琴声了。\n ",
            "\n",
        }) );
        
    set_skill("unarmed", 160);
    set_skill("move", 180);
    set_skill("dodge", 160);
    set_skill("parry", 160);
    set_skill("literate",150);
    set_skill("force", 180);
    set_skill("blade", 280);
    set_skill("meng-steps", 180);
    set_skill("bat-blade", 180);
    set_skill("wuzheng-force", 220);
    set_skill("perception",280);    
    
    map_skill("force", "wuzheng-force");
    map_skill("move",  "meng-steps");
    map_skill("dodge", "meng-steps");
    map_skill("parry", "bat-blade");
    map_skill("blade", "bat-blade"); 
    set("ranks",({"弟子","小邪","少邪","玄武神","朱雀神","白虎神",
                      "青龙神","副岛主"}));
    set("rank_nogen",1); 
    setup();
    carry_object("/obj/armor/armor",
                ([      "name"  :       HIY"金丝软甲"NOR,
                        "long"  :       "这是一件似金非金、似衣非衣的软甲，暗暗的放出
动人的金色光芒，一看就是天下奇珍。\n",
                                "value" :       0,
                                "armor_prop/armor"      : 200 ])
                )->wear();
    carry_object(__DIR__"obj/hanhai")->wield();  
} 
void attempt_apprentice(object ob)
{
    if (ob->query("combat_exp") < 3000000) {
        command("say  这么差的武功，怎么学得会我的刀法？");
        return;
        }        
    if( (int) ob->query_temp("marks/murderhu") == 1 )
     {
        command("say 很好，很好，蝙蝠岛正需要你这样胆大包天、横行无忌的人才！");
        command("recruit " + ob->query("id"));
     }
     else     command("say 你听没听过借刀杀人这句话 ？我现在想借阁下的刀。。。");
}  
void recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "bat");
        ob->add("betrayer",-1);
        if(ob->query("betrayer") < 0) ob->set("betrayer",0);
//      ob->add("score",-5000);
}
