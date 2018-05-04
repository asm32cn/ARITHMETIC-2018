
// PaSchulteGrid2018MFC2010.h : main header file for the PaSchulteGrid2018MFC2010 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CPaSchulteGrid2018MFC2010App:
// See PaSchulteGrid2018MFC2010.cpp for the implementation of this class
//

class CPaSchulteGrid2018MFC2010App : public CWinApp
{
public:
	CPaSchulteGrid2018MFC2010App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPaSchulteGrid2018MFC2010App theApp;
