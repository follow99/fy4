#include <ansi.h> 
inherit ROOM;
void create() 
{ 
    set("short", "密道"); 
    set("long", @long
这条密道四面八方都是路，也不知道到底哪条路是真的，哪条路是假的，
密道有些阴暗，似乎布满杀机。
long 
    ); 
    set("exits", ([ 
    	"east" : __DIR__"midao9", 
    	"south" : __DIR__"midao10",
    	"west" : __DIR__"midao6",
    	"north" : __DIR__"midao3",
        ])); 
    set("indoors","shanxi"); 
set("coor/x",-470);
        set("coor/y",-260);
        set("coor/z",92);
        setup(); 
} 
int valid_leave(object obj, string dir){
        int skills,i,damage;
        string  *dirc = ({ "东", "南", "西", "北" });
        skills=obj->query_skill("perception",1);
        
        if(dir == "west" || dir == "south" || dir == "east" || dir == "north"){
        	if (random(10)>=5) {
            		message_vision(HIR"$N慢慢的摸索前行，突然「嗖嗖嗖」三声，有几道暗器从"+dirc[random(4)]+"面墙壁飞射过来！！\n"NOR, obj); 
            		if( random(skills) < 50 ){
            			message_vision(HIR"暗器疾驰而来，$N躲闪不及，被打了个正着！！\n"NOR,obj);
            			i = (int)obj->query("eff_kee");
        			damage = i/20;
        			obj->set("eff_kee",(int) i - damage );
        			i =  (int)obj->query("kee");
        			obj->set("kee",(int) i - damage);
        			return 1;
            		}
  			else{
  				message_vision(WHT"$N听风辩器，一个跨步躲过了飞射而来的暗器。\n"NOR,obj);
  				return 1;
  			}
                }
        }       
        return 1;
}