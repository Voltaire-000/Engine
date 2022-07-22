#pragma once
#include <afxdockablepane.h>

class CMatPropsToolBar : public CMFCToolBar
{
    virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
    {
        CMFCToolBar::OnUpdateCmdUI((CFrameWnd*)GetOwner(), bDisableIfNoHndler);
    }

    virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CMaterialPropsWnd :
    public CDockablePane
{
public:
    CMaterialPropsWnd() noexcept;
    virtual ~CMaterialPropsWnd();

    void AdjustLayout();

public:
    void SetVSDotNetLook(BOOL bSet)
    {
        m_wndMaterialProperties.SetVSDotNetLook(bSet);
        m_wndMaterialProperties.SetGroupNameFullWidth(bSet);
    }

protected:
    CMatPropsToolBar        m_wndToolBar;
    CMFCPropertyGridCtrl    m_wndMaterialProperties;

    //  Overrides
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
    //  Messages
    afx_msg int     OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void    OnSize(UINT nType, int cx, int cy);
    afx_msg void    OnContextMenu(CWnd* pWnd, CPoint point);
    afx_msg void    OnSetFocus(CWnd* pOldWnd);

    DECLARE_MESSAGE_MAP()
};

