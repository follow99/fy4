 // assasin-hammer.c
inherit SKILL;
#include <ansi.h> 
void setup() {
        set("name",                     "������ɱ");
        set("practice_bonus",   -20);
        set("effective_level",  200);
        set("usage/hammer",     1);
        set("usage/parry",              1);
        set("practice_damage",  40);
        set("skill_class",              "wolf");
        
        set("unarmed_parry_msg", ({"$nһ�С�������ˡ�������$v����ǰ�����$N��æ������� \n",
                                                           "$n�趯$v��ʹ����ԥ������������Ӱ�����ƻ������ȵ�$N�޷����С�\n", 
                                                           "$n��$vбȡ$N���̣�һ�С���ĭ����������$N���Ķ��ˡ� \n"})
        );
        action = ({
        ([      "action":               
"$N����$wб�Ӷ��ϣ�һ�С�ר����㡹����$n��$l����δ�����������ȵ�
$n��Ϊ֮�ϣ� ��",
                "force":                90,
                "dodge":                120,
                "parry":                120,
                "post_action": "bash_weapon",
                "damage_type":  "����"
        ]),
        ([      "action":               
"$N������ȣ�����$w��ɨ��·���ۿ�����ʹ�ϣ�ͻȻ��֪��δ������֣�
һ�С�Ҫ��ϱۡ�����$n��$l�� ",
                "damage":               120,
                "dodge":                30,
                "parry":                60,
                "post_action":  "bash_weapon",
                "damage_type":  "����"
        ]),
        ([      "action":               
"$N���ƽ������������߶���$w��Ȼ�����͵͵����죬����һʽ�������
������$Nһ��ۣ�$w�������֮��������$n��$l�� ", 
                "damage":               270,
                "force" :               240,
                "dodge":                100,
                "parry":                240,
                "post_action":  "bash_weapon",
                "damage_type":  "����"
        ]),
        ([      "action":               
"$N����$w��չ��һ�С������ͼ����㾢��ѹ������Ȼһת��·��ײ��
$n��$l�� ",
                "damage":               100,
                "force" :               100,
                "dodge":                200,
                "parry":                400,
                "post_action":  "bash_weapon",
                "damage_type":  "����"
        ]),
        ([      "action":
"$Nʹ�����������ס���������ǰ���ƣ�$n�е���Ϊ֮�ᡣ$Nһ����ֱ��
���ϣ�$wЮ��һ���ҷ�����$n�� ",
                "force":               30,
        "damage" :      160,
                "dodge":                100,
                "parry":                600,
                "post_action": "bash_weapon",
                "damage_type":  "����"
        ]),
});
} 
int valid_learn(object me) {
        
        if(!::valid_learn(me)) {
                return 0;
        }
        
    if( (int)me->query("str") + (int)me->query("max_force") / 10 < 60 ) {
                return notify_fail("���������������Ҳ������һ����������ǿ������\n");
        }
        return 1;
}  
mixed hit_ob(object me, object victim, int damage_bonus)
{
    object ob;
    if( random(damage_bonus) < 350 ) return 0;
    if(ob=victim->query_temp("weapon"))
    if(ob->query("skill_type") == "blade")
    if(victim->query_skill_mapped("blade") == "bat-blade"
     ||victim->query_skill_mapped("blade") == "ittouryu")
    if(me->query_skill("hammer") > victim->query_skill("blade")) {
    switch(random(3)) {
            case 0:
                    message_vision(HIR "\n$N�ϵл��ȣ�����ռ���Ϸ磡" NOR,me,victim);
                    break;
            case 1:
                    message_vision(HIR "\n$N����׾ٵ�����$n�Ŀ�϶֮�䣡" NOR,me,victim);
                    break;
            case 2:
                    message_vision(HIR "\n$N�����г���$n��ʩչ�����ˣ�" NOR,me,victim);
                    break;
                    }
    return random(me->query_skill("hammer")) * 3;
    }
    return 0;
}      