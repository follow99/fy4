 // sacrifice.c silencer@fy
#include <ansi.h> 
inherit SSERVER; 
int cast(object me, object target)
{ 
        object ding; 
        if(me->query("class")!="taoist")
                return notify_fail("只有三清宫的弟子才能够使用三清道术。\n");
        if(me->is_fighting()) 
                return notify_fail("战斗中不能施此法.\n");
        if((int)me->query_skill("necromancy",1) < 120 )
                return notify_fail("你的三清道术不够高！\n");
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要对谁施展这个法术？\n");
        if (!target->query("env/sacrifice"))
                return notify_fail("此人不愿意牺牲自己。\n"); 
        if (target->query("combat_exp")<1500000)
                return notify_fail("此人功力太浅,只能白白牺牲.\n");
        if (target->query("death/sacrifice_time")+86400>time())
                return notify_fail("此人最近刚献身过，需至少静养一日。\n");     
        if( !objectp(ding = present("ding", environment(me))) )
                        return notify_fail("只能在有宝鼎之处施此法。\n");
        if((int)me->query("mana") < 500 )
                return notify_fail("你的法力不够！\n");
        if((int)me->query("sen") < 500 )
                return notify_fail("你的神不够！\n"); 
        me->add("mana", -500);
        me->receive_damage("sen", 500);
        me->start_busy(5);
        target->start_busy(5);
        
        message_vision(HIW"\n$N盘膝端坐，低首垂目，默念道：‘舍身为人，舍我其谁。。。“\n"NOR,target);
        message_vision(HIY"$N口中喃喃地念著咒文，左手一挥，手中聚起一团金光射向$n！\n" NOR,me,target);
        message_vision(HIY"金光在$N顶门一闪，又射入宝鼎之内。\n"NOR,target);
        message_vision(YEL"$N的面色刹那间枯萎下去。\n"NOR+HIR"$N死了.\n"NOR,target);
        call_out("sacrifice_die",1,target);
        call_out("sacrifice_pill", 3 ,target);
   return 1;
} 
void sacrifice_die(object victim)
{
                int combat_exp, combat_pot; 
                victim->set("bellicosity", 0);  
                combat_exp = victim->query("combat_exp");
                combat_pot = victim->query("potential") - victim->query("learned_points");
                if(combat_pot < 0) {
                        combat_pot = 0;
                }
                
                if(combat_exp < 20000) {
                        victim->add("combat_exp", -(int)(combat_exp * 2 / 100)); 
                } else if(combat_exp < 200000) {
                        victim->add("combat_exp", -(int)(combat_exp * 2 / 100));
                        victim->add("potential", -(int)(combat_pot * 25 / 100));                
                
                } else if(combat_exp < 1000000) {
                        victim->add("combat_exp", -(int)(combat_exp * 3 / 100));
                        victim->add("potential", -(int)(combat_pot * 25 / 100));                
                
                } else {
                        victim->add("combat_exp", -(int)(combat_exp * 3 / 100));
                        victim->add("potential", -(int)(combat_pot * 50 / 100));                
                
                }
                victim->skill_death_penalty(combat_exp);
                victim->set("env/sacrifice",0);
                victim->set("death/sacrifice_time",time());
                victim->unconcious();
}  
void sacrifice_pill(object victim)
{
        object pill;
  
        seteuid(getuid());
        pill= new("/obj/item/sacrifice_pill");
        pill->move(victim);
        message_vision( HIY "\n\n一粒"+pill->name()+HIY"从鼎中跃出，落入$N掌心。\n" NOR, victim);
       
}
                   
