#pragma once
#include <SDL_stdinc.h>
#include <SDL.h>

class player
{
public:
	player(int Hp, int block, int xPos);
	int getHp();
	float getBlock();
	int getXPos();
	void takeBlockDamage(float blockAmount);
	void takeDamage(int healthAmount);
	bool movement(int subtractXPosKey, int addXPosKey);

private:
	int currentHp;
	float currentBlock;
	int currentXPos;
};