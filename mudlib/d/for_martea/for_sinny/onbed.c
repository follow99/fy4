#include  <ansi.h>
#include  <command.h>
//inherit  F_DBASE;
inherit ROOM;
void create()
{
        set("short","牙玉软榻上");
        set("long",@LONG         
一张牙玉色的软榻，榻四周雕着竹叶格，看上去极为精致，纱
衾鸳枕之间散发出一丝丝幽香．
LONG
        );
    set("exits", ([ /* sizeof() == 4 */
                "out" : VOID_OB,
                ]));
                set("no_fight",  1);
                set("no_magic",  1);
                set("sleep_room",1);
                set("if_bed",1);
        setup();
} 
void init()
{
//      add_action("do_out","go");
        add_action("do_look","look");
        add_action("do_sleep","sleep");
} 
int valid_leave(object me, string dir)
{
        object env;
        if( dir!="out") return 1;
        env=environment(query("exit"));
        if( !env) return 1;
        message_vision("$N掀开纱帐，出去了。\n", me);
        me->move(env);
        message_vision("$N从床上爬了出来。\n",me);
        return 0;
} 
int do_look(string arg)
{
   object env;
        if( arg!="out" ) return 0;
        env=environment(query("exit"));
        if( !env) return 0;
        "/cmds/std/look"->look_room(this_player(),env);
        return 1;
}  
int do_sleep(string  arg)
{
        object  obj,  old_target;
        int  i;
        object  *inv;   
        object  where;
        object me;
        object mother,father;
        mapping pregnancy;
        me=this_player();
        where =  this_object();
        if(  !query("sleep_room") ) 
                {
                write(HIY"这里不是睡觉的地方。\n"NOR);
                return 1;
                }
        if  (me->is_busy())
                {
                write(HIY"你正忙着呢！。\n"NOR);
                return 1;
                }
        if(  me->is_fighting()  )
                {
                write(HIY"你现在能自保。\n"NOR);
                return 1;
                }
    if  ((time()-me->query("last_sleep"))<90)
                        {
                        write(HIR"你刚睡过一觉,  先活动活动吧。 \n"NOR);
                        return 1;
                        } 
//              return  notify_fail(HIR"你刚睡过一觉,  先活动活动吧。  \n"NOR);
    if((!arg)||arg==(string)me->query("id"))
            {
            write(HIY"一个人睡觉，多无聊啊！\n"NOR);
                        return  1;
                        }
        if(!objectp(obj  =  present(arg,  where))) {
                        write("你想跟谁一起睡？\n");
                        return 1;
                        } 
        if(  !obj->is_character()  ) {
                write("？脑袋出毛病了？\n");
                return 1;
                } 
        if(  !userp(obj)  ) {
                write("人家可不愿理你！\n");
                return 1;
                }
        //can't  sleep  with  npc... 
        if(me->query("gender")==obj->query("gender"))   {
                write("？对方跟你可是同性呢．．．\n");
                return 1;
                } 
        if(  !living(obj)  ) {
                write(obj->name()  +  "没法跟你睡了。\n");  
                return 1;
                } 
        if  (!where->query("if_bed"))   {
                write("就在这里？不太好吧。\n");
                return 1;
                }
        if( me->query("gender")=="女性" ) {
                        mother=me;
                        father=obj;
                } else {
                        father=me;
                        mother=obj;
                } 
//if( mapp(pregnancy=mother->query("pregnancy") )       )
                if(      mother->query("pregnancy"))
                        if( me==mother ) {
                                write("你还是照顾一下身体吧。 \n");
                           return 1;
                        }
        if(  (int)me->query("kee")  *  100  /  (int)me->query("max_kee")  <  50  ) {
                write("你现在是心有余而力不足。\n");
                return 1;
                } 
        if(  userp(obj)  &&  (object)obj->query_temp("pending/sleep")!=me  )  {
                message_vision(RED  "\n$N含情脉脉地对$n说：我．．．\n\n"  NOR,  me,  obj);
                if(  objectp(old_target  =  me->query_temp("pending/sleep"))  &&!((string)old_target->query("id")==(string)obj->query("id")))
                        tell_object(old_target,  YEL  +  me->name()  +  "改变主意不想跟你睡了。\n"  NOR);
                me->set_temp("pending/sleep",  obj);
                tell_object(obj,  YEL  "看来"  +  me->name()  +
                "("+(string)me->query("id")+")"+  
                "很想跟你．．．如果你愿意，请也下一次  sleep  指令。\n"  NOR);
                write(YEL  "对方正在考虑中．．．\n"  NOR);
                return  1;
        } 
                message_vision(RED  "\n$N冲着$n会心地一笑，点了点头。\n\n"  NOR,  me,  obj);
                
//      inv  =  all_inventory(me);
//        for(i=0;  i<sizeof(inv);  i++)
//            REMOVE_CMD->do_remove(me,  inv[i]);
//      inv  =  all_inventory(obj);
//                                for(i=0;  i<sizeof(inv);  i++)
//            EMOVE_CMD->do_remove(obj,  inv[i]);
        
        
        if(me->query("gender")=="男性"){
                tell_object(me,  HIY  "\n\n你搂着"+obj->query("name")+
                "温软的身体，不由得心醉神迷．．．\n\n\n"  NOR);
                tell_object(obj,  HIY  "\n\n你躺在"+me->query("name")+
                "的怀里，不由得心醉神迷．．．\n\n\n"  NOR);
        }
        else{
                tell_object(obj,  HIY  "\n\n你搂着"+me->query("name")+
                "温软的身体，不由得心醉神迷．．．\n\n\n"  NOR);
                tell_object(me,  HIY  "\n\n你躺在"+obj->query("name")+
                "的怀里，不由得心醉神迷．．．\n\n\n"  NOR);
        }
                me->set("last_sleep",time());
           obj->set("last_sleep",time());
                me->set_temp("block_msg/all",1);
                obj->set_temp("block_msg/all",1);
                message_vision(HIY  "$N和$n钻入被中，搂在一起睡着了．．．\n\n\n"  NOR,me,obj);
                
        me->disable_player("<睡梦中>");
        obj->disable_player("<睡梦中>"); 
        call_out("wakeup",random(45  -  me->query("con"))  +  10,  me,obj,  where);
        call_out("wakeup",random(45  -  obj->query("con"))  +  10,  obj,  me,where);
                
        return  1; 
} 
int  wakeup(object  me,object slept ,object  where)
{
        int  kee_cost,times_sleep;
    object  obj; 
        kee_cost=50+5*((int)me->query("str")-(int)me->query("con"));
        if(kee_cost>(int)me->query("max_kee")/2)        
                kee_cost=(int)me->query("max_kee")/2+1;  
                me->set("sen",(int)me->query("max_sen"));
                if  ((int)me->query("mana")  <  (int)me->query("max_mana"))
                me->set("mana",  (int)me->query("max_mana"));
                me->add("kee",  -kee_cost);      
        me->enable_player();
        times_sleep=me->query("times_sleep");
        me->set("times_sleep",times_sleep+1);
  
        while(  environment(me)->is_character()  )
                me->move(environment(environment(me))); 
                if(me->query("gender")=="男性"){
                        message_vision(HIY  "$N醒了过来，似乎还沉浸在幸福之中。\n"  NOR,me);
                        me->set_temp("block_msg/all",  0);
                        write("你醒了过来，似乎还沉浸在幸福之中。\n");
                   return  1;
                                }
                else{
                        message_vision(HIY  "$N醒了过来，脸上还挂着甜蜜的笑容。\n"  NOR,me);
                        me->set_temp("block_msg/all",  0);
               write("你醒了过来，脸上还挂着甜蜜的笑容。\n");
                        if( obj && random(times_sleep)>25 && me->query("age")>16 && me->query("age")<60) 
                           call_out("make_pregnancy",3,me,slept);
                        return 1;
                        }
}                        
void make_pregnancy(object me,object obj)                       
                        
        {
                                int str,cor,inti,spi,cps,per,con,agi,dur,fle,tol,kar;
                                me->set("pregnancy/father", obj->query("id") );
                                        me->set("pregnancy/father_name", obj->query("name") );
                                me->set("title_old",me->query("title"));
                                me->set("title","孕妇");
                                        if( random(100)>48) 
                                        me->set("pregnancy/gender","男性");
                                else
                                        me->set("pregnancy/gender","女性");
                                str= (me->query("str")+obj->query("str"))/2-15-random(3);
                                if(str<1)       str=1;
                                cor= (me->query("cor")+obj->query("cor"))/2-15+random(3);
                                inti= (me->query("int")+obj->query("int"))/2-15+random(3);
                                spi= (me->query("spi")+obj->query("spi"))/2-15+random(3);
                                cps= (me->query("cps")+obj->query("cps"))/2-15+random(3);
                                per= (me->query("per")+obj->query("per"))/2-15+random(3);
                                con= (me->query("con")+obj->query("con"))/2-15+random(3);
                                agi= (me->query("agi")+obj->query("agi"))/2-15+random(3);
                                fle= (me->query("fle")+obj->query("fle"))/2-15+random(3);
                                dur=  (me->query("dur")+obj->query("dur"))/2-15+random(3);
                                tol= (me->query("tol")+obj->query("tol"))/2-15+random(3);
                                kar= (me->query("kar")+obj->query("kar"))/2-15+random(3);
                                if(cor<1)       cor=1;
                                if(inti<1)      inti=1;
                                if(spi<1)       spi=1;
                                if(cps<1)       cps=1;
                                if(per<1)       per=1;
                                if(con<1)       con=1;
                                if(agi<1)       agi=1;
                                if(fle<1)       fle=1;
                                if(dur<1)       dur=1;
                                if(tol<1)       tol=1;
                                if(kar<1)       kar=1;
                           if(cor>15)      cor=15;
                                if(inti>15)     inti=15;
                                if(spi>15)      spi=15;
                                if(cps>15)      cps=15;
                                if(per>15)      per=15;
                                if(con>15)      con=15;
                                if(agi>15)      agi=15;
                                if(fle>15)      fle=15;
                                if(dur>15)      dur=15;
                                if(tol>15)      tol=15;
                                if(kar>15)      kar=15;
                                me->set("pregnancy/str", str);
                                me->set("pregnancy/cor",cor);
                                me->set("pregnancy/int", inti);
                                me->set("pregnancy/spi",spi);
                                me->set("pregnancy/cps",cps);
                                me->set("pregnancy/per",per);
                                me->set("pregnancy/con",con);
                                me->set("pregnancy/agi",agi);
                                me->set("pregnancy/dur",dur);
                                me->set("pregnancy/fle",fle);
                                me->set("pregnancy/tol",tol);
                                me->set("pregnancy/kar",kar);
                                me->apply_s_condition("pregnancy", 72000); 
}    
