 //Created by justdoit at May 2001
//All Rights Reserved ^_^ 
 
inherit ROOM; 
void create() 
{ 
        set("short", "����ͤ"); 
        set("long", @LONG 
�㲻֪����ʲô���ڡ������컨�����䣬��ͤ��Ȼ��һ����Ȫ��ͤ�ϵ�й���¡� 
���齦�񡣱�Ϧ��һӳ�����߲����⡣�������ɷ������Ȼ��������ط��������� 
�����ϡ����������紵�����㲻����Щ���ˡ����ã����ع�������ͤ�����ң�
                           ��    ��
                           ��    ɽ
                           Ū    ��
                           ��    ��
LONG 
           ); 
        set("exits",  
           ([  
       "northeast" : __DIR__"yuhuage",
       "southup" : __DIR__"dragonplace",
//           "west"  : __DIR__"beach1", 
//           "east"  : __DIR__"beach2", 
            ])); 
    set("resource/water", 1);
    set("liquid/container", "��Ȫ");    
        set("objects",  
           ([  
       __DIR__"npc/qinxin" : 1,
            ])); 
        set("outdoors", "baiyun"); 
        set("coor/x",8); 
        set("coor/y",-1650); 
        set("coor/z",5); 
        setup(); 
        replace_program(ROOM); 
}   