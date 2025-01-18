/*
* Use more classes
* Use vector animation instead of frames
* Use structures
* 
* These are things I should do in the future if I were to come back to it
*/








#include <iostream>
#include <SDL.h>
#include "playerLibs/playerAttack.h"
#include "crowdAndRingRender.h"
#include "playerLibs/playerRender.h"
#include "playerLibs/player.h"
#include "renderingLibrary.h"
#include <chrono>

using namespace std;
using namespace std::chrono;
SDL_Window* window = NULL;
SDL_Event e; // This variable is responsible for seeing if the player has quit the game or not
int screenWidth = 1080;
int screenHeight = 720;

SDL_Surface* playerOneWalkingSurface[4];
SDL_Texture* playerOneWalkingTexture[4];
SDL_Surface* playerTwoWalkingSurface[4];
SDL_Texture* playerTwoWalkingTexture[4];

int playerOneControl[4];
int playerTwoControl[4];
int ticks;

bool walkingAnimationPlayerOne = false;
bool walkingAnimationPlayerTwo = false;


bool punchingAnimationPlayerOne = false;
bool punchingAnimationPlayerTwo = false;


bool blockingAnimationPlayerOne = false;
bool blockingAnimationPlayerTwo = false;

void loadWindow();
void start();
void update();
void renderEverything();

int main(int argsc, char* args[])
{
	loadWindow(); // This is a function that initializes the window for everything to be displayed
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // This defines the renderer that has been declared in renderingLibrary.h, vsync has been implemented to make the movement smoother
	start();
	update();
	return 0;
}

void loadWindow()
{
	if (SDL_INIT_VIDEO < 0)
	{
		cout << "Window could not be initiated" << SDL_GetError();
	}

	window = SDL_CreateWindow("Wrestling Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		cout << "Window couldn't be created: " << SDL_GetError();
	}
}

/*
* the start() function is going to be setting everything up such as ring, crowd, and the animation of the players
* All of the code that is in this function is going to be executed once in the beginning when the code is ran.
*/
void start() 
{
	setUpStage();
	setUpPlayerOne();
	setUpPlayerTwo();
	createAnimationTextures("playerOne", playerOneWalkingSurface, playerOneWalkingTexture);
	createAnimationTextures("playerTwo", playerTwoWalkingSurface, playerTwoWalkingTexture);

	/*
	* The keys that are being pressed are represented by numbers in the SDL library
	* For example, SDL_SCANCODE_LEFT which is what is passed in the key[] function to act when pressing the left-arrow
	key is represented by a number, in this case, 80
	* SDL_SCANCODE_A is represented by 4 and so on.
	*
	* The ones that will be used are:
	* // FOR PLAYER ONE:
	* SDL_SCANCODE_A = 4
	* SDL_SCANCODE_D = 7
	* SDL_SCANCODE_E = 8
	* SDL_SCANCODE_Q = 20
	*
	* // FOR PLAYER TWO
	* SDL_SCANCODE_LEFT = 80
	* SDL_SCANCODE_RIGHT = 79
	* SDL_SCANCODE_1 = 30
	* SDL_SCANCODE_2 = 31
	*
	* More information can be found on this website: https://wiki.libsdl.org/SDL2/SDL_Scancode
	*/

	// The buttons that are going to be used to move the player, for simplicity's sake, is going to be
	// inside an array called playerOneControl and playerTwoControl
	// forward, backward, attack, block
	playerOneControl[0] = SDL_SCANCODE_A;
	playerOneControl[1] = SDL_SCANCODE_D;
	playerOneControl[2] = SDL_SCANCODE_Q;
	playerOneControl[3] = SDL_SCANCODE_E;

	playerTwoControl[0] = SDL_SCANCODE_LEFT;
	playerTwoControl[1] = SDL_SCANCODE_RIGHT;
	playerTwoControl[2] = SDL_SCANCODE_SLASH;
	playerTwoControl[3] = SDL_SCANCODE_PERIOD;

	ticks = 16; // this variable is responsible for controlling the tick rate
}

/*
* The update function will be containing rendering all of the images that have been drawn and all of the movement.
* It will be also containing things that handle damage and whatnot.
* the update function will be containing code that is going to be running every frame like unity and other game engines do
*/
void update()
{
	bool quit = false;	

	auto currentTime = steady_clock::now();
	auto timeSinceEpoch = currentTime.time_since_epoch();
	auto tickTimeStamp = duration_cast<milliseconds>(timeSinceEpoch).count();

	double animationTimeStampP1 = 0;
	double animationTimeStampP2 = 0;

	double punchingTimeStampP1 = 0;
	double punchingTimeStampP2 = 0;

	double blockingTimeStampP1 = 0;
	double blockingTimeStampP2 = 0;

	int frameIndexP1 = 0;
	int frameIndexP2 = 0;


	while (quit == false)
	{

		/*
		A tick system has been implemented so that the 
		player movement is more smoother and also, to ensure that the player
		movement is essentially synchronised with the machine's fps so that
		regardless of what machine you have, the player will move at the same speed

		This is something that is implemented in pretty much every game that has
		graphics and movement.

		The time since the epoch is being recorded constantly, and with each tick, a timestamp is also being recorded.
		And the movement will only happen if the time since epoch (time since 00:00:00, 1st Jan, 1970) - tickTimeStamp is greater than the ticks
		This allows the animation to be smoother, and also handle lag spikes if they were to occur
		*/

		
		auto currentTime = high_resolution_clock::now();
		auto timeSinceEpoch = duration_cast<milliseconds>(currentTime.time_since_epoch());

		if (walkingAnimationPlayerOne == true)
		{
			if (timeSinceEpoch.count() >= animationTimeStampP1) {
				playerOneTexture = playerOneWalkingTexture[(frameIndexP1 + 1) % 4];

				frameIndexP1 += 1;
				animationTimeStampP1 = timeSinceEpoch.count() + 100;
			}
		}

		if (walkingAnimationPlayerTwo == true)
		{
			if (timeSinceEpoch.count() >= animationTimeStampP2) {
				playerTwoTexture = playerTwoWalkingTexture[(frameIndexP2 + 1) % 4];

				frameIndexP2 += 1;
				animationTimeStampP2 = timeSinceEpoch.count() + 100;
			}
		}

		if (punchingAnimationPlayerOne == true && timeSinceEpoch.count() <= punchingTimeStampP1)
		{

			playerOneTexture = playerPunchingTexture;


		}
		if (punchingAnimationPlayerOne == true && timeSinceEpoch.count() >= punchingTimeStampP1)
		{
			punchingAnimationPlayerOne = false;
			playerOneTexture = playerIdleTexture;
		}

		if (punchingAnimationPlayerTwo == true && timeSinceEpoch.count() <= punchingTimeStampP2)
		{
			playerTwoTexture = playerTwoPunchingTexture;
		}
		if (punchingAnimationPlayerTwo == true && timeSinceEpoch.count() >= punchingTimeStampP2)
		{
			punchingAnimationPlayerTwo = false;
			playerTwoTexture = playerTwoIdleTexture;
		}

		if (blockingAnimationPlayerOne == true && timeSinceEpoch.count() <= blockingTimeStampP1)
		{
			playerOneTexture = playerBlockingTexture;
		}
		if (blockingAnimationPlayerOne == true && timeSinceEpoch.count() >= blockingTimeStampP1)
		{
			blockingAnimationPlayerOne = false;
			playerOneTexture = playerIdleTexture;
		}

		if (blockingAnimationPlayerTwo == true && timeSinceEpoch.count() <= blockingTimeStampP2)
		{
			playerTwoTexture = playerTwoBlockingTexture;
		}
		if (blockingAnimationPlayerTwo == true && timeSinceEpoch.count() >= blockingTimeStampP2)
		{
			blockingAnimationPlayerTwo = false;
			playerTwoTexture = playerTwoIdleTexture;
		}


		if ((duration_cast<milliseconds>(timeSinceEpoch).count() - tickTimeStamp) >= ticks)
		{
			tickTimeStamp += ticks;
			renderEverything();

			while (SDL_PollEvent(&e))
			{
				SDL_RenderClear(renderer);
				
				
				
				playerDistance = playerTwo.getXPos() - playerOne.getXPos();
			
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}

				// player one movement, animation, and attack
				if (playerOne.getHp() > 0)
				{
					if (playerOne.movement(playerOneControl[0], playerOneControl[1]))
					{
						walkingAnimationPlayerOne = true;
					
					}
					else
					{
						walkingAnimationPlayerOne = false;
						playerOneTexture = playerIdleTexture;
					}
					
					//int attackKey, int blockKey, int oppositePlayerBlockKey, player attackingPlayer, player oppositePlayer
					if (attackPlayer(playerOneControl[2], playerOneControl[3], playerTwoControl[3], playerOne, playerTwo))
					{
						punchingAnimationPlayerOne = true;
						punchingTimeStampP1 = timeSinceEpoch.count() + 500;
					}

					if (isBlocking)
					{
						blockingAnimationPlayerOne = true;
						blockingTimeStampP1 = timeSinceEpoch.count() + 500;
					}


				}

				// player two movement, animation, and attack
				if (playerTwo.getHp() > 0)
				{
					if (playerTwo.movement(playerTwoControl[0], playerTwoControl[1])) 
					{
						walkingAnimationPlayerTwo = true;
					} 
					else
					{
						walkingAnimationPlayerTwo = false;
						playerTwoTexture = playerTwoIdleTexture;
					}
					
					if (attackPlayer(playerTwoControl[2], playerTwoControl[3], playerOneControl[3], playerTwo, playerOne))
					{
						punchingAnimationPlayerTwo = true;
						punchingTimeStampP2 = timeSinceEpoch.count() + 500;
					}

					if (isBlockingP2)
					{
						blockingAnimationPlayerTwo = true;
						blockingTimeStampP2 = timeSinceEpoch.count() + 500;
					}
				}

				cout << "player distance: " <<  playerDistance << endl;
				cout << "player one hp: " << playerOne.getHp() << endl;
				cout << "player one block: " << playerOne.getBlock() << endl;
				cout << endl;
				cout << "player two hp: " << playerTwo.getHp() << endl;
				cout << "player two block: " << playerTwo.getBlock() << endl;
				cout << endl;
			
				if (playerOne.getHp() == 0 || playerTwo.getHp() == 0)
				{
					cout << "Game over!" << endl;
					if (playerOne.getHp() == 0)
					{
						cout << "player two wins!" << endl;
					}
					else
					{
						cout << "player one wins!" << endl;
					}
					quit = true;
				}
			}
		}
	}
}

void renderEverything()
{
	renderStage();
	renderPlayerOne();
	renderPlayerTwo();
	SDL_RenderPresent(renderer);
}