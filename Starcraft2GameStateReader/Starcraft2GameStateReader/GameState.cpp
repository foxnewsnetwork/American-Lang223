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
	Unit myunits[500]; // Struct for the units arbitrarily set to 500
	SIZE_T bytesRead; // The amount of data read
	BOOL result; // The results of each reading
	
	// Step 1: Attempt reading the first player
	result = ReadProcessMemory(this->processHandle, (void*)(this->playerOffset), (void*)&myplayer, sizeof(myplayer), &bytesRead);
	if( !result || bytesRead != 2264 )
		return false;

	// Step 2: Initializing the output data for the player 
	if( State == NULL )
		State = new SC2PlayerData;

	// Step 3: setting the player variable
	State->player = myplayer;
	State->UnitCount = myplayer.army_size;

	// Step 3.5: we have to find where player 0 ends and where player 1 begins. We do this with an iterative binary tree
	int lolcat = this->FindFirstPlayerUnit(0, 200);
	DWORD actual_offset = this->unitOffset + lolcat * sizeof(Unit);

	// Step 4: now we need to read all the units that belong to a given player
	int temp = sizeof(Unit);
	Unit * temp2;
	int temp3 = sizeof(temp2);
	result = ReadProcessMemory(this->processHandle, (void*)(actual_offset), (void*)&myunits, sizeof(Unit) * (State->UnitCount), &bytesRead);
	if( !result )
		return false;
	State->units = myunits;

	// Step 5: we're done
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
	if( !result || bytesRead != 448 )
		return false;

	// Step 2.5: making the output if it doesn't exist
	if(State == NULL)
		State = new SC2EnvironmentData;

	// Step 3: determining the game states
	if(myplayer.buildings_current > 0 && myplayer.buildings_current < 200)
		State->GameStart = true;
	else
		State->GameStart = false;

	// Step 4: Do something about the timer (don't know how)

	// Step 5: we're done
	return true;

}


CGameState * CGameState::Initialize(void)
{
	CGameState * pGameState = NULL;

	// Step 0: Find the SC2 Process handle
	DWORD processId;
	BOOL result = CGameState::FindMyProcess( L"SC2.exe", processId );

	// If we can't find it, then the user obviously doesn't have sc2 running so we just return the error
	if(result != TRUE)
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

	// Step 3: we're done
	return pGameState;
}


// Finds the process Id of Starcraft 2 on a given windows machine
BOOL CGameState::FindMyProcess( __in WCHAR processName[MAX_PATH] , __out DWORD & processId )
{
	HANDLE hProcessSnap;
	HANDLE hProcess;
	PROCESSENTRY32 pe32;
	DWORD dwPriorityClass;

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	if( hProcessSnap == INVALID_HANDLE_VALUE )
	{
		// We've encountered a terrible terrible error and we ought to abandon this endeavor
		return NULL;
	}

	// Set the size of the structure before using it.
	pe32.dwSize = sizeof( PROCESSENTRY32 );

	// Retrieve information about the first process,
	// and exit if unsuccessful
	if( !Process32First( hProcessSnap, &pe32 ) )
	{
		// Cause of error at Process32First
		CloseHandle( hProcessSnap );          // clean the snapshot object
		return( NULL );
	}

	// Setting up the variables
	TCHAR filename[MAX_PATH];

	// Now we walk the snapshot of processes
	// and look for SC2; we return it if found
	// if not, we give up
	
	do
	{
		// std::cout << "Process name: ";
		for( int k = 0; k < MAX_PATH; k++ )
		{
			// std::cout << CHAR(pe32.szExeFile[k]);
			if( CHAR(pe32.szExeFile[k]) != CHAR(processName[k]) )
				break;
			if( pe32.szExeFile[k] == NULL && processName[k] == NULL ) // second part included to look symmetric but not necessary
			{
				processId = pe32.th32ProcessID;
				return TRUE;
			}
		}
		// std::cout << std::endl;
	}
	while (Process32Next( hProcessSnap, &pe32 ) );
	CloseHandle(hProcessSnap);
	return FALSE;
}


// Sets the offset values for a given instance of the reader
void CGameState::EstablishOffsets(void)
{
	// As I have said, this ought to be done intelligently via stream-based machine learning
	// in the nearby future. For now, however, I will simply declare the values (lol)
	this->playerOffset = 0x026A6EC0; // come to think of it, these should probably be constants
	this->unitOffset = 0x01DE6000; // Do some research and find out this value!
}


// Returns the count of the array and writes the data into the pdata
int CGameState::ReadStarcraftData(__out LPVOID pdata)
{
	// Not implemented
	return 0;
}


// finds the amount of unitary offset from the unitOffset of the first unit belonging to player 1
// doing it iteratively to avoid trouble
int CGameState::FindFirstPlayerUnit(int initial_position, int end_position)
{
	// Step 0: declare the tools I will need
	Unit myunits[2]; // Struct for the units
	SIZE_T bytesRead; // The amount of data read
	BOOL result; // The results of each reading
	DWORD start = this->unitOffset + initial_position * sizeof(Unit);
	int wtf = (end_position - initial_position) / 2;
	DWORD mid = this->unitOffset + (wtf + initial_position) * sizeof(Unit);
	DWORD end = this->unitOffset + end_position * sizeof(Unit);

	// Step 1: We check to see if we're within range
	result = ReadProcessMemory(this->processHandle, (void*)start, (void*)&myunits[0], sizeof(Unit), &bytesRead);
	if( !result )
		return -2; // memory read error
	if( myunits[0].playerOwner != 0 )
		return -1; // bad start range

	result = ReadProcessMemory(this->processHandle, (void*)end, (void*)&myunits[1], sizeof(Unit), &bytesRead);
	if( !result )
		return -2; // memory read error
	if( myunits[1].playerOwner != 1 )
		return -1; // bad end range
	
	// Step 1.5: Terminating cases
	if( end_position == initial_position + 1 )
		return end_position;
	if( (end_position - initial_position) == 2 )
	{
		result = ReadProcessMemory(this->processHandle, (void*)mid, (void*)&myunits[0], sizeof(Unit), &bytesRead);
		if( !result )
			return -2; // memory read error
		if( myunits[0].playerOwner == 0 )
			return end_position;
		else
			return end_position - 1;
	}

	// Step 2: We check the middle
	result = ReadProcessMemory(this->processHandle, (void*)mid, (void*)&myunits, sizeof(Unit)*2, &bytesRead);
	if( !result )
		return -2; // memory read error
	if( myunits[0].playerOwner != myunits[1].playerOwner ) // we've found crossover
		return mid+1;

	// Step 3: We setup the recursion
	if( myunits[0].playerOwner == 0 )
		return this->FindFirstPlayerUnit( wtf+initial_position+1, end_position );
	else if( myunits[1].playerOwner == 1 )
		return this->FindFirstPlayerUnit( initial_position, end_position-wtf-1 );
	else
		return -1; // argument out of range
}
