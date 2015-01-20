#include "MonsterNPC.h"

using namespace std;

//constructor implementation
MonsterNPC::MonsterNPC(char *basename, int x, int y){
	name.assign(basename); health = 100; strength = 0; refreshRate = 0; dropRate = 0;

	textFont = TTF_OpenFont("MavenPro-Regular.ttf", 24);
	SDL_Color displayColor = { 255, 255, 0 }; //displaycolor

	monster = new Bitmap("images/monster.bmp", true);

	//setting up label for the health onscreen
	healthLabel = new Label();
	string healthString("Health: ");
	healthString += to_string(getHealth());
	healthLabel->textToTexture(healthString.c_str(), textFont, displayColor);

	xpos = x;
	ypos = y;

	initialXpos = x;
	initialYpos = y;
}

void MonsterNPC::render(){
	SDL_Color displayColor = { 255, 255, 0 }; //displaycolor

	delete healthLabel;
	healthLabel = new Label();
	string healthString(name);
	healthString += " Health: ";
	healthString += to_string(getHealth());
	healthLabel->textToTexture(healthString.c_str(), textFont, displayColor);

	monster->drawAt(xpos, ypos);

	healthLabel->draw(xpos, ypos + 64);
}

void MonsterNPC::renderAt(int x, int y)
{
	SDL_Color displayColor = { 255, 255, 0 }; //displaycolor

	delete healthLabel;
	healthLabel = new Label();
	string healthString(name);
	healthString += " Health: ";
	healthString += to_string(getHealth());
	healthLabel->textToTexture(healthString.c_str(), textFont, displayColor);

	monster->drawAt(x, y);

	healthLabel->draw(x, y + 64);
}