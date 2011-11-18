#pragma once

#include "stdafx.h"
// DLL- stuff
#ifdef STARCRAFTREADER_API
#undef STARCRAFTREADER_API
#endif

#ifdef STARCRAFTREADER_EXPORTS
#define STARCRAFTREADER_API   __declspec(dllexport)
#else
#define STARCRAFTREADER_API   __declspec(dllimport)
#endif

class STARCRAFTREADER_API SC2PlayerData
{
public:
	Player player;
	Unit * units;
	int UnitCount;
};

class STARCRAFTREADER_API SC2EnvironmentData
{
public:
	bool GameStart; // true if the game has started
	int GameTimer; // in seconds
};

