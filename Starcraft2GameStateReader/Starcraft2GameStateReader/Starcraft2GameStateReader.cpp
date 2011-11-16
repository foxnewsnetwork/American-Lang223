// Starcraft2GameStateReader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// processName better fucking be 0 terminated or else I'm going to skin your cat
BOOL FindMyProcess( __in WCHAR processName[MAX_PATH] , __out DWORD & processId )
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
		std::cout << "Process name: ";
		for( int k = 0; k < MAX_PATH; k++ )
		{
			std::cout << CHAR(pe32.szExeFile[k]);
			if( CHAR(pe32.szExeFile[k]) != CHAR(processName[k]) )
				break;
			if( pe32.szExeFile[k] == NULL && processName[k] == NULL ) // second part included to look symmetric but not necessary
			{
				processId = pe32.th32ProcessID;
				return TRUE;
			}
		}
		std::cout << std::endl;
	}
	while (Process32Next( hProcessSnap, &pe32 ) );
	CloseHandle(hProcessSnap);
	return FALSE;
}

int _tmain(int argc, _TCHAR* argv[])
{
	WCHAR ap[] = L"SC2.exe";
	DWORD myId;
	BOOL lolcat = FindMyProcess(ap, myId);
	if(!lolcat)
	{
		std::cout << "Starcraft 2 not running" << std::endl;
		return -1;
	}

	// Change the below value 
	DWORD offset = 0x026A6EC0; // offset value for getting the player struct
	DWORD offset2 = 0x026AFEBE; // useless 
	DWORD offset3 = 0x01DF9400; // useless
	DWORD o4 = offset3 - 176*448; // offset value for getting the unit struct
	DWORD o5 = 0x026AFEF0 - 0x32; // useless
	Player myplayer;
	Unit myunit;
	HANDLE sc2proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, myId);
	
	if(sc2proc == NULL)
	{
		std::cout << "Failed to open process" << std::endl;
		return -1;		
	}

	SIZE_T bytesRead;
	BOOL result;
	int size_temp = sizeof(myunit);

	result = ReadProcessMemory(sc2proc, (void*)(offset), (void*)&myplayer, sizeof(myplayer), &bytesRead);
	// result = ReadProcessMemory(sc2proc, (void*)(offset), (void*)&myunit, 448, &bytesRead);
	
	if(result == FALSE || bytesRead != 448) // there is 20 bytes just lolnotaccounted for
		return -2;

	std::cout << "Player 1 has " << myplayer.mineralsCurrent << "minerals." << std::endl;
	CloseHandle(sc2proc);
	return 0;
}

