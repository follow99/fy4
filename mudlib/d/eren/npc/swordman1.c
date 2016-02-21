#include <ansi.h>
inherit SMART_NPC;  
void create()
{
        set_name(HIY"替补"NOR,({"guardian"}));
        set("title","昆仑四鹫");
        set("long", "一个出家的道人，国字脸，通天鼻，双眉斜飞人鬓。\n");
        set("age",30+random(20));
        set("attitude", "friendly");
        set("combat_exp", 4300000);
                
        set("max_mana", 1000);
        set("mana", 1000);
        set("max_force",1500);
        set("force",1500);
        set("force_factor",50); 
        set("resistance/kee",30);
        set("resistance/gin",30);
        set("resistance/sen",30); 
        set("reward_npc", 1);
        set("difficulty", 5); 
        set("inquiry", ([
                "燕南天" : "燕大侠是第一个敢闯入恶人谷的正道中人。\n",
                "恶人谷" : "十大恶人散的散，死的死，恶人谷现在太平多了。\n",
        ]));
        
        set("cor", 40);
        set("cps", 40);
        set("int",40);
        set("agi",40);
        
        set("chat_chance", 1);
        set("chat_msg", ({
                "藏翼子叹道：“常听人言道燕南天武功之强强绝天下，贫道还不深信，
但今日一见……唉，唉……”\n",
                
        }) );
        set("chat_chance_combat", 70);
        set("chat_msg_combat", ({
                (: auto_smart_fight() :),    
        }) );
         
        CHAR_D->setup_char(this_object());
        auto_npc_setup("guardian",200,170,1,"/d/eren2/npc/obj/","fighter_w","softsword");
        set_name("藏翼子",({"zang yizi"}));
        set("force_factor",50);
        setup();
        carry_object("/obj/armor/cloth")->wear();
        
}
