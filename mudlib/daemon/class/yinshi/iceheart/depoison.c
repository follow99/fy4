 // recover.c
// inherit "/daemon/condition/generic_condition";
inherit SSERVER;
#include <ansi.h>
#include <condition.h> 
int exert(object me, object target, int amount)
{
        int force, lvl;
        object obj;
        lvl = me->query_skill("iceheart",1);
        if( target != me && lvl < 100) return 
                notify_fail("你的功力不足以为他人逼毒。\n");
                
        force =(int) me->query("force");
        if( force <=100) 
                return notify_fail("你的真气不足。\n");
        
        if (target == me)
        {
        message_vision(HIW"$N运功抗毒，头上冒出豆大的汗．．．\n"NOR, me);       
        me->add("force", -100  );
        if (random(lvl) < 20)   return notify_fail("你失败了。\n");
                else    {
                        me->clear_condition();
                        if (me->query_condition("tianyi"))
                                me->clear_condition_type(BLOOD_POISON);
                        write("你成功了！\n");
                        return 1;
                        }
        }       
        else
        {
                if(!objectp(obj = present(target, environment(me))))
                        return notify_fail("这里没有这个人。\n"); 
                if( !obj->is_character() || obj->is_corpse() )
                        return notify_fail("看清楚一点，那并不是活物。\n");
                
                message_vision(HIW"$N一掌按在$n背心运功驱毒，头上冒出豆大的汗粒．．．\n"NOR, me,target);
                me->add("force", -150  );
                if (random(lvl)< 60)    return notify_fail("你失败了。\n");
           else    {
                target->clear_condition();
                message_vision(HIC"$N汗如雨下，哇地一声吐出一口黑血，脸上的青气慢慢散去．．．\n"NOR, target);
                write("你成功了！\n");
                return 1;
                }
        } 
} 
