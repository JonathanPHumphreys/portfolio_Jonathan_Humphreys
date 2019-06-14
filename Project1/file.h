#pragma once
#include "constants.h"

constexpr auto MAX_SIZE = 21;

class File//used for reading in maps
{
public:
	File();
	~File();
	void setMapSize();//sets the game map as num x N
	void readMap(const char * file);
	int MapSize();
	std::vector<std::vector<int>> map;
};

