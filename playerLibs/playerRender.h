#pragma once
#include "renderingLibrary.h"
#include "playerLibs/player.h"
#include "playerLibs/playerAttack.h"
#include <string>
#include <chrono>

SDL_Surface* playerOneSurface = NULL;
SDL_Texture* playerOneTexture = NULL;

SDL_Surface* playerTwoSurface = NULL;
SDL_Texture* playerTwoTexture = NULL;

SDL_Surface* temp = NULL;

SDL_Texture* playerIdleTexture = NULL;
SDL_Texture* playerTwoIdleTexture = NULL;

SDL_Texture* playerPunchingTexture = NULL;
SDL_Texture* playerTwoPunchingTexture = NULL;

SDL_Texture* playerBlockingTexture = NULL;
SDL_Texture* playerTwoBlockingTexture = NULL;

SDL_Rect playerOnePos;
SDL_Rect playerTwoPos;

int playersPosY = 250;
int playersWidth = 300;
int playersHeight = 300;

/*
* This is a function that is creating the animation textures of the player
* The playerFile parameter just like all of the variable names are written in camelCase
* the playerFile is written like this: (player[The number spelt out])
* Examples:
* playerOne
* playerTwo
*/
void createAnimationTextures(string playerFile, SDL_Surface* playerWalkingSurface[4], SDL_Texture* playerWalkingTexture[4])
{
	// animation frames
	for (int i = 0; i < 4; i++)
	{
		string fileNum = to_string(i + 1);
		string playerFrameFile = "Assets/" + playerFile + "/" + playerFile + fileNum + ".bmp";
		playerWalkingSurface[i] = SDL_LoadBMP(playerFrameFile.c_str()); // .c_str() is for converting string to char datatype: https://stackoverflow.com/questions/7352099/stdstring-to-char
		playerWalkingTexture[i] = SDL_CreateTextureFromSurface(renderer, playerWalkingSurface[i]);
		cout << playerFile + fileNum + ".bmp" << endl;
	}
}

void setUpPlayerOne()
{
	playerOneSurface = SDL_LoadBMP("Assets/playerOne/playerOne.bmp");
	playerOneTexture = SDL_CreateTextureFromSurface(renderer, playerOneSurface);
	playerIdleTexture = SDL_CreateTextureFromSurface(renderer, playerOneSurface);

	temp = SDL_LoadBMP("Assets/playerOne/playerOnePunch.bmp");
	playerPunchingTexture = SDL_CreateTextureFromSurface(renderer, temp);

	temp = SDL_LoadBMP("Assets/playerOne/playerOneBlock.bmp");
	playerBlockingTexture = SDL_CreateTextureFromSurface(renderer, temp);
}


void setUpPlayerTwo()
{
	playerTwoSurface = SDL_LoadBMP("Assets/playerTwo/playerTwo.bmp");
	playerTwoTexture = SDL_CreateTextureFromSurface(renderer, playerTwoSurface);
	playerTwoIdleTexture = SDL_CreateTextureFromSurface(renderer, playerTwoSurface);

	temp = SDL_LoadBMP("Assets/playerTwo/playerTwoPunch.bmp");
	playerTwoPunchingTexture = SDL_CreateTextureFromSurface(renderer, temp);

	temp = SDL_LoadBMP("Assets/playerTwo/playerTwoBlock.bmp");
	playerTwoBlockingTexture = SDL_CreateTextureFromSurface(renderer, temp);
}

void renderPlayerOne()
{
	playerOnePos = { playerOne.getXPos(),playersPosY,playersWidth,playersHeight}; // x, y, w, h
	SDL_RenderCopy(renderer, playerOneTexture, NULL, &playerOnePos);
}

void renderPlayerTwo()
{
	playerTwoPos = { playerTwo.getXPos() , playersPosY, playersWidth, playersHeight};
	SDL_RenderCopy(renderer, playerTwoTexture, NULL, &playerTwoPos);
}