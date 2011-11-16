#pragma once

#include "stdafx.h"

class CGameState
{
public:
	const int StarcraftVersion = 142; // that is, 1.4.2

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
	static DWORD FindProcessId(void);
	// Sets the offset values for a given instance of the reader
	void EstablishOffsets(void);
	// Returns the count of the array and writes the data into the pdata
	int ReadStarcraftData(__out LPVOID pdata);
};
