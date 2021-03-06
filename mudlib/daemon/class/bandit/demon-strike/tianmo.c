 // tie@fengyun
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
        string msg;
        int extra, damage;
        if( !target ) target = offensive_target(me); 
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("［天魔式］只能对战斗中的对手使用。\n");
        extra = me->query_skill("demon-strike",1);
		if(extra < 160) return notify_fail("你的［如意地魔连环八掌］不够熟练！\n");
		damage = (int)me->query("max_gin")/10;
		if(me->query("class") != "bandit") damage = damage/2;
        msg = HIC "$N"+HIC"双臂暴长，一招［天魔式］，双手拢向$n！" NOR;
        if(target->query("combat_exp") < me->query("combat_exp")/2 + random(me->query("combat_exp")*extra/60))
        {
        message_vision(msg+"\n",me,target);
        message_vision( CYN "$N"+NOR CYN"躲闪不及，全身正被掌影罩住！ 一股青气从$N"+NOR CYN"顶门喷涌而出！\n" NOR,target);
        target->receive_damage("gin",damage+random(damage*2),me);
        me->receive_heal("gin",damage);
        COMBAT_D->report_status(target);
		COMBAT_D->win_lose_check(me,target,1);
        }       
        else{
        COMBAT_D->do_attack(me,target, TYPE_PERFORM,msg);
        }
        me->start_busy(2);
        return 1;
}
