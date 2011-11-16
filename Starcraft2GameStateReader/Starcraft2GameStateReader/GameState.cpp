#include "StdAfx.h"
#include "GameState.h"


CGameState::CGameState(void)
	: playerOffset(0)
	, unitOffset(0)
	, processHandle(0)
{
}


CGameState::~CGameState(void)
{
	CloseHandle(this->processHandle);
}

// The structure of the player state will look 
bool CGameState::RetrievePlayerState(__out SC2PlayerData * State)
{
	// Step 0: declare the tools I will need
	Player myplayer; // Struct for the player
	Unit myunit; // Struct for the units
	SIZE_T bytesRead; // The amount of data read
	BOOL result; // The results of each reading

	// Step 1: Attempt reading the first player
	result = ReadProcessMemory(this->processHandle, (void*)(this->playerOffset), (void*)&myplayer, sizeof(myplayer), &bytesRead);
	if( !result || bytesRead != 2264 )
		return false;

	// Step 2: Attempt reading the first unit
	result = ReadProcessMemory(this->processHandle, (void*)(this->unitOffset), (void*)&myunit, sizeof(myunit), &bytesRead);
	if( !result || bytesRead != 468 )
		return false;

	// Step 3: Initializing the output data for the player
	State->player = myplayer;

	// Step 4: setting up the unit data
	State->units = new CTypedPtrList<Unit, Unit*>;
	if(myunit.playerOwner == *myplayer.name)
	{
		State->units->AddHead(&myunit);
	}

	// Step 5: We're done
	return true;
}


// Retreives the environment variables
bool CGameState::RetrieveEnvironmentState(__out SC2EnvironmentData * State)
{
	// Step 0: declare the tools I will need
	Player myplayer; // Struct for the player
	Unit myunit; // Struct for the units
	SIZE_T bytesRead; // The amount of data read
	BOOL result; // The results of each reading

	// Step 1: Attempt reading the first player
	result = ReadProcessMemory(this->processHandle, (void*)(this->playerOffset), (void*)&myplayer, sizeof(myplayer), &bytesRead);
	if( !result || bytesRead != 2264 )
		return false;

	// Step 2: Attempt reading the first unit
	result = ReadProcessMemory(this->processHandle, (void*)(this->unitOffset), (void*)&myunit, sizeof(myunit), &bytesRead);
	if( !result || bytesRead != 468 )
		return false;

	// Step 3: determining the game states
	
	State->gamestart = true;

}


CGameState * CGameState::Initialize(void)
{
	CGameState * pGameState = NULL;

	// Step 0: Find the SC2 Process handle
	DWORD processId = CGameState::FindProcessId();

	// If we can't find it, then the user obviously doesn't have sc2 running so we just return the error
	if(processId == NULL)
		return pGameState;
	else
		pGameState = new CGameState;

	// Step 1: Get the handle to the sc2process
	pGameState->processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

	// We should check again if we've failed to open the correct process
	if(pGameState->processHandle == NULL)
		return 0;

	// Step 2: Set the offsets (eventually this ought to be done intelligently)
	pGameState->EstablishOffsets();
}


// Finds the process Id of Starcraft 2 on a given windows machine
DWORD CGameState::FindProcessId(void)
{
	// Implement me!
	return 0;
}


// Sets the offset values for a given instance of the reader
void CGameState::EstablishOffsets(void)
{
	// As I have said, this ought to be done intelligently via stream-based machine learning
	// in the nearby future. For now, however, I will simply declare the values (lol)
	this->playerOffset = 0x26A6EC0;
	this->unitOffset = 0; // Do some research and find out this value!
}


// Returns the count of the array and writes the data into the pdata
int CGameState::ReadStarcraftData(__out LPVOID pdata)
{
	// Not implemented
	return 0;
}
