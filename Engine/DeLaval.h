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
	// fix incomplete type DeLaval
	DeLavalBase				m_wndDeLaval;
	CImageList				m_Images;
	int						m_nMyDeLavalY;
	int						m_nComboHeight;
	CComboBox				m_wndPropellantCombo;
	CButton					m_wndProfileButton;
	CButton					m_wndBooleanButton;
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
	afx_msg void OnCut();
	afx_msg void OnFuse();

	afx_msg void OnSample();

	afx_msg void On2dFillet();
	afx_msg void OnSketchCircle();

	DECLARE_MESSAGE_MAP()
protected:
	CFont	m_fntPropList;

	void InitPropList();
	void SetPropListFont();

};

