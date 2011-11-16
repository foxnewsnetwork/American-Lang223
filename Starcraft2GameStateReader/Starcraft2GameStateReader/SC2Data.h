#pragma once

#include "StdAfx.h"

class SC2PlayerData
{
public:
	Player player;
	CTypedPtrList<Unit, Unit*> * units;
	// Unit * units;
	// int unitCount;
};

class SC2EnvironmentData
{
public:
	bool gamestart; // true if we're in a game
	int gametimer; // in-game seconds

}