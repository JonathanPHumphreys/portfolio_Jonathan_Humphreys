#pragma once
#include "constants.h"
#include "Pathfinding.h"

constexpr auto OBJECT_SIZE = 30;
constexpr auto MAP_HALF = 10;

//TODO:: create some classes to cover some functions that repeat 
class movingOBJS
{
public:
	/*virtual int get_currentX(SDL_Rect &rect);
	virtual int get_currentY(SDL_Rect &rect);*/
};

class staticOBJS
{
	
};

class Player
{
public:
	Player();
	Player(SDL_Texture* text);
	void setStartingLocation(int _x, int _y);//sets the current and starting locations to what is set from the map
	bool positionCheck(int num);
	int getX();
	int getY();
	int get_currentX();//returns the index value for the map
	int get_currentY();//returns the index value for the map
	~Player();
	SDL_Texture* texture;
	SDL_Rect dst;
private:
	int starting_x;
	int starting_y;
};

class Orbs
{
public:
	Orbs();
	Orbs(SDL_Texture* text);
	void setStartingLocation(int _x, int _y);//sets the current and starting locations to what is set from the map
	int getX();
	int getY();
	SDL_Texture* texture;
	SDL_Rect dst;
	~Orbs();

private:
	int starting_x;
	int starting_y;
};

class Pickups
{
public:
	Pickups();
	Pickups(SDL_Texture* text);
	void setStartingLocation(int _x, int _y);//sets the current and starting locations to what is set from the map
	int getX();
	int getY();
	SDL_Texture* texture;
	SDL_Rect dst;
	~Pickups();

private:
	int starting_x;
	int starting_y;
};

class Sentry
{
public:
	Sentry();
	Sentry(SDL_Texture* text);
	void setStartingLocation(int _x, int _y);//sets the current and starting locations to what is set from the map
	void Move();
	int getX();
	int getY();
	int get_currentX();//dont need y as its the same
	//int get_currentY();
	SDL_Texture* texture;
	SDL_Rect dst;
	bool moveRight;
	~Sentry();
	int current_x;
	int current_y;

private:
	int starting_x;
	int starting_y;
	int speed;
};

class Guard
{
public:
	Guard();
	Guard(SDL_Texture* text);
	void setStartingLocation(int _x, int _y);//sets the current and starting locations to what is set from the map
	int getX();
	int getY();
	int get_currentX();
	int get_currentY();
	SDL_Texture* texture;
	SDL_Rect dst;
	~Guard();
	int current_x;
	int current_y;

	//CLASSES
	Pathfinding path;//each guard needs their own path

private:
	int starting_x;
	int starting_y;
};

class Walls
{
public:
	Walls();
	Walls(SDL_Texture* text);
	void setStartingLocation(int _x, int _y);//sets the current and starting locations to what is set from the map
	int getX();
	int getY();
	SDL_Texture* texture;
	SDL_Rect dst;
	~Walls();

private:
	int starting_x;
	int starting_y;

};

class GameObject//hierarchy
{
public:
	GameObject();
	~GameObject();
	void setUpMap(SDL_Renderer* ren, std::vector<std::vector<int>> map, int size);
	Sentry sent;
	std::vector<Player> playerVec;
	std::vector<Guard> guardVec;
	std::vector<Pickups> pickupVec;
	std::vector<Orbs> orbVec;
	std::vector<Walls> wallVec;
};

