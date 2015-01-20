#include "StateBattle.h"
#include <time.h>

float Rnd(float x, float y)
{
	if (x>y)
		return (rand() % (int)(x - y) + y);
	else if (x<y)
		return (rand() % (int)(y - x) + x);
	else
		return x;
}

void StateBattle::init(){}
void StateBattle::draw(SDL_Window * window, Game &context) //draw the game state 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear window
	SDL_Color colour = { 255, 255, 0 };

	context.getMonsterManager()->getBattleMonster()->renderAt(800,512);
	context.getMonsterManager()->getPlayer()->renderAt(124,512);

	SDL_GL_SwapWindow(window); // swap buffers
}
void StateBattle::handleEvent(SDL_Event const &sdlEvent, Game &context){} //method to handle what state the game is at

void StateBattle::update(Game &context) //update the gamestate
{
	if ((SDL_GetTicks() - attackTime[0]) >= attackDelay[0])
	{
		//then enough time has past for the player to attack
		context.getMonsterManager()->getBattleMonster()->subtractHealth(Rnd(1, context.getMonsterManager()->getPlayer()->getStrength()));
		attackTime[0] = SDL_GetTicks();
		//set a new random delay for attacking again
		attackDelay[0] = Rnd(1000, context.getMonsterManager()->getPlayer()->getRefreshRate());

		if ((context.getMonsterManager()->getBattleMonster()->getHealth()) <= 0)
		{
			if (context.getMonsterManager()->checkMonsterStillAlive())
			{
				context.getMonsterManager()->getPlayer()->subtractHealth(-dmgTaken / 2);
				context.setState(context.getPlayState());
			}
			else
				context.setState(context.getGameWinState());
		}
		

	}

	if ((SDL_GetTicks() - attackTime[1]) >= attackDelay[1])
	{
		int dmg = Rnd(1, context.getMonsterManager()->getBattleMonster()->getStrength());
		//then enough time has past for the monster to attack
		context.getMonsterManager()->getPlayer()->subtractHealth(dmg);
		dmgTaken += dmg;
		attackTime[1] = SDL_GetTicks();
		//set a new random delay for attacking again
		attackDelay[1] = Rnd(1000, context.getMonsterManager()->getBattleMonster()->getRefreshRate());

		if ((context.getMonsterManager()->getPlayer()->getHealth()) <= 0)
		{
				context.setState(context.getGameOverState());
		}


	}
}

void StateBattle::Cleanup(){} //delete everything that is unused so that memory can be freed

void StateBattle::enter(Game &context)
{
	dmgTaken = 0;

	for (int i = 0; i < 2; i++)
	{
		attackTime[i] = SDL_GetTicks();
	}

	//delay for the first attack of player
	attackDelay[0] = Rnd(1000, context.getMonsterManager()->getPlayer()->getRefreshRate());
	//delay for the first attack of monster
	attackDelay[1] = Rnd(1000, context.getMonsterManager()->getBattleMonster()->getRefreshRate());
		

}