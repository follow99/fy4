 // Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
inherit NPC;
inherit F_MASTER;
#include <ansi.h>
int kill_him();
int leave();
void create()
{
    set_name("南宫灵", ({ "master nangong", "master"}) );
    set("nickname", HIR "神掌"NOR);
    set("gender", "男性" );
    set("class","beggar");
    set("reward_npc", 1);
    set("difficulty", 5);
    set("age", 34);
    set("per", 35);
    set("int",30);
    set("attitude","friendly");
    set("max_force", 800);
    set("force", 800);
    
    set("long", "现任天下第一大帮的帮主，前老帮主任慈的爱徒。\n");
    create_family("丐帮", 7, "龙头帮主");
    set("rank_nogen",1);
    set("ranks",({"堂外弟子","一袋弟子","两袋弟子","三袋弟子","四袋弟子",
                      "五袋弟子","六袋弟子","七袋弟子","八袋弟子",WHT"九袋弟子"NOR,
                      WHT"长老"NOR,HIW"龙头大哥"NOR}));
    set("rank_levels",({ 32000,64000,128000,256000,512000,
                             1024000,1536000,2304000,3456000,
                             5187000,26244000 })); 
    set("chat_chance_combat", 30);
    set("chat_msg_combat", ({
        (: perform_action, "unarmed.xianglongwuhui" :),
             }) );
    set("combat_exp", 2000000);
    
    set_skill("perception", 100);
    set_skill("move", 120);
    set_skill("parry",120);
    set_skill("dodge", 120);
    set_skill("force", 180);
    set_skill("literate", 140);
    set_skill("unarmed",150);
    set_skill("doggiesteps",120);
    set_skill("dragonstrike",120);
    set_skill("huntunforce",150);
    set_skill("staff",150);
    set_skill("dagou-stick",120);
    set_skill("begging",220);
    set_skill("foreknowledge",120);
    map_skill("dodge", "doggiesteps");
    map_skill("force", "huntunforce");
    map_skill("unarmed", "dragonstrike");
    map_skill("staff","dagou-stick");
    map_skill("parry","dagou-stick");
    set("inquiry", ([
        "谋杀" : (: kill_him :),
        "任慈" : (: kill_him :),
        "leave" : (: leave :),
        ]));
    setup();
    carry_object(__DIR__"obj/9bagcloth")->wear(); 
} 
void attempt_apprentice(object me)
{
    if((int)me->query("deposit")<=0)
    {
        command("say 看在你一贫如洗的份上，我就收你为徒吧！\n");
        command("recruit " + me->query("id") );
        return;
    }
    else
    {
        command("sigh");
        command("say 看来真的是树大招风，你有钱有势的，为什么要加入我丐帮？"); 
    }
} 
void recruit_apprentice(object ob)
{
    if( ::recruit_apprentice(ob) )
        ob->set("class", "beggar");
} 
int kill_him()
{
    object me;
    me = this_player();
    command("say 看来你已经知道得太多了！！ \n");
    this_object()->kill_ob(me);
    me->kill_ob(this_object());
    return 1;
} 
int accept_object(object who, object ob)
{
        if(ob->query("name")!="乌鞘长刀") return 0;
        if(who->query("天枫_quest2")=="成功")
        {
        message_vision(HIC"南宫灵大笑着对$N道：把这刀捎我大哥！！\n"NOR,who);
                return 0;
        }
        if(who->query("天枫_quest1")!="成功")
        {
                message_vision(HIR"南宫灵脸色一变，说道：“小子，只好怪你知道得太多了。。。”\n"NOR,who);
                kill_ob(who);
                return 0;
        }
    message_vision(HIW "南宫灵一把抹干眼泪，连声道：好好好，待我干完这杯，就和大哥一起去把他老
人家接回来。\n"NOR,who);
        message_vision(WHT"南宫灵将乌鞘长刀还给$N。\n"NOR,who);
    tell_object(who,"南宫灵轻声说道：劳烦帮我通知大哥无花，他现在少林出家为僧。\n");
        tell_room( environment(), "南宫灵在"+who->name()
                + "耳边小声地说了些话。\n", ({ who, this_object() }) );
        who->set("天枫_quest2","成功");
        this_object()->set("chat_msg", ({
"南宫灵手中拿着个酒杯，若有所思状。\n"
        }) );
        this_object()->set("chat_chance",2);
//      return 2;
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
        if(id_class == "beggar"&& userp(victim)&& player != victim)
        {
            message_vision(HIW
"$N冷笑一声：叫花子虽不成材，却也轮不到阁下来管教吧！\n"NOR, this_object());
            this_object()->kill_ob(player);
            player->kill_ob(this_object());
            if (!player->is_busy()) player->start_busy(2);
            return 0;
        } 
    }
    return 0;
} 
int leave() {
        if (this_player()->query("class")!="beggar") return 0;
        message_vision(CYN"$N叹了口气道，“你到底是贪图富贵呀。“\n"NOR, this_object());
        message_vision(CYN"$N说：打狗棒法和混饨心诀是祖师爷留下来的，你走了就学不会了。\n"NOR,this_object());
        return 1;
} 
