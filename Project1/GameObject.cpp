#include "GameObject.h"



GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::setUpMap(SDL_Renderer * ren, std::vector<std::vector<int>> map, int size)
{
	SDL_Texture* wall_Texture = IMG_LoadTexture(ren, "wall.png");
	SDL_Texture* player1_Texture = IMG_LoadTexture(ren, "player1.png");
	SDL_Texture* player2_Texture = IMG_LoadTexture(ren, "player2.png");
	SDL_Texture* guard_Texture = IMG_LoadTexture(ren, "guard.png");
	SDL_Texture* sentry_Texture = IMG_LoadTexture(ren, "sentry.png");
	SDL_Texture* orb_Texture = IMG_LoadTexture(ren, "orb.png");
	//SDL_Texture* orb_pinkTexture = IMG_LoadTexture(ren, "orb_pink.png");
	//SDL_Texture* orb_greenTexture = IMG_LoadTexture(ren, "orb_green.png");
	SDL_Texture* orb_purpleTexture = IMG_LoadTexture(ren, "orb_purple.png");

	int orbCounter = 0;
	int wallCounter = 0;
	int pickupCounter = 0;
	int guardCounter = 0;
	int playerCounter = 0;

	for (int i = 0; i < size; i++)//IN ORDER OF MOST COMMON
	{
		for (int j = 0; j < size; j++)
		{
			if (map[i][j] == 0)//WALL
			{
				wallVec.emplace_back(wall_Texture);
				wallVec[wallCounter++].setStartingLocation((j * OBJECT_SIZE), (i * OBJECT_SIZE));
			}
			else if (map[i][j] == 2)//PLAIN ORBS
			{
				orbVec.emplace_back(orb_Texture);
				orbVec[orbCounter++].setStartingLocation((j * OBJECT_SIZE), (i * OBJECT_SIZE));
			}
			else if (map[i][j] == 8)//pickups
			{
				pickupVec.emplace_back(orb_purpleTexture);
				pickupVec[pickupCounter++].setStartingLocation((j * OBJECT_SIZE), (i * OBJECT_SIZE));
			}
			else if (map[i][j] == 7)//guards
			{
				guardVec.emplace_back(guard_Texture);
				guardVec[guardCounter++].setStartingLocation((j * OBJECT_SIZE), (i * OBJECT_SIZE));
			}
			else if ((map[i][j] == 3) || (map[i][j] == 9))//player1
			{
				playerVec.emplace_back(player1_Texture);
				playerVec[playerCounter++].setStartingLocation((j*OBJECT_SIZE), (i*OBJECT_SIZE));
			}
			else if (map[i][j] == 5)//sentry
			{
				sent.texture = sentry_Texture;
				sent.setStartingLocation((j*OBJECT_SIZE), (i*OBJECT_SIZE));
			}
		}
	}
}

Player::Player()
{
}

Player::Player(SDL_Texture * text)
{
	texture = text;
}

void Player::setStartingLocation(int _x, int _y)
{
	starting_x = _x;
	starting_y = _y;
	dst.x = _x + 2;
	dst.y = _y + 2;
	dst.w = dst.h = (OBJECT_SIZE - 4);
}

bool Player::positionCheck(int num)
{
	if (num == 0)
	{
		if (get_currentY() > MAP_HALF)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (get_currentY() < MAP_HALF)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

int Player::getX()
{
	return starting_x;
}

int Player::getY()
{
	return starting_y;
}

int Player::get_currentX()
{
	return (dst.x / dst.w);
}

int Player::get_currentY()
{
	return (dst.y / dst.h);
}

Player::~Player()
{
	texture = nullptr;
	delete texture;
}

Orbs::Orbs()
{
}

Orbs::Orbs(SDL_Texture * text)
{
	texture = text;
}

void Orbs::setStartingLocation(int _x, int _y)
{
	starting_x = _x;
	starting_y = _y;
	dst.x = _x + 5;
	dst.y = _y + 5;
	dst.w = dst.h = (OBJECT_SIZE - 10);
}

int Orbs::getX()
{
	return starting_x;
}

int Orbs::getY()
{
	return starting_y;
}

Orbs::~Orbs()
{
	texture = nullptr;
	delete texture;
}

Pickups::Pickups()
{
}

Pickups::Pickups(SDL_Texture * text)
{
	texture = text;
}

void Pickups::setStartingLocation(int _x, int _y)
{
	starting_x = _x;
	starting_y = _y;
	dst.x = _x + 5;
	dst.y = _y + 5;
	dst.w = dst.h = (OBJECT_SIZE - 10);
}

int Pickups::getX()
{
	return starting_x;
}

int Pickups::getY()
{
	return starting_y;
}

Pickups::~Pickups()
{
	texture = nullptr;
	delete texture;
}

Sentry::Sentry()
{
	speed = 2;
}

Sentry::Sentry(SDL_Texture * text)
{
	texture = text;
}

void Sentry::setStartingLocation(int _x, int _y)
{
	starting_x = _x;
	current_x = _x;
	starting_y = _y;
	current_y = _y;
	dst.x = _x + 2;
	dst.y = _y + 2;
	dst.w = dst.h = OBJECT_SIZE - 4;
}

void Sentry::Move()
{
	if (dst.x > 480)
	{
		moveRight = false;
	}
	else if(dst.x < 120)
	{
		moveRight = true;
	}
	//check the bools and move accordingly.
	if (moveRight == true)
	{
		dst.x += speed;
	}
	else
	{
		dst.x -= speed;
	}


}

int Sentry::getX()
{
	return starting_x;
}

int Sentry::getY()
{
	return starting_y;
}

int Sentry::get_currentX()
{
	return (dst.x / dst.w);
}

Sentry::~Sentry()
{
	texture = nullptr;
	delete texture;
}

Guard::Guard()
{
}

Guard::Guard(SDL_Texture * text)
{
	texture = text;
}

void Guard::setStartingLocation(int _x, int _y)
{
	starting_x = _x;
	current_x = _x;
	starting_y = _y;
	current_y = _y;
	dst.x = _x + 2;
	dst.y = _y + 2;
	dst.w = dst.h = OBJECT_SIZE - 4;
}

int Guard::getX()
{
	return starting_x;
}

int Guard::getY()
{
	return starting_y;
}

int Guard::get_currentX()
{
	return (dst.x / dst.w);
}

int Guard::get_currentY()
{
	return (dst.y / dst.h);
}

Guard::~Guard()
{
	texture = nullptr;
	delete texture;
}

Walls::Walls()
{
}

Walls::Walls(SDL_Texture * text)
{
	texture = text;
}

//Walls::Walls(const Walls & w)
//{
//	//copy constructor for the main map check?
//}

void Walls::setStartingLocation(int _x, int _y)
{
	starting_x = _x;
	starting_y = _y;
	dst.x = _x;
	dst.y = _y;
	dst.w = dst.h = OBJECT_SIZE;
}

int Walls::getX()
{
	return starting_x;
}

int Walls::getY()
{
	return starting_y;
}

Walls::~Walls()
{
	texture = nullptr;
	delete texture;
}

//int movingOBJS::get_currentX(SDL_Rect &rect)
//{
//	return (rect.x / rect.w);
//}
//
//int movingOBJS::get_currentY(SDL_Rect &rect)
//{
//	return (rect.y / rect.h);
//}