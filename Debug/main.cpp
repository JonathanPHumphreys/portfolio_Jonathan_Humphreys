#include "include\SDL.h"
#include "include\SDL_image.h"
#include "include\SDL_ttf.h" 
#include "include\SDL_mixer.h"
#include "Object.h"
#include "Sprite.h"
#include <chrono>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

//TODO - FIX COLLISION AND MENU, set a score

	SDL_Window *window;
	SDL_Surface* surface;
	SDL_Renderer* renderer;
	SDL_Rect playersrc;
	SDL_Rect playerdrc;
	SDL_Event event;
	SDL_Event ev;

	vector<Sprite> Blocks;
	//vector<Sprite> Enemy;
	//vector<Sprite> Bonus;
	vector<Sprite> Fonts;

	int Map[25][20];
	int col = 25;
	int row = 20;
	int fontcol = 10;
	int fontrow = 10;

	int numbers[10];
	string nums[11] = { "Score: ","1","2","3","4","5","6","7","8","9","0" };
	int rendernums[10][10];
	vector<int> ballvalue;

	bool runMenu = true;
	bool running = true;
	bool keyPress = false;
	bool checkCol = false;
	bool addOne = true;
	bool first = false;

	int directionp1 = 0;
	int directionp2 = 0;//  0 -left, 1 down, 2 right, 3 up
	float deltaTime = 0;
	float playerSpeed =  1; 
	int player1x = 0;
	int player2x = 0;
	int player1y = 0;
	int player2y = 0;

	Mix_Chunk *sndEffect = Mix_LoadWAV("scratch.wav");

	Sprite player1;
	Sprite player2;
	Sprite enemyPink;
	Object ObjP1;
	Object ObjP2;

	SDL_Texture* menuStart;
	SDL_Texture* menuExit;

SDL_Texture * loadTexture(string file);
SDL_Texture* loadFont(string file, int fontsize, string text, int r, int g, int b, int o);
void fillBlocks(vector<Sprite>&);
void createFonts(vector<Sprite>&);
void colourPicker(int num);
void readIn(char * filename);
void ToggleFullscreen(SDL_Window* wind);

//formenu----
void processinputmenu();
void rendermenu();

//-----------

void update()
{
	if (checkCol == true)
	{
		for (int i = 0; i < col; i++)
		{
			for (int j = 0; j < row; j++)
			{
				if (Map[i][j] == 1 || Map[i][j] == 2)
				{
					if (ObjP1.collisionBalls(player1.drc, Blocks[i * row + j].drc) == true)
					{
						ballvalue.push_back(i*row + j);
						//Blocks[i*row + j].DRCforBlocks(0,0,0,0);//delete block
						fontrow++;
						Mix_PlayChannel(1, sndEffect, 0);
						//add 10 points to thingy
						//this deletes all blocks
					}
				}
				else {
					ObjP1.checkCollision(player1.drc, Blocks[i * row + j].drc, playerSpeed);
				}
			}
		}
	}
	
	if (keyPress == true)
	{
		switch (directionp1)
		{
		case 0://left
			player1.src.x = 80;
			player1x -= playerSpeed;
			break;
		case 1://down
			player1.src.x = 170;
			player1y += playerSpeed;
			break;

		case 2://right
			player1.src.x = 0;
			player1x += playerSpeed;
			break;

		case 3://up
			player1.src.x = 260;
			player1y -= playerSpeed;
			break;
			default:
				cout << "this should not occur" << endl;
				SDL_Log("cannot be more than 3 as only 4 directions");
		}

		switch (directionp2)
		{
		case 0://left
			player2.src.x = 80;
			player2x -= playerSpeed;
			break;
		case 1://down
			player2.src.x = 170;
			player2y += playerSpeed;
			break;

		case 2://right
			player2.src.x = 0;
			player2x += playerSpeed;
			break;

		case 3://up
			player2.src.x = 260;
			player2y -= playerSpeed;
			break;
		default:
			cout << "this should not occur" << endl;
			SDL_Log("cannot be more than 3 as only 4 directions");
		}
	}
}

void process_input()
{
	while (SDL_PollEvent(&event))//can use switch statements for multiple options
	{
		//handle event here
		if (event.type == SDL_QUIT)//if you click the x on the top right
		{
			running = false;//quits
		}
		else if (event.type == SDL_KEYDOWN)
		{
			
			//select surcases bases on key press
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				running = false;
				break;
			//--------------------
			case SDLK_p:
				Mix_PauseMusic();
				break;
			case SDLK_r:
				Mix_ResumeMusic();
				break;
			case SDLK_h:
				Mix_HaltMusic();
				break;
			//---------------------------------------------------
			case SDLK_LEFT:
				keyPress = true;
				directionp1 = 0;
				break;
			case SDLK_RIGHT:
				keyPress = true;
				directionp1 = 2;
				break;
			case SDLK_UP:
				keyPress = true;
				directionp1 = 3;
				break;
			case SDLK_DOWN:
				keyPress = true;
				directionp1 = 1;
				break;
			//-------------------------
			case SDLK_w:
				keyPress = true;
				directionp2 = 3;
				break;
			case SDLK_a:
				keyPress = true;
				directionp2 = 0;
				break;
			case SDLK_s:
				keyPress = true;
				directionp2 = 1;
				break;
			case SDLK_d:
				keyPress = true;
				directionp2 = 2;
				break;

			//-----------------------------------------------------
			case SDLK_RETURN:
				if (event.key.keysym.mod & KMOD_LALT)
					ToggleFullscreen(window);
				break;
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			keyPress = false;
		}
	}
}

void render()
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
	SDL_RenderClear(renderer);//need to clear before displaying
	//SDL_Texture* font = loadFont("XBR.ttf", 15, "Score: ", 0, 0, 0, 255);
	int count = 0;
	int y = 0;
	for (int i = 0; i < col; i++)
	{

		int x = 0;
		for (int j = 0; j < row; j++)
		{
			//if (ballvalue[0] == (i * row + j))
			//{
			//	//Blocks[i * row + j].textureBlock = nullptr;
			//	SDL_DestroyTexture(Blocks[i * row + j].textureBlock);
			//}
			if (Map[i][j] == 1 || Map[i][j] == 2)
			{
				SDL_RenderCopy(renderer, Blocks[i * row + j].textureBlock,
				&Blocks[i* row + j].SRCforBalls(1,370,40,40), &Blocks[i * row + j].DRCforBlocks(400 + x, 70 + y, 30, 30));
			}
			else if (Map[i][j] == 3)
			{
				if (count == 1 || count == 2)
				{

				}
				else if (count == 3)
				{
					SDL_RenderCopy(renderer, player1.textureBlock, &player1.src, &player1.DRCforBlocks(401 + x + player1x, 71 + y + player1y, 25, 25));
				}
				else {
					SDL_RenderCopy(renderer, player2.textureBlock, &player2.src, &player2.DRCforBlocks(401 + x + player2x, 71 + y + player2y, 25, 25));
				}
				
				count++;
			}

			else {
			SDL_RenderCopy(renderer, Blocks[i * row + j].textureBlock,
			NULL, &Blocks[i * row + j].DRCforBlocks(400 + x, 70 + y, 30, 30));
			}
			
			x += 30;
		}
		y += 30;
	}
	checkCol = true;
	//--------------------------------------------------------
	/*SDL_RenderCopy(renderer, player1.textureBlock, &player1.src, &player1.drc);*/

	if (fontrow == 0 || fontrow > 10)
	{
		fontrow = 1;
	}
	if (first = true && fontrow == 10)
	{
		fontcol++;
	}

	if (fontcol == 11 || fontcol == 0)
	{
		fontcol = 1;
	}
		SDL_RenderCopy(renderer, Fonts[0].textureBlock, NULL, &Fonts[0].DRCforBlocks(100,10,100,30));
		SDL_RenderCopy(renderer, Fonts[fontcol].textureBlock, NULL, &Fonts[fontcol].DRCforBlocks(190, 16, 20, 20));
		//cout << fontcol << endl;
		SDL_RenderCopy(renderer, Fonts[fontrow].textureBlock, NULL, &Fonts[fontrow].DRCforBlocks(220, 16, 20, 20));
		//cout << fontrow << endl;
		SDL_RenderCopy(renderer, Fonts[10].textureBlock, NULL, &Fonts[10].DRCforBlocks(250, 16, 20, 20));
		
		
		first = true;
		
	SDL_RenderPresent(renderer);
}

void ToggleFullscreen(SDL_Window* wind)
{
	Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN_DESKTOP;
	bool isFull = SDL_GetWindowFlags(wind) & FullscreenFlag;
	SDL_SetWindowFullscreen(wind, isFull ? 0 : FullscreenFlag);
	SDL_ShowCursor(isFull);
}

void createFonts(char* filename)
{
	ifstream reader;
	reader.open(filename);
	if (!reader.is_open())
	{
		SDL_Log("map not found");
		exit(EXIT_FAILURE);
	}
	char num;
	reader >> num;
	while (reader.good())
	{
		for (int i = 0; i < 10; i++)
		{
			int c = num - 48;//convert to int
			numbers[i] = c;
			//cout << numbers[i] << endl;
			reader >> num;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			rendernums[i][j] = numbers[j];
			//cout << rendernums[i][j] << endl;
		}
	}
}
void fillFonts(vector<Sprite>& newnewclass)
{
	for (int i = 0; i < 11; i++)
	{
		SDL_Texture* font = loadFont("XBR.ttf", 15, nums[i], 0, 0, 0, 255);
		if (font == nullptr)
		{
			SDL_Log("an error has occured creating fonts");
		}
		newnewclass.emplace_back(font);
	}
}
void fillBlocks(vector<Sprite>& newnewclass)
{
	int counter = 0;
	SDL_Texture* textBlocks = loadTexture("blueblock.png");
	SDL_Texture* textBalls = loadTexture("spritesheet.png");
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			if (Map[i][j] == 0)
			{
				newnewclass.emplace_back(textBlocks);
				counter++;
			}
			else if (Map[i][j] == 3)
			{
				//do nothing - will be player spawn and bonus spawn
				newnewclass.emplace_back();
				counter++;
			}
			else if (Map[i][j] == 1 )
			{
				newnewclass.emplace_back(textBalls);
				counter++;
			}
			else if (Map[i][j] == 2)
			{
				newnewclass.emplace_back(textBalls);
				counter++;
			}
			else {
				SDL_Log("this is not valid");
				cout << "there should not be a greater value than 4 here";
			}
		}
	}
}	
void readIn(char * filename)
{
	ifstream reader;
	reader.open(filename);
	if (!reader.is_open())
	{
		SDL_Log("map not found");
		exit(EXIT_FAILURE);
	}
	char num;
	reader >> num;
	while (reader.good())
	{
		for (int i = 0; i < 25; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				int c = num - 48;//convert to int
				Map[i][j] = c;
				//cout << Map[i][j] << endl;
				reader >> num;
			}
		}
		break;
	}
}

void deleteBlocks(vector<Sprite> & newnewclass, int numOfElements)
{
	for (int i = 0; i < numOfElements; i++)
	{
		SDL_DestroyTexture(newnewclass[i].textureBlock);
	}
	cout << "delete completed" << endl;
	SDL_Log("deletion of textures completed");
}

void colourPicker(int num)
{
	switch (num)
	{
	case 0:
		loadTexture("blueblock.png");
		break;
	case 1:
		loadTexture("greenblock.png");
		break;
	case 2:
		loadTexture("purpleblock.png");
		break;
	case 3:
		loadTexture("redblock.png");
		break;
	case 4:
		loadTexture("yellowblock.png");
		break;
	default:
		SDL_Log("this should not occur");
		break;
	}
}

void processinputmenu()
{
	while (SDL_PollEvent(&ev) != 0)
	{
		if (ev.type = SDL_MOUSEMOTION)
		{
			if (ev.button.y > 399)
			{
				menuExit = loadFont("XBR.ttf", 30, "E X I T", 155, 183, 255, 255);
				if (ev.type = SDL_MOUSEBUTTONDOWN)
				{
					if (ev.button.button == SDL_BUTTON_LEFT)
					{
						//runMenu = false;
						//running = false;
					}
				}
			}
			else if (ev.button.y < 399)
			{
				menuStart = loadFont("XBR.ttf", 30, "START", 255, 102, 234, 255);
				if (ev.type = SDL_MOUSEBUTTONDOWN)
				{
					if (ev.button.button == SDL_BUTTON_LEFT)
					{
						runMenu = false;
					}
				}
			}
		}
	}

}

void rendermenu()
{
	SDL_Rect start;
	start.x = 100;
	start.y = 300;
	start.w = 200;
	start.h = 70;

	SDL_SetRenderDrawColor(renderer, 255, 124, 0, 255);
	SDL_RenderClear(renderer);
	menuStart = loadFont("XBR.ttf", 30, "START", 255, 255, 255, 255);
	menuExit = loadFont("XBR.ttf", 30, "E X I T", 255, 255, 255, 255);
	SDL_RenderCopy(renderer, menuStart, NULL, &start);
	start.y = 400;
	SDL_RenderCopy(renderer, menuExit, NULL, &start);
	SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	window = SDL_CreateWindow("games_window", SDL_WINDOWPOS_CENTERED/*x*/, SDL_WINDOWPOS_CENTERED/*y*/, 
		1000/*w*/, 700/*h*/, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, (SDL_RENDERER_ACCELERATED));//-1 becuase there is no index
							
	//initialise font
	if (TTF_Init() == -1) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_ttf init error: %s\n", SDL_GetError());
		return 1;
	}
	SDL_Log("SDL_ttf initialised OK!\n");
	//initialise audio
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		Mix_GetError();
	}
	Mix_Music *bgm = Mix_LoadMUS("Blank.mp3");//check template for music
	Mix_PlayMusic(bgm, -1);// -1 for loop

							  /// //////////////////////////////////////////////////////////////////
	readIn("Map.txt");
	createFonts("numbers.txt");
	fillBlocks(Blocks);
	fillFonts(Fonts);

	SDL_SetRenderDrawColor(renderer, 255, 255, 172, 255);
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags))
	{
		cout << IMG_GetError() << endl;
		SDL_Log(IMG_GetError());
	}
	if (TTF_Init() < 0)
	{
		SDL_GetError();
	}

	auto tmpTexture1 = loadTexture("spritesheet.png");
	if (tmpTexture1 != nullptr)
	{
		cout << "loaded player 1 successfully" << endl;
	}
	player1.textureBlock = tmpTexture1;
	player1.initialisePlayer();
	SDL_Texture* tmpTexture2 = loadTexture("spritesheet.png");
	if (tmpTexture2 != nullptr)
	{
		cout << "loaded player 2 successfully" << endl;
	}
	player2.textureBlock = tmpTexture2;
	player2.initialisePlayer();

	int counter = 0;
	//for time--------------
		int prevTime = 0;
		int currentTime = 0;
	//-----------------------
		currentTime = SDL_GetTicks();
		
		while (runMenu)
		{
			processinputmenu();
			rendermenu();
		}

		SDL_DestroyTexture(menuStart);
		SDL_DestroyTexture(menuExit);
	//-----------------
	while (running)
	{
		
		deltaTime = (SDL_GetTicks() - currentTime);// 1000.0f;//divide by 1000 to get decimal values
		currentTime = SDL_GetTicks();
		
		update();
		process_input();
		render();
	}
	//bgm = nullptr;
	deleteBlocks(Blocks, col * row);
	SDL_FreeSurface(surface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	IMG_Quit();
	//TTF_CloseFont();
	TTF_Quit();
	Mix_FreeChunk(sndEffect);
	Mix_FreeMusic(bgm);
	Mix_Quit();
	return 0;
}

SDL_Texture* loadFont(string file, int fontsize, string text, int r, int g, int b, int o)// add a way to change score
{
	if (r > 255 || g > 255 || b > 255 || o > 255)
	{
		cout << "cannot be greater than 255" << endl;
		SDL_Log("there cannot be a rgbo value greater than 255");
	}
	else if (r < 0 || g < 0 || b < 0 || o < 0)
	{
		cout << "cannot be lower than 0" << endl;
		SDL_Log("there cannot be a rgbo value lower than 0");
	}
	else {
	TTF_Font* font = TTF_OpenFont(file.c_str(), fontsize);
	SDL_Color colour = { r,g,b,o };
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str() , colour);
	SDL_Texture* fontTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
	SDL_QueryTexture(fontTexture, NULL, NULL, NULL, NULL);
	return  fontTexture;
	}
	
}

SDL_Texture * loadTexture(string file)
{

	SDL_Surface* loadedSurface = IMG_Load(file.c_str());//creates a surface with the filepath inserted
	SDL_Texture* spriteTexture = nullptr;
	if (loadedSurface == NULL)//check if fail
	{
		cout << "FAIL_SURFACE- " << file.c_str() << endl << IMG_GetError << endl;
	}
	else
	{
		spriteTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (spriteTexture == NULL)//check if fail
		{
			cout << "FAIL_TEXTURE- " << file.c_str() << endl << SDL_GetError() << endl;
		}
		SDL_FreeSurface(loadedSurface);//free surface
	}
	return spriteTexture;
}