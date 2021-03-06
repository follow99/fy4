 // - by neon
#include <ansi.h>
inherit F_CLEAN_UP;
void move_team(object me,object ob);
int main(object me, string arg)
{
        string what, who;
        object ob, *team;
        int i, delay;
        object where = environment(me);
        if ( me->query("class")!="beggar" )
          return notify_fail("只有丐帮弟子才能飞鸽传书！\n"); 
        if( environment(me)->query("no_beg") ||environment(me)->query("no_magic")
                || environment(me)->query("no_fly")
        )
                return notify_fail("这里是不适合丐帮弟子使用飞鸽传书！\n"); 
        if( me->is_busy() )
                return notify_fail("你现在正在忙！\n"); 
        if( me->query_temp("inform_in_progress") )
                return notify_fail("你的信鸽正在接引队友！\n"); 
        if( !arg ) return
                notify_fail("指令格式：inform <某人>\n"); 
        if ( (int)me->query_skill("begging",1) < 100 
                || me->query("combat_exp")<2000000
                || !me->query("open_sesame") )
        {
                return notify_fail("你现在还没有能力使用飞鸽传书。\n");
        } 
        if( !pointerp(team = me->query_team()) )  
                return notify_fail("你并没有任何队友！\n");
                
        ob = find_player(arg);
        if (!ob || ob == me) return notify_fail("你要飞鸽传书给谁？\n");
        for ( i=0; i<sizeof(team); i++) {
                if (team[i]==ob ) break;
        }
        if (i == sizeof(team)) return notify_fail("飞鸽不能传书给队伍以外的人。\n");
// Now start to summon 
        if (environment(ob) == environment(me)) return notify_fail(ob->name() + "已经在你身边了！\n");
        
        message_vision(WHT"$N忽然一举手，一只白色的信鸽腾空而起，在振羽声中飞向远方。\n"NOR, me);
        me->set_temp("inform_in_progress", 1);
        
        if(environment(ob)->query("no_magic")) {
                message_vision(WHT"\n但是，信鸽在远方盘旋了一会儿，又飞回$N手里。\n"NOR, me);   
                me->delete_temp("inform_in_progress", 1) ;
                write("信鸽无法发现你的队友！\n");
                return 1;
        }
                        
        if (ob->is_busy() || ob->is_fighting()) {
                message_vision(WHT"\n但是，信鸽在远方盘旋了一会儿，又飞回$N手里。\n"NOR, me);   
                me->delete_temp("inform_in_progress", 1);
                write(ob->name()+"似乎没有空闲来接收信鸽。\n");
                return 1;
        }
        message_vision(WHT"一只白色的信鸽忽然飞来，在$N头顶上下飞动，一个盘旋，向远处飞去。\n$N面色一凛，立刻展开轻功，追随飞鸽而去。\n"NOR, ob);        
        tell_object(ob, "\n ... \n你加快脚步，在信鸽指引下向前急奔。\n");       
        
        delay = 500/ (1 + ob->query_skill("move")) + 1;
        delay = delay >5 ? 5 : delay;
        delay = delay <2 ? 2 : delay;
        ob->start_busy(delay +1);
        me->start_busy(delay +1);
        call_out("move_team",delay, me,ob);     
        return 1;       
}  
void move_team(object me, object ob){
        
        message_vision(WHT"信鸽划过一道白色的弧线，飞回到$N手里。$n在后面匆匆赶到。\n"NOR, me, ob);     
        ob->move(environment(me));
        me->delete_temp("inform_in_progress", 1);
} 
int help(object me)
{
write(@HELP
指令格式 : inform <他人>
飞鸽传书，这是一个丐帮专用的指令，可以呼唤队友的帮助。 
HELP
    );
    return 1;
}  
