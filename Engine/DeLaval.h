#pragma once
#include "DeLavalBase.h"

///////////////////////////////////////////////////////////
/// <summary>
/// ///Creates the DeLaval Profile
/// </summary>
class DeLaval : public DeLavalBase
{
	//	Construction
public:
	DeLaval();
	//virtual BOOL Create(_In_ DWORD dwStyle, _In_ const RECT& rect, _In_ CWnd* pParentWnd, _In_ UINT nId);

	//	Attributes
protected:
	// TODO check if right
	DeLavalBase m_wndDeLaval;
	CImageList m_Images;
	int m_nMyDeLavalY;

	//	Overrides
public:
	virtual BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT nID = (UINT)-1);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//	Implementation
public:
	virtual ~DeLaval();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()

};

