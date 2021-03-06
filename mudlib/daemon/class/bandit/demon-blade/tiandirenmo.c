 // tie@fengyun
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
        string dodskill,msg;
        int extra, step, n;
        extra = (int)me->query_skill("demon-blade",1);
        step = (int)me->query_skill("demon-steps",1);
		n = 4;

        if ( extra < 50) 
                return notify_fail("你的［如意天魔连环八式］还不够纯熟！\n");
        if ( step < 50) 
                return notify_fail("你的［如意人魔连环八步］还不够纯熟！\n");
        dodskill = (string) me->query_skill_mapped("dodge");
        if ( dodskill != "demon-steps")
                return notify_fail("［天地人魔］需要如意人魔连环八步的配和！\n");
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("［天地人魔］只能对战斗中的对手使用。\n");
        
		if (me->query("class")!="bandit" || me->query_skill_mapped("force")!="demon-force") {
            
			step = step/2;
			n = 5;
		}

        me->add_temp("apply/attack",step);
//        me->add_temp("apply/damage",extra);     
        msg = HIB  "$N"+HIB"神气贯通，将［如意天魔连环八式］一气呵成！\n\n"NOR;
		msg += HIW "“万魔初醒”    "+HIR"【斩】！！" NOR;
        COMBAT_D->do_attack(me,target,TYPE_PERFORM,msg);
        msg = HIW  "“魔焰万丈”    "+HIR"【散】！！" NOR;
        COMBAT_D->do_attack(me,target,TYPE_PERFORM,msg);
        msg = HIW  "“魔光乍现”    "+HIR"【劈】！！" NOR;
        COMBAT_D->do_attack(me,target,TYPE_PERFORM,msg);
        msg = HIW  "“天魔独尊”    "+HIR"【砍】！！" NOR;
        COMBAT_D->do_attack(me,target,TYPE_PERFORM,msg);
        msg = HIW  "“万刃天魔”    "+HIR"【滚】！！" NOR;
        COMBAT_D->do_attack(me,target,TYPE_PERFORM,msg);
        msg = HIW  "“天魔回天”    "+HIR"【撩】！！" NOR;
        COMBAT_D->do_attack(me,target,TYPE_PERFORM,msg);
        msg = HIW  "“天魔七现”    "+HIR"【扫】！！" NOR;
        COMBAT_D->do_attack(me,target,TYPE_PERFORM,msg);

        msg = HIW  "“万魔归宗”    "+HIR"【杀】！！" NOR;
        me->add_temp("apply/attack",step);
        me->add_temp("apply/damage",extra);
        COMBAT_D->do_attack(me,target,TYPE_PERFORM,msg);
        me->add_temp("apply/attack",-step*2);
        me->add_temp("apply/damage",-extra);    
	
	if (me->query("combat_exp")<=1500000) n=3;
        me->start_busy(n);
        return 1;
}     
