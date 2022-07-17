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
	DeLaval() noexcept;
	
	void AdjustLayout();

	//	Attributes
protected:
	// TODO check if right
	DeLavalBase				m_wndDeLaval;
	CImageList				m_Images;
	int						m_nMyDeLavalY;
	int						m_nComboHeight;
	CComboBox				m_wndPropellantCombo;
	CButton					m_wndProfileButton;
	CEdit					m_wndDevEdit;
	CMFCPropertyGridCtrl	m_wndPropertyList;

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
	afx_msg void OnCreateProfile();

	DECLARE_MESSAGE_MAP()
protected:
	CFont	m_fntPropList;

	void InitPropList();
	void SetPropListFont();

};

