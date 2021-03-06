 inherit NPC;
#include <ansi.h>
inherit F_MASTER;
void create()
{
    set_name(HIY "真武帝君" NOR, ({ "master zhenwu", "master", "zhenwu" }) ); 
    set("gender", "男性");
    set("age", 999);
    set("long", "真武为天界亚帝，坐镇武当，为道界三教祖师，荡魔天尊，乃道教崇奉的大神。\n");
    set("attitude", "peaceful");
   set("reward_npc", 1);
        set("difficulty", 30);
    set("str", 6000);
    set("cor", 30);
    set("int", 24);
    set("cps", 30);
    set("force", 2000);
    set("max_force", 2000);
    set("force_factor", 1000);
    set("combat_exp", 20000000);
    set("score", 20000);
    set("class", "wudang");
    
    set_skill("unarmed", 160);
    set_skill("force", 200);
    set_skill("sword", 200);
    set_skill("taijiforce", 200);
    set_skill("literate",150);
    set_skill("incarnation",320);
    set_skill("dodge",160);
    set_skill("taiji",160);
    set_skill("taiji-sword",160);
    set_skill("parry",190);
    set_skill("changelaw", 200);
    set_skill("qixing",100);
    set_skill("five-steps",160);
    set_skill("spells",100);
    set_skill("move",160);
    
    set_temp("apply/damage",30000);
    map_skill("spells","qixing");
    map_skill("dodge","five-steps");
    map_skill("move","five-steps");     
    map_skill("force", "taijiforce");
    map_skill("unarmed", "taiji");
    set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
             (: perform_action, "unarmed.nianzijue" :),
        }) );
    set("no_shown",1);
    set("rank_nogen",1);
    create_family("武当派", 1, "玄天祖师"); 
    set("ranks",({"真人",YEL"仙人"NOR,YEL"天尊"NOR,HIY"帝君"NOR}));
    set("rank_levels",({320000,5187000,26244000}));
    setup();
}
int accept_fight(object me)
{
    return 0;
}
void attempt_apprentice(object me)
{
/*      if (me->query("once_menpai/shaolin") && !me->query("marks/muren_time")
                && !me->query("marks/bugout") && me->query("class")=="wudang"
                && me->query("betrayer")==0)
        {       message_vision("$N说，你师傅找你，先去见他一次。\n",this_object());
                return;
                }       */
        
        if(me->query("class")=="wudang"
                &&me->query_skill("changelaw",1)>100
                &&me->query("marks/武当_执着")
                &&me->query("combat_exp")>=1000000)
                {
                me->set("once_menpai/wudang",1);
                command("recruit " + me->query("id") );
                }
} 
void recruit_apprentice(object ob)
{
    if( ::recruit_apprentice(ob) )
        ob->set("class", "wudang");
}
void init()
{
    add_action("do_look","look");
      add_action("do_killing", "kill");
} 
int do_look(string arg)
{
    if (arg == "master zhenwu" || arg == "zhenwu" || arg =="master")
    {
        write(HIY "真武为天界亚帝，坐镇武当，为道界三教祖师，荡魔天尊，乃道教崇奉的大神。。\n" NOR);
        return 1;
    }
    return 0;
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
        if(id_class == "wudang"&& userp(victim)&&player!=victim)
        {
message_vision(HIW"$N对著$n喝道：" + RANK_D->query_rude(player) 
                                                + "竟敢杀" + RANK_D->query_self_rude(this_object()) 
                                                + "的徒弟，去死吧。\n"NOR, this_object(), player);
            this_object()->kill_ob(player);
            player->kill_ob(this_object());
            if (!player->is_busy()) player->start_busy(2);
            return 0;
        } 
    }
    return 0;
}
