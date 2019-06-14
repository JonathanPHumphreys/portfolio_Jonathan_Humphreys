#pragma once
#include "constants.h"

class Pathfinding
{
public:
	Pathfinding();
	void cost_calc(std::vector<std::vector<int>> g, std::vector<std::vector<int>> h, int num);//FCOST : 
	void cost_calc(int x, int y, int num);//GCOST : x = j, y = i
	void cost_calc(int x1, int y1, int x2, int y2, int num);//HCOST : 1 = guard, 2 = player
	std::vector<std::vector<int>> g_cost;//cost to move the guard.
	std::vector<std::vector<int>> h_cost;//this is how far the guard is from the target(player).
	std::vector<std::vector<int>> F_COST;// g+h cost
	bool active;
	~Pathfinding();
private:
};

