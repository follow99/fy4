 // Room: /d/oldpine/epath3.c
inherit ROOM; 
void create()
{
        set("short", "�ּ�С·");
        set("long", @LONG
������������һ�������ּ��С·��������һ��Сʯ�ź����һ��
ɽ���ϣ�������Զ���ƺ������ӵĳ��ڣ�һ���ƾɵ�ջ������ɽ��ͨ��
ɽ�ϣ��㷢�ֵ�����һЩʪ�����Ľ�ӡ��������Ϊ��ӡ̫�࣬�ֲ�����
������ȥ��
LONG
        );
        set("item_desc", ([ /* sizeof() == 1 */
                "footprints" : "һЩ���ҵĽ�ӡ���������˵Ľ�ӡ�����������в�������ӡ��\n",
        ]));
        set("exits", ([ /* sizeof() == 1 */
                "west" : __DIR__"epath2",
        ]));
        set("objects", ([
                __DIR__"npc/venomsnake": 2
        ]) );
        set("outdoors", "oldpine"); 
        set("coor/x",550);
        set("coor/y",2370);
        set("coor/z",100);
        setup();
        replace_program(ROOM);
} 