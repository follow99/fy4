 // Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
inherit NPC;
inherit F_MASTER;
#include <ansi.h>
int kill_him();
int leave();
int wieldsword();
void create()
{
    set_name("胡金袖", ({ "master hu", "master"}) );
    set("nickname", HIY "身轻如燕"NOR);
    set("gender", "女性" );
    set("class","quanli");
    set("reward_npc", 1);
    set("difficulty", 5);
    set("age", 34);
    set("per", 35);
    set("str", 25);
    set("ill_boss",5);
    set("int",30);
    set("attitude","friendly");
    set("max_force", 800);
    set("force", 800);
    
    set("long", "
她身上宽大的袖子飘逸、柔软、华美，袖口绣着金边，是名家用金线绣出的牡丹。\n袖中伸出的一双玉手，修长、圆润、十指纤纤宛如白玉雕成。\n");
    create_family("财神庙", 12, "当家");
    set("rank_nogen",1);
    set("ranks",({"脚夫","伙计","信差","趟子手","执旗手","镖师","镖头",
                      "副总镖头","总镖头",HIW"特使"NOR,
                      RED"令主"NOR,HIY"大当家"NOR}));
    set("rank_levels",({ 32000,64000,128000,256000,512000,
                             1024000,1536000,2304000,3456000,
                             5187000,26244000 })); 
    set("chat_chance_combat", 99);
    set("chat_msg_combat", ({
        (: perform_action, "sword.meikaiwudu" :),
                (: wieldsword  :),
             }) );
    set("combat_exp", 3500000);
    set("inquiry",  ([
                "leave": (: leave :),
                ]) );
        set("chat_chance", 1);
    set("chat_msg", ({
                "胡金袖掩口偷笑：狼牙怎麽会在老卜那，狼牙当然是长在狼嘴里啦．．．\n",
            }) ); 
    set_skill("perception", 180);
    set_skill("move", 220);
    set_skill("parry",100);
    set_skill("dodge", 220);
    set_skill("force", 100);
    set_skill("literate", 140);
    set_skill("unarmed",100);
    set_skill("sword",120);

    set_skill("zhao-sword",120);
    set_skill("tenderzhi",120);
    set_skill("stormdance",320);
    set_skill("qiankunstrike",100);
    set_skill("wuchenforce",100);

    map_skill("dodge", "stormdance");
    map_skill("move", "stormdance");
    map_skill("force", "wuchenforce");
    map_skill("unarmed", "qiankunstrike");
    map_skill("sword","zhao-sword");
    map_skill("parry","zhao-sword");


   setup();
   carry_object(__DIR__"obj/thin_sword")->wield();
   carry_object("d/fugui/npc/obj/m_cloth2")->wear(); 
} 
void attempt_apprentice(object me)
{
    if((int)me->query("deposit")>=1000000)
    {
    	if (me->query("betrayer"))
    	    	{  command("shake");
    	           command("say 钱虽能通神，但可一不可再啊。。。");
    	           return;
                   }    	
        command("xixi");
        command("say 看你也像只肥羊，暂且就照顾照顾你吧！\n");
        command("recruit " + me->query("id") );
        return;
    }
    else
    {
        command("heihei");
        command("say 就那点身家，就想学人当财神？！"); 
    }
} 
 
void recruit_apprentice(object ob)
{
    if( ::recruit_apprentice(ob) )
        ob->set("class", "quanli");
} 



void init()
{       
        ::init();
        add_action("do_killing", "kill");
} 

int do_killing(string arg)
{
    object player, victim;
    string id,id_class;
    player = this_player();
    if(!arg || arg == "") return 0;
    victim = present(arg, environment(player));
        if(!objectp(victim))
                return notify_fail("这里没有这个人。\n");
    if(living(victim))
    {
        id_class=victim->query("class");
        id=victim->query("id");
        if(id_class == "quanli"&& userp(victim)&& player != victim)
        {
            message_vision(HIW
"$N冷笑一声：谋财害命？！找错地方了吧！\n"NOR, this_object());
            this_object()->kill_ob(player);
            player->kill_ob(this_object());
            if (!player->is_busy()) player->start_busy(2);
            return 0;
        } 
    }
    return 0;
} 

int leave() {
        if (this_player()->query("class")!="quanli") return 0;
        message_vision(CYN"$N哼了一声，用不屑的眼神看着你。\n"NOR, this_object());
        message_vision(CYN"$N说：不懂珍惜荣华富贵，这五展梅剑法你也不配再用了！\n"NOR,this_object());
        return 1;
} 
int wieldsword()
{
command("unwield sword");
perform_action("unarmed.qiankun");
command("wield sword");
return 1;
}