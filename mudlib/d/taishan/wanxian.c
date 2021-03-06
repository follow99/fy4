 // Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
inherit ROOM;
void create()
{
  set("short","万仙楼");
  set("long",@LONG
一入万仙楼，仿佛入了“世外桃源”。一道山溪漫流而过，山色清
幽，溪水澄清。溪底一块五六亩地的五色花纹石坪，石上刻有唐，宋，
元，明各代题字，可惜由于溪水的长年洗刷，字迹已经模糊。溪东青林
翠竹，绿浪浓荫，夹岸石壁，五色交辉。溪西石壁上书“听泉”二字，
听那潺潺流水“铿鸣金石”的合唱，自然的魅力一显无余。怪不得引得
万仙驻足。留连忘返。
LONG
  );
  set("exits",([
         "up":__DIR__"doumu",
         "down" :__DIR__"hongmen",
               ]));
        set("objects", ([
        __DIR__"npc/ding" : 1,
                        ]) );
        set("outdoors", "fengyun");
        set("coor/x",310);
        set("coor/y",2380);
        set("coor/z",20);
        setup();
        replace_program(ROOM);
}
