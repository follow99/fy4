 inherit NPC;
#include <ansi.h>
void create()
{
        set_name(HIC"萧秋水"NOR, ({ "xiao qiushui" }) );
        create_family(HIG"忘忧山庄"NOR,0,RED"统领"NOR);
        set("gender", "男性" );
        set("no_fly",1);
        set("age", 32);
        set("str", 100);
        set("dur",100);
        set("cor", 14);
        set("per", 4);
        set("cps", 29);
        set("int", 25);
        set("long", "负责忘忧山庄安全的统领，此人内功深厚，你最好不要惹他。\n");
        set("chat_chance", 1);
        set("chat_msg", ({
                }) );   
        set("combat_exp", 5000000);
        set("attitude", "friendly");
            
        set("max_force", 5000);
        set("force", 5000);
        set("force_factor", 100);
        set_skill("unarmed",250);
        set_skill("dodge",500);
        set_skill("move",500);
        set_skill("parry",200); 
        set_skill("blade",300);
        set_skill("huanhua-steps",500);
        set_skill("huanhua-sword", 500);
        
        map_skill("sword", "huanhua-sword"); 
        map_skill("dodge", "huanhua-steps");
        map_skill("move",  "huanhua-steps");
        map_skill("parry", "huanhua-sword");
        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: perform_action, "sword.jingtianyijian" :),
                (: perform_action, "dodge.hongyeluanfei" :),
        }) ); 
        setup();
        carry_object("/obj/armor/cloth")->wear();
        carry_object("/obj/weapon/sword")->wield();
} 
 void die(){
         message_vision(RED"$N诡笑一声道：忘忧山庄的人是不死的！\n"NOR, this_object());
        "/cmds/imm/full"->main(this_object(),"");
}      
 void init()
{       
        object ob; 
        ::init();
        add_action("do_killing", "kill");
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}   
void greeting(object ob,object obj)
{    
	object me,qt;
	me=this_player();
        if( !ob || environment(ob) != environment() ) return;   
		if((string)me->query("id") == "xiaolang"){
			 message_vision(MAG"$N看到$n进来，恭敬道：恭迎庄主！\n"NOR,this_object(),ob);
		return;
               }

    if (qt=present("qingtie",me) && me->query_temp("忘忧山庄/请帖")){
    	 message_vision(HIW"$N看到$n进来，微笑道：欢迎来到忘忧山庄，庄主在大厅恭候多时了，请！\n"NOR,this_object(),ob);
    return;}
    else
       message_vision(MAG"$N冷冷的看着$n，凌厉的眼神让$n不寒而栗！\n"NOR,this_object(),ob);
    return;
}

int do_killing(string arg)
{       
        object player, victim, weapon;
        string name,id;
        if(!arg) return 0;
        player = this_player();
        		
        if( objectp(victim = present(arg, environment(this_object()))) && living(victim))
        {
                name = victim->name();
                id = victim->query("id");
                if( id == "xiao qiushui")
                {        
                        if( (string)player->query("id")=="xiaolang" ){
                           message_vision(RED"$N突然想动手杀$n。\n"NOR,player,this_object());
        		               message_vision(HIW"\n萧秋水慌忙向$N下跪道：请庄主赎罪！\n"NOR,player);
        		            return 1;
        		                }
                        if (weapon = present("sword", this_object())) {
                                message_vision(HIW"$N叹了一口气道：在忘忧山庄捣乱的人只有一个字：死！。\n"NOR, this_object());
                                message_vision("$N从腰间抽出佩剑！\n", this_object());
                                weapon->wield();
                                call_out("do_unwie", 3);
                                }
                        return 0;
               }
               if( id == "xiaolang")
               {
                  message_vision(RED"$N冷笑一声道：在忘忧山庄里竟然敢杀庄主，难道不想活了？！\n"NOR, this_object());
                  weapon = present("sword", this_object());
                  if(weapon)
                    {
                    message_vision("$N从腰间抽出一把佩剑。\n", this_object());
                    weapon->wield();
                    }
               this_object()->kill_ob(player);
               player->kill_ob(this_object());
               remove_call_out("do_unwie");
               call_out("do_unwie", 3);
               return 0;
               }
        //
                return 0;
        }
        return 0;               
} 
int do_unwie()
{        

        if( !this_object()->is_fighting())
        {     
                command("unwield sword");
                message_vision(WHT"$N轻轻的放下手中的剑!\n"NOR, this_object());
                command("get sword");
                command("sigh");
                return 1;
        }
        else
                call_out("do_unwie", 3);
} 