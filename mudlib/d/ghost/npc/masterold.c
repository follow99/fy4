inherit NPC;
inherit F_MASTER;
#include <ansi.h>
void smart_fight(); 
void create()
{
    set_name("老刀把子", ({ "master lao dao", "master"}) );
    set("gender", "男性" );
    set("class","wudang");
    set("age", 45);
    set("int", 30);
    set("per", 30);
    set("str",50);
    set("apprentice_available", 50);
    set("reward_npc", 1);
    set("difficulty", 15);
    set("fly_target",1);
    create_family("幽灵山庄", 1, "庄主");
    set("rank_nogen",1);
    set("ranks",({ "弟子","领班","小管家","管家","大管家",
                        "总管","大总管","副城主" }));
    
    set("long", "他身穿灰袍，头戴竹笠，就象个有形无质的鬼魂。\n" );
    
    set("inquiry", ([
        "两仪心法": 
        "两仪心法乃我数十年闭关修炼所得，其[如封似闭]乃武林一绝。\n",
        "如封似闭": 
        "此诀的妙处在于无论是空手或执刃，无论是用何种武功，都可以使用。\n",
        ]) ); 
         
    set("max_atman", 1000);
    set("atman", 1000);
    set("max_force", 1000);
    set("force", 1000);
    set("force_factor", 90);
    set("max_mana", 2000);
    set("mana", 2000);
    
    set("resistance/kee",30);
    set("resistance/sen",50);
    set("resistance/gin",30);
    
    set("combat_exp", 9999999);
    set("score", random(90000));
    
    set("skill_public", 1); 
    set("chat_chance_combat", 40);
    set("chat_msg_combat", ({
               (: smart_fight() :),
        }) );
    
    set_skill("perception", 150);
    set_skill("foreknowledge", 180);
    set_skill("changelaw", 150);
    set_skill("unarmed", 150);
    set_skill("sword", 180);
    set_skill("move", 150);
    set_skill("force", 180);
    set_skill("parry", 150);
    set_skill("literate", 180);
    set_skill("dodge", 150);
    set_skill("three-sword", 180);
    set_skill("taiji", 160);
    set_skill("five-steps",160);
    set_skill("liangyi-force",180); 
    map_skill("force","liangyi-force");
    map_skill("unarmed", "taiji");
    map_skill("sword", "three-sword");
    map_skill("parry", "three-sword");
    map_skill("dodge","five-steps"); 
    setup();
    carry_object(__DIR__"obj/cloth3")->wear();
    carry_object(__DIR__"obj/hat")->wear();
    carry_object(__DIR__"obj/swordd")->wield();
} 
/*void reset()
{
    delete_temp("learned");
    set("apprentice_available", 20);
}
*/ 
void attempt_apprentice(object ob)
{
            call_out("do_recruit", 2, ob);
} 
void do_recruit(object ob)
{
    if((int)ob->query_temp("marks/顾云飞")) {
        command("stare " + ob->query("id"));
        command("say 你不是来做奸细的吧？\n");
        return;
    }
    else  if((int)ob->query_temp("marks/幽灵山庄")) {
        say("\n");
        command("say 好！你把武当的镇山七星宝剑拿来给我，再将那石老儿杀了，不用拜师，我也传授你一身武功！\n");
        ob->set("marks/拿七星宝剑", 1);
        return;
    }
    else {
        command("sigh");
        command("say 我早已不收徒弟了！");
        return;
    }
} 
/*int recruit_apprentice(object ob)
{
    if( ::recruit_apprentice(ob) )
        ob->set("class", "ghost");
    add("apprentice_availavble", -1);
}*/  
int recognize_apprentice(object ob)
{
    return ( ob->query("marks/老刀把子") ||
             (string) ob->query("class") == "ghost");
} 
int accept_object(object who, object ob)
{
    if((string)ob->name() != "七星剑") return 0;
    if(!who->query("marks/拿七星宝剑")) return 0;
    if(ob->query("real") && (object)ob->query_temp("marks/owner") == who &&
       who->query_temp("killed_master_shi"))
    {
        who->delete("marks/拿七星宝剑");
        command("spank " + who->query("id"));
        command("say 你想要武功秘籍，还是向我学武？(accept book/teach?)");
        who->set_temp("marks/拿到七星宝剑", 1);
        add_action("do_accept", "accept");
    }
    else
    {
        say("老刀把子接过七星剑，仔细地看了看。\n");
        command("sigh");
        command("say 这一柄又是假的！");
    }
    return 1;
} 
int do_accept(string arg)
{
    object me, book;
    
    if(!arg || (arg != "book" && arg != "teach")) 
        return notify_fail("你想要什么？\n");
    me = this_player();
    if(!me->query_temp("marks/拿到七星宝剑")) return 0;
    me->set_temp("marks/拿到七星宝剑", 0);
    if(arg == "book")
    {
        book = new(__DIR__"obj/book");
        book->move(this_object());
        command("give book to " + me->query("id"));
        command("say 你功劳不小，所以你还可以向我学武。");
    }
    else 
        command("say 从今天开始，你可以同我学武了。");
    me->set("marks/老刀把子", 1);
    return 1;
}  
smart_fight()
{
   int i;
        object *enemy, who;
        who = this_object();
        enemy = this_object()->query_enemy();
        for(i=0; i<sizeof(enemy); i++) {
        if (!enemy[i]->is_zombie() && enemy[i]->query("id")!="guard") 
                who->perform_action("sword.nianzijue"); 
        }
        return;
}      
