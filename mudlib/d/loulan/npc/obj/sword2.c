 // sword.c : an example weapon
#include <weapon.h>
#include <ansi.h> 
inherit BLADE; 
void create()
{
    set_name(HIW"冰魄寒光刀"NOR, ({ "ice blade","blade" }) );
        set_weight(7000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
        set("long", "冰魄寒光刀,每一刀劈出,俱是冰之魂、雪之魄、霜之灵、寒之胆。\n");
        set("value", 9000);
                set("material", "steel");
        }
    init_blade(70); 
// These properties are optional, if you don't set them, it will use the
// default values. 
        set("wield_msg", "$N「唰」地一声抽出一把$n握在手中。\n");
        set("unwield_msg", "$N将手中的$n插入腰间的刀鞘。\n");  
}   
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int dam;
        dam = (int) me->query("max_gin");
        victim->receive_damage("gin",dam/10,me);
        return HIW "冰魄寒光刀上冻彻入骨的冷意，令$n不由自主地打了个颤抖。\n" NOR;
}  
