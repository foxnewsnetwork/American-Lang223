// SC2GameReader.h : main header file for the SC2GameReader DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSC2GameReaderApp
// See SC2GameReader.cpp for the implementation of this class
//

class CSC2GameReaderApp : public CWinApp
{
public:
	CSC2GameReaderApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
