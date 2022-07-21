#pragma once
#include <afxdockablepane.h>

class COutputWnd : public CDockablePane
{
public:
    COutputWnd() noexcept;
    virtual ~COutputWnd();

    void UpdateFonts();

protected:
    CMFCTabCtrl m_wndTabs;

    CMFCPropertyGridCtrl    m_wndMaterialProperties;
    CMFCPropertyGridCtrl    m_wndObjectTransform;

    //afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

    DECLARE_MESSAGE_MAP()

protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);

    DECLARE_MESSAGE_MAP()

};

