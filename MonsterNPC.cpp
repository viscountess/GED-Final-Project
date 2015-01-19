#include "MonsterNPC.h"

//constructor implementation
MonsterNPC::MonsterNPC(char *basename, int x, int y){
	name.assign(basename); health = 100; strength = 0; refreshRate = 0; dropRate = 0;

	monster = new Bitmap("images/monster.bmp", true);

	xpos = x;
	ypos = y;
}

void MonsterNPC::render(){
	monster->drawAt(xpos, ypos);
}

void MonsterNPC::renderAt(int x, int y)
{
	monster->drawAt(x, y);
}