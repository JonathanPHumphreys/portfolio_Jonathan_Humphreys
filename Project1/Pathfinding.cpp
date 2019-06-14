#include "Pathfinding.h"



Pathfinding::Pathfinding()
{
	active = false;
}

void Pathfinding::cost_calc(std::vector<std::vector<int>> g, std::vector<std::vector<int>> h, int num)
{
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			F_COST[i][j] = (g[i][j] + h[i][j]);
		}
	}
}

void Pathfinding::cost_calc(int x, int y, int num)
{
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			g_cost[i][j] = (j - x) + (i - y);
		}
	}
}

void Pathfinding::cost_calc(int x1, int y1, int x2, int y2, int num)
{
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			h_cost[i][j] = (x1 - x2) + (y1 - y2);
		}
	}
}


Pathfinding::~Pathfinding()
{
}
