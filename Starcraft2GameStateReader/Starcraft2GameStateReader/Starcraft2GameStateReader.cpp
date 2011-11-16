// Starcraft2GameStateReader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



int _tmain(int argc, _TCHAR* argv[])
{
	// Change the below value 
	DWORD offset = 0x026A6EC0; // offset value for getting the player struct
	DWORD offset2 = 0x026AFEBE; // useless 
	DWORD offset3 = 0x01DF9400; // useless
	DWORD o4 = offset3 - 176*448; // offset value for getting the unit struct
	DWORD o5 = 0x026AFEF0 - 0x32; // useless
	Player myplayer;
	Unit myunit;
	HANDLE sc2proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 0x000013A0);
	
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

