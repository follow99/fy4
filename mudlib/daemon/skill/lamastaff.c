 // lamastaff.c
inherit SKILL; 
void setup() {
        set("name",                     "密宗杖法");
        set("learn_bonus",              -100);
        set("practice_bonus",           -5);
        set("black_white_ness",         -10);
        set("effective_level",          190);
        set("usage/staff",                      1);
        set("usage/parry",                      1);
        set("practice_damage",          30);
        set("skill_class",                      "lama");       
        set("parry_msg",                        ({
                        "$n口宣佛号，手中的$v竟如有生命般飞了起来，封住了$N的攻势。\n",
                        })
        ); 
        set("unarmed_parry_msg",        ({
                        "$n口宣佛号，手中的$v竟如有生命般飞了起来，封住了$N的攻势。\n",
                        })
        );
        action = ({
                        ([      "action":               
                                        "$N口宣佛号，手中$w竟如有生命般飞了起来，扫向$n下盘！",
                                "damage":               30,
                                "dodge":                40,
                                "parry":                40,
                                "post_action":  "bash_weapon",
                                "damage_type":  "挫伤"
                        ]),
                        ([      "action":               
                                        "$N口宣佛号，手中$w竟如有生命般飞了起来，径直攻向$n$l！",
                                "damage":               60,
                                "dodge":                30,
                                "parry":                60,
                                "post_action":  "bash_weapon",
                                "damage_type":  "挫伤"
                        ]),
                        ([      "action":           
										"$N口宣佛号，手中$w竟如有生命般飞了起来，拦腰击向$n$l！",
                                "damage":               50,
                                "dodge":                50,
                                "parry":                70,
                                "post_action":  "bash_weapon",
                                "damage_type":  "挫伤"
                        ]),
                        ([      "action":               
                                        "$N口宣佛号，手中$w竟如有生命般飞了起来，回旋撞向$n$l！",
                                "damage":               30,
                                "dodge":                30,
                                "parry":                50,
                                "post_action":  "bash_weapon",
                                "damage_type":  "挫伤"
                        ]),
        });
} 
int valid_learn(object me) {
        if(!::valid_learn(me)) {
                return 0;
        }
		if( (int)me->query_skill("lamaism",1) <= (int)me->query_skill("lamastaff",1)/2) {
                return notify_fail("你的密宗佛法修为不够，无法领悟更高深的密宗杖法。\n");
        }
        return 1;
        
        if((int)me->query("str") + (int)me->query("max_force") / 10 < 35) {
                return notify_fail("你的膂力还不够，也许该练一练内力来增强力量。\n");
        }
        return 1;
}  
int practice_skill(object me)
{
        
        if ((int)me->query("force") < 20) {
                return notify_fail("你的内力不够练密宗杖法。\n");
        }
        if(!::practice_skill(me)) {
                return 0;
        }
        me->add("force", -10);
        return 1;
}
