#include "file.h"



File::File()
{
	
}


File::~File()
{
	map.clear();
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			map[i].pop_back();
		}
	}
}

void File::setMapSize()
{
	std::vector<int> temp;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		map.push_back(temp);
	}
}

void File::readMap(const char * file)
{
	std::ifstream reader;
	reader.open(file);
	if (!reader.is_open())
	{
		SDL_Log("map not found");
		exit(EXIT_FAILURE);
	}
	char num;
	reader >> num;
	while (reader.good())
	{
		for (int i = 0; i < MAX_SIZE; i++)
		{
			for (int j = 0; j < MAX_SIZE; j++)
			{
				int c = num - 48;//convert to int
				map[i].push_back(c);
				reader >> num;
			}
		}
		break;
	}
	reader.close();
}

int File::MapSize()
{
	return MAX_SIZE;
}
