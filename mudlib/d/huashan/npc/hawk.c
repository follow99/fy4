#include <ansi.h>
#include <globals.h>
inherit NPC;
string player_env(object target, object me); 
//void eatMeat(object ob);
void create()
{
    set_name(HIC"苍鹰"NOR, ({ "hawk" }) );
    set("race", "野兽");
    set("age", 1);
    set("gender", "雄性");
    set("long","一只勾嘴利爪的苍鹰。它一双凶猛锐利的眼睛正盯着你看，毫无半分退缩之意。 ");
    set("attitude","peaceful");
    set("limbs", ({ "头部", "身体","尾巴" }) );
    set("verbs", ({ "bite","claw" }) );
        set("weight", 3000);
        set("agi", 40);
        set("per",30);
        set("str",150);
        set_skill("move",400);
    set_skill("unarmed",400);
    set_skill("dodge",400);
    set("combat_exp", 50000000);
        set("max_gin", 3000);
    set("max_kee", 3000);
    set("max_sen", 3000);
    set("eff_gin", 3000);
    set("eff_kee", 3000);
        set("eff_sen", 3000);
        set("marks/chained",1);
        set("marks/trained",0);
        set("no_give", 1);
        //set("no_drop", 1);
//    set("unique_amount", 1);  
//    ITEM_D->setup_unique(this_object());  
        setup();
}  
void init() 
{
        ::init();
   add_action("do_catch", "catch");
        add_action("do_feed","feed");
        add_action("do_chain","chain");
        add_action("do_train","train");
        add_action("do_drop","drop");
} 
int checkChained()
{
        
        object hawk;
        hawk = this_object();
        if (hawk->query("marks/chained"))
        {
                object room;
                room = find_object("/d/huashan/fupi");
                if(environment() == room && room->query("item_desc") == 0)
                {
                        room->set("item_desc", ([
                        "chain": "一条系鹰用的细细的黑色铁链，似乎竟是玄铁做的。\n 你在想，不知道开铁链的钥匙在哪里。也许可用什么试试砍断(chop)它。 \n",
                        "铁链":"一条系鹰用的细细的黑色铁链，似乎竟是玄铁做的。 \n 你在想，不知道开铁链的钥匙在哪里。也许可用什么试试砍断(chop)它。\n",
                        ]) );
                }
                //return notify_fail("苍鹰的脚上还系着铁链呢！ \n");
                return 1;
        }
        return 0;
}  
int do_catch(string arg) 
{
        object me, hawk, chain, *inv;
        object hawktrainer;
        int i;
        me = this_player();
        hawk=this_object();
        if(!arg || (arg != "hawk" && arg != "苍鹰")) 
        {
                return 0;
        }
        if(!(present(hawk, environment(me))) || hawk->query("marks/trained"))
        {
        return 0;
    }
        
        if (hawktrainer=present("trainer",environment(hawk)))
        {
                message_vision(RED"$N对$n大吼一声：想打我猎鹰的主意！你活得不耐烦了！ \n"NOR,
                       hawktrainer,this_player());
        hawktrainer->kill_ob(this_player());
        this_player()->start_busy(2);
        return 1;
        }
        if (checkChained())
        {
                return notify_fail("苍鹰的脚上还系着铁链呢！ \n");
        }
        
        if (random(4))
        {
                message_vision(HIW"苍鹰一声厉叫，警告$N不要靠近。\n"NOR,me);
        }
        else
        {
                message_vision(HIR"苍鹰一鼓翅膀，腾身而起，一双利爪抓向$N面前！\n"NOR,me);
                inv = all_inventory(me);
                for (i=0;i<sizeof(inv);i++ )
                {
                        //write (inv[i]->name()+":"+inv[i]->query("equipped")+"\n");
                        if (objectp(inv[i]) && (inv[i]->name()==YEL"眼罩"NOR) && (inv[i]->query("equipped")=="worn"))
                        {
                                message_vision(HIW"苍鹰的双爪啪地击在$N的眼罩上，好险啊。。。 \n"NOR,me);
                                return 1;
                        }
                }               
                // will be blind sob
                tell_object(me, HIR"你双眼一阵剧痛！ \n 你的眼前一片漆黑。。。 \n"NOR);
                me->set_temp("block_msg/all", 1);
        }
        return 1;
} 
void eatMeat(object me)
{
        int avai,remain;
        object hawk,wolfmeat;
        hawk = this_object();
        call_out("eatMeat",20,me);
        if (!present(hawk,me))
        {
                remove_call_out("eatMeat");
                message_vision("$N长啸一声，向长空飞去。\n",hawk);
                destruct(hawk);
        }
        if (wolfmeat = present("wolfmeat",me))
        {
                remain = (int)wolfmeat->query("food_remaining") * (int)wolfmeat->query("food_supply");
                avai = 100;
                //avai = (int)hawk->max_food_capacity() - (int)hawk->query("food");
                //make avai a certain amount to make hawk eat faster
                if( remain > avai )
                {
                        add("food_remaining", -(avai/(int)wolfmeat->query("food_supply")));
                }
                else
                {
                        //hawk->add("food",remain);
                        wolfmeat->set("food_remaining", 0);
                }
                        wolfmeat->set("value", 0);
                        if( !wolfmeat->query("food_remaining") ) 
                        {
                                //meat is gone
                                message_vision("$N将剩下的" + name() + "吃得乾乾净净。\n", hawk);
                                if( !wolfmeat->finish_eat() )
                                        destruct(wolfmeat);
                                message_vision("$N吃完$n手中的肉，腾身向空中飞去。\n",hawk,me);
                                me->clear_condition("hawk_claw");
                                remove_call_out("eatMeat");
                                destruct(hawk);
                        }
                        else 
                                message_vision("$N叼起$n咬了几口。\n", hawk,wolfmeat);
   }
        else
        {
                //dunno why have to do this
                message_vision("$n手中的肉被吃完了，$N腾身向空中飞去。\n",hawk,me);
                me->clear_condtion("hawk_claw");
                remove_call_out("eatMeat");
                destruct(hawk);
        }
        return ;
} 
int do_drop(string arg)
{
        object me,hawk;
        hawk = this_object();
        me = this_player();
        if (arg != "hawk" && arg !="苍鹰")
        {
                return 0;
        }
        //seems no need to check so many status, just for caution
        if(!present(hawk, me) || hawk->query("marks/owner"))
        {
                return 0;
        }
        me->clear_condtion("hawk_claw");
        remove_call_out("eatMeat");
        if (hawk->query("marks/feeding"))
        {
                message_vision("$N手臂吃痛，不禁将苍鹰放了下来。\n",me);
        }
        message_vision("苍鹰在空中盘旋几圈，腾身飞去。\n",me);
        destruct(hawk);
        return 1;
}
     
int do_feed(string arg)
{
        object me;
        object wolfmeat,leathersleeves,hawktrainer;
   object hawk;
        string argmeat, arghawk;
        hawk = this_object();
        me = this_player();
        if(!(present(hawk, environment(me))) || hawk->query("marks/trained"))
        {
        return 0;
    }
        if(!arg) 
        {
                return notify_fail("你要喂谁什麽东西？\n");
    }
    if(sscanf(arg, "%s to %s", argmeat, arghawk)==2 || sscanf(arg, "%s %s", arghawk, argmeat)==2 );
    else 
        {
                return 0;
    }
    
        if (argmeat !="wolfmeat" && arg !="狼肉脯" && arghawk != "hawk" && arghawk != "苍鹰")
        {
                return 0;
        }
        if (checkChained())
        {
                return notify_fail("苍鹰的脚上还系着铁链呢，不能飞过来吃肉！\n");
        }
        if (hawktrainer = present("hawk trainer",this_object()))
        { 
        message_vision(RED"$N对$n大吼一声：想打我猎鹰的主意！你活得不耐烦了！ \n"NOR,
                       hawktrainer,me);
        hawktrainer->kill_ob(me);
        me->start_busy(2);
        return 1;
    }
        if (!wolfmeat=present("wolfmeat",me))
        {       
                return notify_fail("你身上没有这样东西 \n");
        }
        message_vision("$N试着拿出狼肉脯逗引苍鹰。\n ",me);
        if (random(10) && me->query("per")<=20)
   {
                message_vision("苍鹰犹疑不定地看着$N。\n" ,me);
                return 1;
        }
        if (hawk->move(me))
        {
                message_vision("苍鹰飞上$N的手臂，从$N手里叼过狼肉脯吃了起来。\n",me);
                if (!leathersleeves=present("leather sleeves",me))
                {
                        me->apply_condition("hawk_claw",10);
                }
                hawk->set("marks/feeding",1);
                call_out("eatMeat",10,me);
        }
        else
        {
                tell_object(me,"你现在无法承受苍鹰的重量。\n");
        }
        return 1;
} 
int do_chain(string arg)
{
        object hawk, me,chain;
        hawk = this_object();
        me = this_player();
        if (!present(hawk,me) || !hawk->query("marks/feeding") || hawk->query("marks/trained"))
        {
                return 0;
        }
        if (arg != "hawk" && arg !="苍鹰")
        {
                return 0;
        }
        
        if (!chain = present("chain",me))
        {
                return notify_fail("你要用什么系苍鹰 \n");
        }
        message_vision("$N趁$n忙着吃狼肉脯，轻轻地把一段小铁链系在它脚上。\n",me,hawk);
        destruct(chain);
   hawk->set("marks/feeding",0);
        //now we can stick hawk with the player
        set("no_drop", 1);
        hawk->set("marks/owner",me->name());
        me->clear_condition("hawk_claw");
        remove_call_out("eatMeat");
        return 1; 
}
int do_train(string arg)
{
        object me,hawk;
        hawk = this_object();
        me = this_player();
        if (!present(hawk,me) || hawk->query("marks/owner") != me->name() || hawk->query("marks/trained"))
        {
                return 0;
        }
        if (arg != "hawk" && arg != "苍鹰")
        {
                return 0;
        }
        if (me->query_skill("animal-training") < 300)
        {
                return notify_fail("你的训兽术还不够高！\n");
        }
        message_vision("$N耐心的训练$n,$n似乎听懂了$N的话，振翅向天空盘旋了几圈又落在了$N的肩上。\n",me,hawk);
        set("marks/trained",1);
        set_name(HIC"猎鹰"NOR, ({ "hawk" }) );
    set("long","一只听话的猎鹰，它可以帮你侦察（SPY）情况。");
        add_action("do_spy","spy");
        return 1;
}
void spy_player(object target, object me)
{
        if (!target)
        {
                delete("marks/inspy");
                remove_call_out("spy_player");
                tell_object(me,"猎鹰向你汇报道：你要侦察的人离开了 \n");
        }
   if (!present(this_object(),me))
        {
                delete("marks/inspy");
                remove_call_out("spy_player");
                tell_object(me,"猎鹰已经离你而去，不能继续为你侦察。 \n");
                destruct(this_object());
        }
        call_out("spy_player",10,target,me);
        set("marks/inspy",1);
        tell_object(me,"猎鹰振翅向天空盘旋了几圈落在了你的肩上 \n");
        tell_object(me,"猎鹰向你汇报道：\n");
        tell_object(me,player_env(target,me));
}
int do_spy(string arg)
{
        object hawk,me,target;
        hawk = this_object();
        me = this_player();
        if (!present(hawk,me) || hawk->query("marks/owner") != me->name() || !hawk->query("marks/trained"))
        {
                return 0;
        }
        if (!arg)
        {
                return notify_fail("你想侦察谁的情况？(spy none 如果你想停止现存侦察)\n");
        }
        if (arg=="none")
        {
                delete("marks/inspy");
                remove_call_out("spy_player");
        }else
        {
                target = find_living(arg);
                if (!target || !userp(target))
                {
                        return notify_fail("猎鹰不满的看着你，似乎在说：老大，没有这个人耶！\n");
                }
                if (wizardp(target))
                {
                        // will ban them to spy wizard , grin
           }
                if (query("marks/inspy"))
                {
                        return notify_fail("猎鹰不满的看着你，似乎在说：老大，不要虐待动物。先停止侦察这个人再说 ！(spy none) \n");
                }
                spy_player(target,me);
        }
        return 1;
} 
string player_env(object target,object me) {
        int i;
        object *inv,env;
        mapping exits;
        string roomdesc, str, *dirs;
        env = environment(target); 
        if(!env) {
                return target->name() + "的四周灰蒙蒙地一片，什麽也没有。\n";
        }
        if (!env->query("outdoors"))
                str = target->name() + "好象在 \n";
        else
                str = "";
        
        // room descriptions.
        str += sprintf( "%s \n    %s",
                        env->query("short"),
                        //wizardp(target)? file_name(env)+sprintf(" - (%d,%d,%d)",env->query("coor/x"),
                        //              env->query("coor/y"),env->query("coor/z")): "",
                        //env->long(),
                        env->query("outdoors")? NATURE_D->outdoor_room_description() : "" ); 
        // exits.
        if(mapp(exits = env->query("exits"))) {
                dirs = keys(exits);
                for(i=0; i<sizeof(dirs); i++) {
                        if((int)env->query_door(dirs[i], "status") & 1 ) {
                                dirs[i] = 0;
                        }
                }
                dirs -= ({ 0 });
                if(sizeof(dirs)==0) {
                   str += "    这里没有任何明显的出路。\n";
                } else if(sizeof(dirs)==1) {
                        str += "    这里唯一的出口是 " + BOLD + dirs[0] +NOR + "。\n";
                } else {
                        str += sprintf("    这里明显的出口是 " + BOLD + "%s" +NOR + 
                                        " 和 " + BOLD + "%s" +NOR + "。\n",
                                        implode(dirs[0..sizeof(dirs)-2], "、"), dirs[sizeof(dirs)-1]);
                }
        } else {
                str += "    这里没有任何明显的出路。\n";
        }
        
        // all things in the room.
        inv = all_inventory(env);
        for(i=0; i<sizeof(inv); i++) {
                if( inv[i]->query("no_shown") || !me->visible(inv[i])) {
                        continue;
                }
                str += "  " + inv[i]->short() + "\n";
        }
        return str;
}        
