#pragma once

class pointAnimation//the animation of the points coming from orbs and score
{
public:
	pointAnimation();
	~pointAnimation();
};

class guardAnimation//the animation of th guard moving across walls
{
	guardAnimation();
	~guardAnimation();
};

class inputAnimation//animation for the input display
{
	inputAnimation();
	~inputAnimation();
};

class slimeAnimation//animation for player trails
{
	slimeAnimation();
	~slimeAnimation();
};

class Animator//used for animation of collision and points.
{
public:
	Animator();
	~Animator();
	inputAnimation inputANIM;
	pointAnimation pointANIM;
	guardAnimation guardANIM;
	slimeAnimation slimeANIM;

private:

};

