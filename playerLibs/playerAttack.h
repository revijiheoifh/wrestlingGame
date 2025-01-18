#pragma once
#include "playerLibs/player.h"
#include <iostream>
#include <chrono>

int xPosP1 = 0;
int xPosP2 = 790;
//int minPlayerPos = 10;
//int maxPlayerPos = 790;

int health = 100;
int block = 25;

const Uint8* key = SDL_GetKeyboardState(NULL); // this function is for checking to see if a key has been pressed down

player playerOne{ health, block, xPosP1 };
player playerTwo{ health, block, xPosP2 };

using namespace std;
using namespace std::chrono;

bool isBlocking = false;
bool isBlockingP2 = false;

int playerDistance;

/*
The attackPlayer() function allows for both players to be able to attack each other
the way attacking works is:

* it calculates the distance between the two players by subtracting their position on the x-axis
* if the distance is small enough (not too small), the players can attack each other and take away the opposite player's health.
* There will be a cooldown for attacking to prevent health from decreasing too quickly
The players can also block the other player's attack by pressing one of the keys on the keyboard:
* But the block is also going to be having a health-bar of sorts
* After a certain amount of hits from the opposite player, the block will break and the opposite
player will be open to attack you

* Player one controls:
* A to move left.
* D to move right
* Q to attack
* E to block
*
* Player two controls:
* Left-arrow key to move left
* Right-arrow key to move right
* / key to attack
* . key to block
*/

auto timestamp = 0;

//int attackKey, int blockKey, int oppositePlayerBlockKey, player attackingPlayer, player oppositePlayer
bool attackPlayer(int attackKey, int blockKey, int oppositePlayerBlockKey, player &attackingPlayer, player &oppositePlayer)
{
	auto clock = steady_clock::now();
	auto time = clock.time_since_epoch();
	
	if (key[attackKey] && ((playerDistance <= 140 && playerDistance >= 110) || (playerDistance >= -140 && playerDistance <= -110)) && (attackingPlayer.getHp() > 0) && !key[blockKey] && duration_cast<seconds>(time).count() > timestamp)
	{
		if (key[oppositePlayerBlockKey] && oppositePlayer.getBlock() > 0)
		{
			if (key[SDL_SCANCODE_E])
			{
				isBlocking = true;
			}
			else
			{
				isBlocking = false;
			}
			
			if (key[SDL_SCANCODE_PERIOD])
			{
				isBlockingP2 = true;
			}
			else
			{
				isBlockingP2 = false;
			}
			oppositePlayer.takeBlockDamage(5);
		}
		else
		{
			isBlocking = false;
			isBlockingP2 = false;
			oppositePlayer.takeDamage(5);
		}
		timestamp = duration_cast<seconds>(time).count() + 2;
		return true;
	}
	else
	{
		return false;
	}
	if (!key[oppositePlayerBlockKey] && oppositePlayer.getBlock() < 10 && duration_cast<seconds>(time).count() > timestamp)
	{
		isBlocking = false;
		oppositePlayer.takeBlockDamage(-2);
		timestamp = duration_cast<seconds>(time).count() + 1;	
	}
}