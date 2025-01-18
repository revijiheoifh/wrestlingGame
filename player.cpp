#include "playerLibs/player.h"
#include <SDL_stdinc.h>
#include <SDL.h>

player::player(int hp, int block, int xPos)
{
	currentHp = hp;
	currentBlock = block;
	currentXPos = xPos;
}

int player::getHp()
{
	return currentHp;
}

float player::getBlock()
{
	return currentBlock;
}

int player::getXPos()
{
	return currentXPos;
}

void player::takeBlockDamage(float blockAmount)
{
	currentBlock -= blockAmount;
	if (currentBlock < 0)
	{
		currentBlock = 0;
	}
}

void player::takeDamage(int healthAmount)
{
	currentHp -= healthAmount;
	if (currentHp < 0)
	{
		currentHp = 0;
	}
}

bool player::movement(int subtractXPosKey, int addXPosKey)
{
	int minPlayerPos = 10;
	int maxPlayerPos = 790;

	const Uint8* key = SDL_GetKeyboardState(NULL);
	if (key[subtractXPosKey] && (currentXPos > minPlayerPos))
	{
		currentXPos -= 20;
		return true;
	}
	if (key[addXPosKey] && (currentXPos < maxPlayerPos))
	{
		currentXPos += 20;
		return true;
	}
	else
	{
		return false;
	}
}