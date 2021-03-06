 // hell_guard.c
#include <ansi.h> 
inherit NPC;
void backattack();
void create()
{
        string *order = ({"子", "丑", "寅", "卯", "辰", "巳", "午", "未", "申", "酉", "戌", "亥"}); 
        set_name( (order[random(12)]) + "阴鬼卒", ({ "hell guard","hellguard"}) );
        set("long", "这是一位来自阴界的守护神，专门担任护法之责。\n");
        set("attitude", "friendly");
        set("no_fly",1);
        set("no_arrest",1);
        
        set("combat_exp", 100000);
        set("chat_chance", 15);
        set("chat_msg_combat", ({
                name() + "喝道：孽障！随我赴阴司受审吧。\n"
        }) ); 
        set_skill("fork", 90);
        set_skill("parry", 70);
        set_skill("dodge", 50);
        set_skill("move", 70);
        set_skill("hunting-fork",70);
        set_skill("notracesnow",70);
        map_skill("dodge","notracesnow");
        map_skill("fork","hunting-fork");
        map_skill("parry","hunting-fork");
        setup(); 
        carry_object(__DIR__"obj/steel_armor")->wear();
        carry_object(__DIR__"obj/steel_fork")->wield();
} 
int heal_up()
{
        if( environment() && !is_fighting() ) {
                call_out("leave", 1);
                return 1;
        }
        return ::heal_up() + 1;
} 
void leave()
{
        object owner,*pros;
        message("vision",
                HIB + name() + "说道：末将奉法主召唤，现在已经完成护法任务，就此告辞！\n\n"
                + name() + "的身形发出幽暗的蓝光，沉入地下不见了。\n" NOR, environment(),
                this_object() );
        if(objectp(owner=this_object()->query("possessed")))
        {
                owner->add_temp("max_guard",-1);
                pros = owner->query_temp("protectors");
                        pros -= ({ this_object() });
                owner->set_temp("protectors",pros);
        }                
        destruct(this_object());
} 
void invocation(object who, int level)
{
        int i, bonus_skill;
        object *enemy,*pros; 
        set("str",10+level/10+random(level/12));
        set("agi",10+random(level/12));
        set("cor",15+random(level/12));
        
        set("max_kee",300+random(level*level/60));
        set("eff_kee",query("max_kee"));
        set("kee",query("max_kee"));
        set("max_gin",query("max_kee")/2);
        set("gin",query("max_kee")/2);
        set("eff_gin",query("max_kee")/2);
        set("max_sen",query("max_kee")/2);
        set("eff_sen",query("max_kee")/2);
        set("sen",query("max_kee")/2);
        
        set("max_force",300+random(level*level/200));
        set("force",query("max_force")); 
        
        bonus_skill = 50 + level/4 + random(level/4);
        set_skill("fork", 50 + level/4 + random(level/4));
        set_skill("parry", 50 + level/4 + random(level/4));
        set_skill("dodge", 50 + level/4 + random(level/4));
   set_skill("move", 50 + level/4 + random(level/4));
        set_skill("notracesnow",20 + level/4 + random(level/4));
        set_skill("hunting-fork",30 + level/4 + random(level/4));
        
        set("combat_exp", 20000 + level/8*level*level/2+random(level/8*level*level/2)); 
         
        pros = who->query_temp("protectors");
        if(sizeof(pros))
                pros += ({ this_object() });
        else
                pros = ({ this_object() });
        who->set_temp("protectors",pros);
        
        message("vision",
                HIB "一道蓝光从地底升起，蓝光中出现一个手执钢叉、面目狰狞的鬼卒。\n\n"
                + name() + "说道：末将奉法主召唤，特来护法！\n" NOR,
                environment(), this_object() );
        enemy = who->query_enemy();
        i = sizeof(enemy);
        while(i--) {
                if( enemy[i] && living(enemy[i]) ) {
                        kill_ob(enemy[i]);
                        if( userp(enemy[i]) ) enemy[i]->fight_ob(this_object());
                        else enemy[i]->kill_ob(this_object());
                }
        }
        set_leader(who);
        set("possessed",who);
}
void backattack()
{
        int i;
        object owner, *enemy;
        if(objectp(owner=this_object()->query("possessed")))
        {
                enemy = this_object()->query_enemy();
        i = sizeof(enemy);
        while(i--) {
                if( enemy[i] && living(enemy[i]) ) {
                        owner->kill_ob(enemy[i]);
                        enemy[i]->kill_ob(owner);
                }
        } 
        } 
} 
void die()
{
        object *pros,owner;
        if(objectp(owner=this_object()->query("possessed")))
        {
                owner->add_temp("max_guard",-1);
                pros = owner->query_temp("protectors");
                        pros -= ({ this_object() });
                owner->set_temp("protectors",pros);
        }                
        backattack();
        ::die();
}  
void heart_beat()
{
        object leader;
        
        ::heart_beat();
        
        if(query_temp("is_unconcious")||is_busy())
                return ;
        if(query("possessed"))
        {
                leader=query("possessed");
                if(objectp(leader) && environment(leader)!=environment())
                {
                        message_vision("$N匆匆离去。\n",this_object());
                        this_object()->move(environment(leader));
                        message_vision("$N走了过来。\n",this_object());
                        delete("leave_room");
                }
        }
        
        else
        {
           if(!query("leave_room"))
                        set("leave_room",1);
                else
                        add("leave_room",1);
                if(query("leave_room")==5)
                        leave();
        }
}   
