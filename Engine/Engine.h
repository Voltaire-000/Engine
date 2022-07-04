
// Engine.h : main header file for the Engine application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CEngineApp:
// See Engine.cpp for the implementation of this class
//

class CEngineApp : public CWinAppEx
{
private:
	Handle(Graphic3d_GraphicDriver) m_GraphicDriver;
public:
	CEngineApp() noexcept;
	Handle(Graphic3d_GraphicDriver) GetGraphicDriver()
	{
		return m_GraphicDriver;
	}


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEngineApp theApp;
