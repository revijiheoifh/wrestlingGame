#pragma once
#include "renderingLibrary.h"

SDL_Surface* ringSurface = NULL;
SDL_Texture* ringTexture = NULL;
SDL_Surface* crowdSurface = NULL;
SDL_Texture* crowdTexture = NULL;

void setUpStage() 
{
	ringSurface = SDL_LoadBMP("Assets/ring.bmp");
	ringTexture = SDL_CreateTextureFromSurface(renderer, ringSurface);
	crowdSurface = SDL_LoadBMP("Assets/crowd.bmp");
	crowdTexture = SDL_CreateTextureFromSurface(renderer, crowdSurface);
}


void renderStage()
{
	SDL_RenderCopy(renderer, crowdTexture, NULL, NULL);
	SDL_RenderCopy(renderer, ringTexture, NULL, NULL);
}