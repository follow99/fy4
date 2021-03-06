 // qingfeng-sword.c
// Last modification by neon
// Change: hit_ob action dependes on force_factor instead of force
#include <ansi.h>
inherit SKILL;
void setup() {
        set("name", "清风十三式");
        set("usage/sword", 1);
        set("usage/parry", 1);
        set("practice_damage", 30);
        set("skill_class", "huashan");
        set("effective_level", 120);
        set("practice_limit",180);
        set("learn_bonus", 0);
        set("practice_bonus", -5);
        set("black_white_ness", 10);
        set("unarmed_parry_msg",({
                "$n手中$v慢慢挑起，剑势飘动间如团团落絮随风而起，“清风十三式”中
第六式“落絮轻扬”使出，悠悠漫漫织成一道剑网。\n",
                "$n轻摆$v，剑光若有若无间斜飘而至，使出“清风十三式”中第十一式
“雁阵偏吹”，将$N攻势化于无形。\n",
                "$n如风吹弱柳，微微侧身，反手挥出$v，剑光似片片落霞飘来，以“清风
十三式”中 第十三式“落霞流散”将$N封出。\n",
                                        })      
        );
        action = ({
        ([      "action":               
"$N左手横眉，$w斜削而出，剑光似有似无，出手似快似慢，剑路似实似虚，招式 
将变未变。正是“清风十三式”中的第一式“清风徐来” ",
                "dodge":                100,
                "damage":               533,
                "damage_type":  "割伤"
        ]),
        ([      "action":               
"$N使出“清风十三式”中第八式“风动千铃”。剑光点点流动，如风铃此起彼伏，却 
分不清到底哪一处在响。"NOR,
                "dodge":                120,
                "damage":               540,
                "damage_type":  "刺伤"
        ]),
        ([      "action":               
"$N使出“清风十三式”中第二式“流空萤火”，回剑轻削，飘渺的剑光点点飞来如同
夜空中流萤飞舞，袭向$n$l。",
                "dodge":                100,
                "damage":               550,
                "damage_type":  "割伤"
        ]),
        ([      "action":               
"$N手腕轻抖横剑削来，只见剑意萧萧，飘摇不定，却是“清风十三式”中第三式
“竹外山岚” ",
                "dodge":                270,
                "damage":               50,
                "damage_type":  "割伤"
        ]),
        ([      "action":               
"$N手中$w回掠，似乎意态优闲，停招不发，然而剑势不经意的变幻之间已拂向$n$l，
正是“清风十三式”中第四式“云淡风轻”。",
                "dodge":                150,
                "damage":               5100,
                "damage_type":  "刺伤"
        ]),
        ([      "action":               
"$N左手轻掠划了一个半弧，右手$w连点，使出“清风十三式”中第五式“空穴来风”， 
淡淡的剑气忽然从四面八方掩向$n。",
                "dodge":                100,
                "damage":               50,
                "damage_type":  "刺伤"
        ]),
        ([      "action":               
"$N将$w横持在面前，左手斜挥而下，右手一转将$w平平推出，丝丝剑气飘然而至。 
正是“清风十三式”中第七式“霜笛清晓”。",
                "dodge":                195,
                "damage":               570,
                "damage_type":  "刺伤"
        ]),
        ([      "action":               
"$N手中$w剑势忽左忽右，不断向前飘动，让人分不清方向，然而剑光却渐渐 
涨起，如春风点染绿林。正是“清风十三式”中第九式“绿涨春风”。",
                "dodge":                110,
                "damage":               50,
                "damage_type":  "刺伤"
        ]),                       
        ([      "action":               
"$N使出“清风十三式”中第十式“寒梅落雪”，只见剑势萧疏，剑光清冷， 
如点点落梅在风中飘向$n$l。",
                "dodge":                195,
                "damage":               5120,
                "damage_type":  "刺伤"
        ]),
        ([      "action":               
"$N手中$w轻转，一道道短短的弧光浮现身前，正是“清风十三式”中 
第十二式“风送浮萍”，只见弧光飘动，浮向$n$l。”",
                "dodge":                260,
                "damage":               5130,
                "damage_type":  "割伤"
        ]),     
                   
        });
}
int valid_learn(object me)
{
    if((int)me->query("max_force") < 300 ) {
            return notify_fail("你的内力不够，没有办法练清风剑法。\n");
        }
        if(!::valid_learn(me)) {
                return 0;
        }
    return 1;
}  
mapping query_action(object me, object weapon)
{
        int attack_act;
        object *victims,victim;
        
        attack_act=random(sizeof(action));
        me->set_temp("qingfeng-act",attack_act); 
        return action[attack_act];
} 
int practice_skill(object me)
{ 
   if((int)me->query("force") < 10 ){
        return notify_fail("你的内力或气不够，没有办法练习清风剑法。\n");
    }
    if(!::practice_skill(me)) {
        return 0;
    }   
    me->add("force", -10);
    write("你按著所学练了一遍清风剑法。\n");
    return 1;
}  
mixed hit_ob(object me, object victim)
{       int act;
        int pro;
        int dam;
        int level_bonus;
        
        string damtype;
        object weapon;
        if (me->query_skill_mapped("force") != "hanmei-force")
                return ("");    
        level_bonus = me->query_skill("qingfeng-sword",1);
        act=me->query_temp("qingfeng-act");     
        switch(act) {
                case 2:
                        damtype="kee";
                        break;
                case 5:
                        damtype="gin";
                        break;
                case 8:
                        damtype="gin";
                        break;
                case 9:
                        damtype="sen";
                        break;
                case 1: if (me->query("class")!="huashan") break;
                        if (me->query("combat_exp")<2000000) break;
                        damtype="kee";
                        break;
                case 3: if (me->query("class")!="huashan") break;
                   if (me->query("combat_exp")<2500000) break;
                        damtype="kee";
                        break;
                case 4: if (me->query("class")!="huashan") break;
                        if (me->query("combat_exp")<3500000) break;
                        damtype="kee";
                        break;
                case 6: if (me->query("class")!="huashan") break;
                        if (me->query("combat_exp")<4500000) break;
                        damtype="sen";
                        break;
                }
        if(damtype)
        {
                // To add level bonus, changed 10* to 8*  
                // 03-30-2002
                //  -neon
                dam = 8 * (int) me->query("force_factor");
                dam += 3*level_bonus/2 ;
                pro = victim->query_con();
                if (pro>30)     
                        dam -= (dam*(pro-30))/30;
                victim->receive_damage(damtype,dam,me);
                return (HIY"$n"NOR+HIY"觉得浑身一麻，似乎已被$N的内劲所伤。\n" NOR);
        }               
} 
