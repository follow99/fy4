 // Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
void create()
{
    set_name("殷正廉", ({ "master yin", "master","yin" }) );
    set("long",
        "风云城中最高的官，有至高无上的权力\n");
    set("nickname", RED"一品钦差"NOR);
    set("attitude", "heroism");
        set("chat_chance", 1);
        set("chat_msg", ({
                "殷正廉道：皇上当年赐给我的尚方宝剑不见了。。。\n",
                "殷正廉摇摇头道：宝剑不见了，没有心情教学生。。。\n",
        }) );
    // Make this before create_family will prevent generation in title
    set("rank_nogen",1); 
    create_family("朝廷",6,"官员");
    set("student_title","官员");
    set("ranks",({ "七品芝麻官","六品官","五品官","四品官","三品官",
                       "二品官","一品官","钦差大臣","兵马统领",
                       "兵马总统领","镇远将军","定国大将军" }));
    set("rank_levels",({ 32000,64000,128000,256000,512000,
                             1024000,1536000,2304000,3456000,
                             5187000,26244000 }));    
    
    set("vendetta_mark", "authority");
    set("str", 27);
    set("cor", 26);
    set("cps", 25);
    set("agi",25);
    set("int",30);
    set("max_kee",7000);
    set("max_gin",5000);
    set("max_sen",5000);
        set("age",55);
    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
        (: perform_action, "unarmed.yuhuan" :),
            }) );
    set("combat_exp", 90000000);
    set_temp("apply/damage",500);
    set_skill("unarmed", 220);
    set_skill("sword",100);
    set_skill("force",80);
    set_skill("parry", 120);
    set_skill("dodge", 90);
    set_skill("changquan",200);
    set_skill("feixian-steps",60);
    set_skill("feixian-sword",80);
    set_skill("jingyiforce",50);
    set_skill("move", 100);
    set_skill("literate",90);
    set_skill("leadership",200);
    set_skill("strategy",200);
    map_skill("unarmed","changquan");
    map_skill("dodge","feixian-steps");
    map_skill("force","jingyiforce");
    map_skill("sword","feixian-sword"); 
    
    setup();
    if(random(2)) set("env/no_teach",1);
    carry_object(__DIR__"obj/guanfu")->wear();
} 
void attempt_apprentice(object me)
{
    if( !me->query("class"))
    {
        if((int)me->query("combat_exp") > 20000) {
        command("smile");
        command("say 很好！朝廷正在用人之时，努力吧！\n");
        command("recruit " + me->query("id") );
        } else command("say 你什么都不会，也没有什么经验，怎么给朝廷效力？\n");
    }
    else command("say 朝廷不需要你这种不三不四，来历不明之人！\n");
} 
void recruit_apprentice(object ob)
{
    if( ::recruit_apprentice(ob) )
        ob->set("class", "official");
    ob->set("vendetta_mark", "authority"); 
} 
int accept_object(object who, object ob)
{
        if( ob->query("shangfang") ){
                this_object()->delete("env/no_teach");
        if(who->query_temp("marks/sword_gotit")) {
        //give reward
        command("nod");
        command("say 你真的是帮了我一件大忙，是个可以托付重任的人。\n");
        command("say 你再帮我查查是谁杀了当今武林武当派的老掌门？\n");
         if(!who->query("m_success/尚方宝剑")) {
                who->set("m_success/尚方宝剑",1);
                who->add("score",100);
         }
        } else {
        //punish
        command("ah");
        command("say 大胆！竟敢偷老夫的宝剑\n");
        kill_ob(who);
        }
        return 1;
        }
        return 0;
}
