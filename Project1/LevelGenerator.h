#pragma once
#include "constants.h"
#include "file.h"

class Level
{
public:
	Level();
	~Level();
};


class LevelGenerator
{
public:
	LevelGenerator();
	~LevelGenerator();
	void organiseData(SDL_Renderer* ren);
	File file;
};

