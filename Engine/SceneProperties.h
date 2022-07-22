#pragma once
#include <afxdockablepane.h>

class CScenePropertiesToolBar : public CMFCToolBar
{
    virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
    {
        CMFCToolBar::OnUpdateCmdUI((CFrameWnd*)GetOwner(), bDisableIfNoHndler);
    }

    virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CScenePropertiesWnd :
    public CDockablePane
{
public:
    CScenePropertiesWnd() noexcept;
    virtual ~CScenePropertiesWnd();

    void AdjustLayout();

public:
    void SetVSDotNetLook(BOOL bSet)
    {
        m_wndSceneProperties.SetVSDotNetLook(bSet);
        m_wndSceneProperties.SetGroupNameFullWidth(bSet);
    }

protected:
    CScenePropertiesToolBar     m_wndSceneToolBar;
    CMFCPropertyGridCtrl        m_wndSceneProperties;

protected:
    DECLARE_MESSAGE_MAP()
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    virtual void AssertValid() const;
protected:
    afx_msg void OnSetFocus(CWnd* pOldWnd);
};

