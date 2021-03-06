 // a skeleton for user rooms
#include <ansi.h>
#define X_COOR 15
#define Y_COOR 2041
#define Z_COOR 50
#define R_FLAG 2049
#define OWNER "chuchu"
#define CLASS "白云城"
inherit ROOM;
void create()
{
set("short", "小木屋");
set("long", @LONG
在山深处，在水之滨，在一个远离红尘的绿树林里，搭着一间小小的木屋。 
　　在你饱经忧患，历尽艰苦，出生入死，百战归来的时候，偷半日闲，带一个你
喜欢她、她也喜欢你的女孩子，到这木屋来，做一点你喜欢做她也喜欢做的事，或
者什么都不做。 
　　木屋里有四扇大大的窗子，一个小小的火炉。 
　　如果是夏天，他们就会打开窗子，让来自远山、来自水滨的风吹进窗户来，静
静地呼吸风中从远山带来的木叶芬芳。 
　　如果是冬天，他们就会在小小的火炉里生一堆旺旺的火，在火上架一个小小的
铁锅，温一角酒，静静地看着火焰闪动。 
　　这是他们的世界，宁静的世界。 

LONG
);
        set("exits", ([
	//	"south" : __DIR__"chuchu6",
	]));

        set("item_desc", ([
        	"window": "木制的窗棂，要不要推推看？\n",
        ]) );

        set("coor/x",X_COOR);
   	set("coor/y",Y_COOR);
        set("coor/z",Z_COOR);
        set("room_flag",R_FLAG);
        set("owner", OWNER);
        set("class", CLASS);
        set("indoors","residence");
        setup();
}
void init()
{
        int flag;
        flag = (int) query("room_flag");
        if(flag & 1) set("valid_startroom",1);
        if(flag & 2) set("NONPC",1);
        if(flag & 4) set("no_fight",1);
        if(flag & 8) set("no_magic",1);
        if(flag & 16) set("indoors","residence");
        add_action("do_invite","invite");
        add_action("do_setowner","setowner");
        add_action("do_list","list");
        add_action("do_push","push");
}

int do_push(string arg)
{
	if(arg=="window")
	{
		message_vision(HIC"$N推开窗，月华如水洒落了一地。叶子随风在月影中婆娑，宛如舞着一支唯美的月光竹曲。
不在乎谁吵醒了谁的惊梦，不在乎谁打断了谁的残醉，只在乎与你分享同一个感觉，同一个天地。\n"NOR, this_player());
	        if( !query("exits/out") ) 
	        {
        		set("exits/out", __DIR__"chuchu6");
        		call_out("close_path", 5);
        	}
		return 1;
	}
	return 0;
}

void close_path()
{
        if( !query("exits/out") ) return;
        delete("exits/out");
}

int valid_enter(object me)
{
        int flag;
// means no enter at the beginning.
        int enter = 0;
    flag = (int) query("room_flag");
// always let owner go in:
        if((string)me->query("id") == (string)query("owner"))
        enter = 1;
        if(flag & 16)
        enter = 1;
        if(flag & 512)
        if((string)me->query("id") == (string)query("owner"))
        enter = 1;
        if(flag & 1024)
        if((string)me->query("class") == (string)query("class"))
        enter = 1;
        if(flag & 2048) 
        {
                if(strlen(query("invite")) && strsrch((string)query("invite"),"["+(string)me->query("id")+"]") != -1)
           enter = 1;
        }
//      write(sprintf("%d", enter));    
        return enter;
}
int do_list()
{
        object me;
        string *list,invitelist;
        me = this_player();
        if((string)me->query("id") != (string)query("owner"))
        return 0;
        invitelist = query("invite");
        if (strlen(invitelist))
        {
                list = explode("]"+invitelist+"[", "][");
                write("你邀请了下列玩家到你的房间:\n");
                for(int i=0;i<sizeof(list);i++)
                        write(list[i]+"\n");
        }else
                write("你没有邀请任何人到你的房间。\n");
        return 1;
} 
int do_invite(string arg)
{
        object me;
        string invitelist;
        me= this_player();
        if((string)me->query("id") != (string)query("owner"))
        return 0;
        if( !arg )
        {
                write("你要邀请谁? \n");
                return 1;
        }
        invitelist = (string)query("invite");
        if(strlen(invitelist) && strsrch(invitelist,"["+arg+"]") != -1)
        {
                //if the person has already been invited, remove it from invite list.
                invitelist = replace_string(invitelist,"["+arg+"]","");
           set("invite",invitelist);
                write("你将"+arg+"从你的邀请名单中除去。\n");
        }else
        {
                //invite the person.
                if( find_player(arg))
                {
                        if(!strlen(invitelist))
                                set("invite","["+arg+"]");
                        else
                                set("invite",invitelist+"["+arg+"]");
                        write("你邀请"+arg+"来你的房间。\n");
                }else
                {
                        write("咦... 有这个人吗?\n");
                }
        }
        return 1;
} 
int do_setowner(string arg)
{
        string oldowner;
        oldowner = (string)query("owner");
        set("owner",arg);
        write("你将房间的主人暂时设为"+arg+"。\n");
        call_out("set_back",60, oldowner);
        return 1;
} 
int set_back(string oldowner)
{
        set("owner", oldowner);
        return 1;
}
    
