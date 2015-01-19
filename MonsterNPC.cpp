#include "MonsterNPC.h"

//constructor implementation
MonsterNPC::MonsterNPC(char *basename){
	name.assign(basename); health = 100; strength = 0; refreshRate = 0; dropRate = 0;

	monster = new Bitmap("images/player.bmp", true);
}

void MonsterNPC::render(){
	monster->drawAt(512, 512);
}

