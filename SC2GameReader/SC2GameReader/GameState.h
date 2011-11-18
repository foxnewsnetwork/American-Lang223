#pragma once

#include "stdafx.h"

// Stuff or DLL management
#ifdef STARCRAFTREADER_API
#undef STARCRAFTREADER_API
#endif

#ifdef STARCRAFTREADER_EXPORTS
#define STARCRAFTREADER_API   __declspec(dllexport)
#else
#define STARCRAFTREADER_API   __declspec(dllimport)
#endif

class STARCRAFTREADER_API CGameState
{
public:
	const static int StarcraftVersion = 142; // that is, 1.4.2

protected:
	CGameState(void);
	virtual ~CGameState(void);

protected:
	// The amount offset for a given player
	DWORD playerOffset;
	
	// The amount of offset required for th first unit
	DWORD unitOffset;

	// The handle to the SC2 process
	HANDLE processHandle;

public:
	// Retrieves the player state variables
	bool RetrievePlayerState(__out SC2PlayerData * State);
	// Retreives the environment variables
	bool RetrieveEnvironmentState(__out SC2EnvironmentData * State);
	// Initializes the reader; must call this before using the retrieve functions (obviously)
	static CGameState * Initialize(void);

protected:
	// Finds the process Id of Starcraft 2 on a given windows machine
	static BOOL FindMyProcess(__in WCHAR processName[MAX_PATH] , __out DWORD & processId);
	// Sets the offset values for a given instance of the reader
	void EstablishOffsets(void);
	// Returns the count of the array and writes the data into the pdata
	int ReadStarcraftData(__out LPVOID pdata);
};

