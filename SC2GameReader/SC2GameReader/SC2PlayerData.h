#pragma once

#include "stdafx.h"

class SC2PlayerData
{
public:
	Player player;
	Unit * units;
	int UnitCount;
};

class SC2EnvironmentData
{
public:
	bool GameStart; // true if the game has started
	int GameTimer; // in seconds
};

