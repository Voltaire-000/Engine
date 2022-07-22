
// MainFrm.h : interface of the CMainFrame class
//

#pragma once

#include "DeLaval.h"
#include "MaterialProps.h"

class COutlookBar : public CMFCOutlookBar
{
	virtual BOOL AllowShowOnPaneMenu() const { return TRUE; }
	virtual void GetPaneName(CString& strName) const { BOOL bNameValid = strName.LoadStringW(IDS_OUTLOOKBAR); ASSERT(bNameValid); if (!bNameValid) strName.Empty(); }
};

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame() noexcept;

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = nullptr, CCreateContext* pContext = nullptr);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CMFCMenuBar			m_wndMenuBar;
	CMFCToolBar			m_wndToolBar;
	CMFCStatusBar		m_wndStatusBar;
	CMFCToolBarImages	m_UserImages;
	COutlookBar			m_wndNavigationBar;
	
	CMaterialPropsWnd	m_wndMatProperties;
	DeLaval				m_wndDeLaval;


// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();

	//void SetDockingWindowIcons(BOOL bHiColorIcons);
	BOOL CreateOutlookBar(CMFCOutlookBar& bar, UINT uiID, DeLaval& delaval, int nInitialWidth);

	//int FindFocusedOutlookWnd(CMFCOutlookBarTabCtrl** ppOutlookWnd);

	//CMFCOutlookBarTabCtrl*	FindOutlookParent(CWnd* pWnd);
	CMFCOutlookBarTabCtrl*		m_pCurrOutlookWnd;
	CMFCOutlookBarPane*			m_pCurrOutlookPage;

};


