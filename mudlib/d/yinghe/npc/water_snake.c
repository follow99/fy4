#include <ansi.h>
inherit NPC;
void use_poison(); 
void create()
{
    set_name(HIW"寒水蛇"NOR, ({ "hanshui snake", "snake" }) );
    set("race", "野兽");
    set("age", 4);
    set("long", "一条全身银白色的小蛇。此蛇据说生长在寒水之处，却又喜爱在沙中畅游，
蛇胆更是珍贵无比。\n");
    set("limbs", ({ "头部", "身体", "尾巴", "七寸" }) );
    set("verbs", ({ "bite" }) );
    set("attitude", "aggressive");
    set_skill("dodge", 50);
    set("combat_exp", 5000000 + random(2000000));
        set("bellicosity", 300 );
    set("chat_chance_combat", 1);
    set("chat_msg_combat", ({
            (: use_poison :),
    }) );
    setup();
        carry_object(__DIR__"obj/shedan");
} 
void use_poison(){
    object *enemy, ob;
    string msg; 
    enemy = query_enemy();
    if( sizeof(enemy) ) ob = enemy[random(sizeof(enemy))]; 
    tell_object(ob,
"你觉得脸上剧痛，伸手一摸发现两个毒牙印痕。\n");
            ob->apply_condition("snake_poison", 
            (int)this_player()->query_condition("snake_poison")
            + random(3)+3);
}      
