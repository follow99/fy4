 // stormdance.c
inherit SKILL;
void setup(){
        set("name", "七宝天岚舞");
        set("usage/dodge", 1);
        set("usage/move", 1);
        set("effective_level", 150);
        set("learn_bonus", 20);
        set("practice_bonus", 20);
        set("black_white_ness", 20);            
        set("dodge_msg", ({
        "但是$n身法轻灵，翩翩地飘了开去！\n"
        }) );
}        
