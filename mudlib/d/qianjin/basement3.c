 inherit ROOM;
void create()
{
        set("short", "������");
        set("long", @LONG
�ڹ�¡��
LONG
        );
/*        set("exits", ([ 
  "southwest" : __DIR__"hehuadang2",
]));
*/
        set("indoors","qianjin"); 
        set("coor/x",-60);
        set("coor/y",-20);
        set("coor/z",-20);
        
        set("objects", ([
                __DIR__"npc/meihuadao" : 1,
        ]));    
        setup(); 
} 
void init()
{
//        if(!wizardp(this_player()))
//      {
        "/cmds/std/look"->look_room(this_player(),this_object());
//      this_player()->set("startroom", __FILE__);
        add_action("do_nothing", "");
        add_action("do_quit","quit");
//      }
}        
int do_nothing()
{
        if (this_player()->query_temp("marks/meihuadao")) {
                write("�����´󼱣��ٰ�����������Ѩ�����㣬һ��Ҳ���ܶ�����������\n");
                return 1;
        }
        else return 0;
} 
int do_quit()
{
        "/cmds/usr/quit"->main(this_player(),"");
        return 1;
}  