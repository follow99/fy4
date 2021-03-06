 // xiaohun-whip.c
#include <ansi.h>
inherit SKILL;
int check_skill(object victim) ; 
void setup(){
        set("name", "黯然销魂鞭法");
        set("usage/whip", 1);
        set("usage/parry", 1);
        set("practice_damage", 100);
        set("effective_level", 330);
        set("learn_bonus", -850);
        set("practice_bonus", -300);
        set("black_white_ness", 0);     
        set("skill_class", "new");
        set("parry_msg", ({
                "$n手中$v如一片柳絮，轻飘飘地飞起，一式[暗柳萧萧]将$N迫退。\n",
        "鞭光流散，$n黯然低首，[迷离晓梦啼莺] 随心而发，点点鞭影零落
飘来，$N顿时有不知所措的感觉。\n",
        }) ); 
        set("unarmed_parry_msg", ({
                "$n手中$v如一片柳絮，轻飘飘地飞起，一式[暗柳萧萧]将$N迫退。\n",
        "鞭光流散，$n黯然低首，[迷离晓梦啼莺] 随心而发，点点鞭影零落
飘来，$N顿时有不知所措的感觉。\n",
        }) );
        
        action = ({
        ([      "action":               
"$N一展$w，一招[旧时月色]鞭光朦胧，如梦如幻，洒向$n。。。 ",
                //"dodge":                50,
                "damage":               530,
                "damage_type":  "刺伤"
        ]),
        ([      "action":               
"$N的$w轻摆，如萧萧凉风拂过竹林，给人如在梦镜的感觉。忽然间，
几点鞭光闪出飞向$n，正是黯然销魂鞭法的[竹外疏花]。",
                //"dodge":                120,
                "damage":               630,
                "damage_type":  "刺伤"
        ]),
        ([      "action":               
"$N缓缓一鞭推出，一招[夜雪初积]，只见鞭光如织盖向$n",
                //"dodge":                155,
                "damage":               850,
                "damage_type":  "割伤"
        ]),
        ([      "action":               
"$N回鞭反削，使出[红萼无言]，片片鞭影飞起，却寂然无声，点点笼向$n",
                "dodge":                300,
                "damage":               320,
                "damage_type":  "刺伤"
        ]),
        ([      "action":               
"$N神情落寞，手中$w向下斜指。$w忽然色转苍碧，黯然销魂鞭法的绝技
[幽阶一夜苔生]已经发出，鞭气波动，如苍苔铺地向$n卷来。",
//                "dodge":                150,
                "damage":               1500,
                "damage_type":  "刺伤"
        ]),
        });
}
int valid_learn(object me)
{
       /*if (!me->query("m_success/销魂传人") && (me->query("class")!="swordsman") )
                return notify_fail("蓝一尘的销魂鞭法已有传人了，学他的销魂鞭法吧。\n");*/
        
        if( (int)me->query("max_force") < 100 ){
            return notify_fail("你的内力不够，没有办法练黯然销魂鞭法。\n");
        }       
        if(!::valid_learn(me)){
                return 0;
        }
        return 1;
} 
/*int practice_skill(object me)
{
        return notify_fail("黯然销魂鞭法只能用学的。\n");
} */
mapping query_action(object me, object weapon) 
{
        int act;
   act=random(sizeof(action));
        me->set_temp("xiaohun-act",act);
        return action[act]; 
} 
string query_parry_msg(object weapon) {
        mapping msg;
        int act;
        
        if(objectp(weapon)) {
                msg = skill_attr["parry_msg"];
        }
        
        if(sizeof(msg) == 0) {
                msg = skill_attr["parry_msg"];
        }
       if(sizeof(msg) > 0) {
                act=random(sizeof(msg));
                this_player()->set_temp("xiaohun-parry",act);
                return msg[act];
        }
        
        return 0;
} 
mixed hit_ob(object me, object victim){ 
        int act, pro, dam;
        
        act=me->query_temp("xiaohun-act");      
        if(act==1)
        {
                dam = (int) me->query("max_force");
                dam = (random(dam)+dam)/2;
                pro = victim->query("con");
                if (pro>30)
                {
                        dam = dam*(1-(pro-30)/30);
                }
                victim->receive_damage("sen",dam/10);
                return (HIY "$n只觉黯然神伤，神智逐渐模糊起来。\n" NOR);
        }
        if(act==4)
        {
                dam = (int) me->query("max_force");
                dam = (random(dam)+dam)/2;
                pro = victim->query("con");
                if (pro>30)
                {
                        dam = dam*(1-(pro-30)/30);
                }
                victim->receive_damage("sen",dam/10);
                return (HIY "$n只觉黯然神伤，神智逐渐模糊起来。\n" NOR);
        }
} 
mixed parry_ob(object victim, object me)
{       int busy_time,alr_busy_time;
        int level;
        if (victim->query("race")=="野兽") return 0;
        if (victim->query_temp("xiaohun-parry")!=1)     return 0;
        //if (!check_skill(victim)) return 0;
        level = me->query_skill("xiaohun-whip",1);
        if (level < 50) return 0;
        alr_busy_time=victim->query_busy();
        
        busy_time=random(level/40);
        if(!busy_time) return 0;
        if(busy_time>alr_busy_time)     victim->start_busy(busy_time);
        return HIB"$N"HIB"被$n"HIB"的鞭招所惑，一时竟忘了如何反应。\n"NOR;
}         
int check_skill(object victim) {
        
        object weapon;
        
        if (weapon=victim->query_temp("weapon"))
        if (weapon->query("skill_type")=="blade" && victim->query_skill("blade",1)>100 
                && victim->query_skill("shenji-blade",1)>100
                && victim->query_skill_mapped("blade")=="shenji-blade")
                return 0; 
        return 1;
}        

/*mixed hit_ob(object me, object victim, int damage_bonus)
{
    object ob;
    if( random(damage_bonus) < 100 ) return 0;
    if(ob=victim->query_temp("weapon"))
    if((ob->query("skill_type") == "blade")||(ob->query("skill_type") == "sword")||(ob->query("skill_type") == "dagger"))
    if(
      (victim->query_skill_mapped("blade") == "moon-blade" )
||     ( victim->query_skill_mapped("blade") == "demon-blade" )
  ||    (victim->query_skill_mapped("blade") == "shenji-blade" )
    ||  (victim->query_skill_mapped("blade") == "xiruo-blade" )
      ||(victim->query_skill_mapped("sword") == "spring-sword" )
||      (victim->query_skill_mapped("sword") == "feixian-sword" )
  ||    (victim->query_skill_mapped("sword") == "doom-sword" )
    ||  (victim->query_skill_mapped("sword") == "hanshan-sword" )
      ||(victim->query_skill_mapped("dagger") == "xinyue-dagger" )
||      (victim->query_skill_mapped("dagger") == "yuping-dagger" )     )
    if((me->query_skill("whip")*5 > victim->query_skill("blade")*2)
||    (me->query_skill("whip")*5 > victim->query_skill("sword")*2)
||(me->query_skill("whip")*5 > victim->query_skill("dagger")*2))
       {
    switch(random(3)) {
            case 0:
message_vision(HIR "\n因武功路数相克，$N占尽了上风！" NOR,me,victim);
                    break;
            case 1:
                   message_vision(HIR "\n$N轻而易举地抢入$n的空隙之间！" NOR,me,victim);
                    break;
            case 2:
 message_vision(HIR "\n因刀剑相克，$n逐渐施展不开了！" NOR,me,victim);
                    break;
                    }
    return random(me->query_skill("sword")) * 5;
    }
    return 0;
 }*/