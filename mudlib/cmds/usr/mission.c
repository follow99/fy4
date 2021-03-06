 // quest.c
// Copyright (C) 1995 - 2001, by FengYun Workshop. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
//
        
#include <ansi.h>
inherit F_CLEAN_UP;
int time_period(int timep, object me);
int main(object ob, string arg) {
        int i,nowtime,fail_time;
        object me;
        object* mem;
        nowtime = (int)time();
        fail_time = (int)time();
  if(!arg || !wizardp(ob)) {
                me = this_player();

        if(!me->query("have_mission")) write("你现在没有任何组织任务。\n");
        else {
                string mission;
                mission =  me->query("mission/name");
                write("你现在的组织任务是关于【" + mission+ "】。\n");
        nowtime = me->query("mission/mission_time") - (int)time();     //剩余时间
        if(nowtime<=0){
                write(NOR"但是你已经没有足够的时间来完成这个组织任务了。\n");
                me->delete("mission");
                me->set("mission_fail",1);
                me->set("mission_wait",fail_time+600);
                me->set("have_mission",0);
                return notify_fail("这个组织任务自动取消了。\n");
        }else {time_period(nowtime, me);}
        }
  } 

  else {
         if(!(ob = present(arg, environment(ob))) && !(ob =  find_player(arg))) {
                return notify_fail("你要察看谁的组织任务？\n");
        }
        if(!ob->query("have_mission")) {
                return notify_fail(ob->name()+"现在没有任何组织任务！\n");
        } 
        }       
        return 1;
} 
int time_period(int timep, object me) {
        int t, d, h, m, s;
        string time;
        t = timep;
        s = t % 60;             t /= 60;
        m = t % 60;             t /= 60;
        h = t % 24;             t /= 24;
        d = t;
        
        if(d) time = chinese_number(d) + "天";
        else time = "";
        
        if(h) time += chinese_number(h) + "小时";
        if(m) time += chinese_number(m) + "分";
        time += chinese_number(s) + "秒";
        tell_object(me,"你的组织任务还有" + time + "结束。\n");
        return 1;
} 
int help(object me) {
        write(@HELP
指令格式 : mission
 
这个指令可以显示出你当前的组织任务。
HELP);
        return 1;
}    
