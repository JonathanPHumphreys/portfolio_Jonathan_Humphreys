#include <time.h>
#include "constants.h"
#include "LevelGenerator.h"
#include "GameObject.h"
#include "Animator.h"

//GLOBALS SDL
SDL_Window *window;
SDL_Renderer* renderer;
SDL_Event event;
LevelGenerator lg;
Level level;
GameObject go;
Animator animator;

//GLOBAL FUNCTIONS
void render();
void process_input();
void update();

int main(int argc, char *argv[])
{
	srand(time(NULL));//reset time each time the game is played
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	window = SDL_CreateWindow("Portfolio Game", SDL_WINDOWPOS_CENTERED/*x*/, SDL_WINDOWPOS_CENTERED/*y*/,
		1000/*w*/, 700/*h*/, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, (SDL_RENDERER_ACCELERATED));//-1 becuase there is no index
	if (TTF_Init() == -1) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_ttf init error: %s\n", SDL_GetError());
		return 1;
	}
	SDL_Log("SDL_ttf initialised OK!\n");

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << IMG_GetError() << std::endl;
		SDL_Log(IMG_GetError());
	}
	if (TTF_Init() < 0)
	{
		SDL_GetError();
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "ERROR" << Mix_GetError() << std::endl;
	}
	//GAME VARIABLES
	bool game = true;
	//TIME VARIABLES
	double delta_time, old_time;
	int timeStep = 0;
	const double FPS = 60.0;
	const double frameDelay = 1000 / FPS;

	//setup before the game loop
	lg.file.setMapSize();
	lg.file.readMap("map1.txt");
	go.setUpMap(renderer, lg.file.map, lg.file.MapSize());

	//go.p1.get_currentX(go.p1.dst);

	while (game)
	{
		old_time = SDL_GetTicks();//get current time

		process_input();
		update();
		render();

		delta_time = SDL_GetTicks() - old_time;//how many ticks did it take to gameloop
		if (frameDelay > delta_time)//delay so it hits the expected frame rate
		{
			SDL_Delay(frameDelay - delta_time);
		}
		timeStep += 1;
	}
	
	return 0;
}

void process_input()
{
	//add player movement
}

void update()
{
	//MOVE THE SENTRY --:
	go.sent.Move();

	//pathfinding checks
	for (auto i = 0; i < go.guardVec.size(); i++)
	{
		//checks if the player is above/below the halfway mark :: making the guards start moving.
		//returns true if the guard needs to move.
		if (go.playerVec[i].positionCheck(i) == true)
		{
			go.guardVec[i].path.active = true;
		}
		else
		{
			go.guardVec[i].path.active = false;
		}
		//move the guard closer to the player
		//1. calculate the hcost for movement
		if (go.guardVec[i].path.active == true)
		{
			//gcost
			go.guardVec[i].path.cost_calc(go.guardVec[i].getX(), go.guardVec[i].getY(), lg.file.MapSize());
			//fcost
			//TODO : check if this is the correct player
			go.guardVec[i].path.cost_calc(go.guardVec[i].getX(), go.guardVec[i].getY(), 
				go.playerVec[i].getX(), go.playerVec[i].getY(), lg.file.MapSize());
			//hcost
			go.guardVec[i].path.cost_calc(go.guardVec[i].path.g_cost, go.guardVec[i].path.h_cost, lg.file.MapSize());
			//move the guard
			//TODO: move the guard in accordance of easiest path
			// it does not care about walls since the animation should move it over the walls.

		}
		
	}

}

void render()
{
	SDL_SetRenderDrawColor(renderer, 204, 255, 255, 255);//light blue
	SDL_RenderClear(renderer);
	//DRAW HERE - TAKE CARE OF Z-LAYERS
	for (int i = 0; i < go.wallVec.size(); i++)
	{
		SDL_RenderCopy(renderer, go.wallVec[i].texture, NULL, &go.wallVec[i].dst);
	}
	for (int i = 0; i < go.orbVec.size(); i++)
	{
		SDL_RenderCopy(renderer, go.orbVec[i].texture, NULL, &go.orbVec[i].dst);
	}
	for (int i = 0; i < go.pickupVec.size(); i++)
	{
		SDL_RenderCopy(renderer, go.pickupVec[i].texture, NULL, &go.pickupVec[i].dst);
	}
	//DOES FOR BOTH PLAYER AND GUARDS SINCE THEY ARE BOTH THE SAME SIZE
	for (int i = 0; i < go.playerVec.size(); i++)
	{
		SDL_RenderCopy(renderer, go.playerVec[i].texture, NULL, &go.playerVec[i].dst);
		SDL_RenderCopy(renderer, go.guardVec[i].texture, NULL, &go.guardVec[i].dst);
	}
	//SENTRY : by itself
	SDL_RenderCopy(renderer, go.sent.texture, NULL, &go.sent.dst);


	SDL_RenderPresent(renderer);
}

//TODO: create a templete to handle in the different classes for a cleaner render function.