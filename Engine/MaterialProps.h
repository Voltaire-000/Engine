#pragma once
#include <afxdockablepane.h>

class CMatToolBar : public CMFCToolBar
{
    virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
    {
        CMFCToolBar::OnUpdateCmdUI((CFrameWnd*)GetOwner(), bDisableIfNoHndler);
    }

    virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CMaterialProps :
    public CDockablePane
{
public:
    CMaterialProps() noexcept;
    virtual ~CMaterialProps();

    void AdjustLayout();
    void OnChangeVisualStyle();

protected:
    CMatToolBar m_wndToolBar;

    //  Overrides
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
    //  Messages
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    afx_msg void OnPaint();
    afx_msg void OnSetFocus(CWnd* pOldWnd);

    DECLARE_MESSAGE_MAP()
};

