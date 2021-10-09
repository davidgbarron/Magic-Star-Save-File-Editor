
// Mario64SaveFileEditorMFC.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMario64SaveFileEditorMFCApp:
// See Mario64SaveFileEditorMFC.cpp for the implementation of this class
//

class CMario64SaveFileEditorMFCApp : public CWinApp
{
public:
	CMario64SaveFileEditorMFCApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMario64SaveFileEditorMFCApp theApp;
