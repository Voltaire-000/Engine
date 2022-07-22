#include "pch.h"
#include "SceneProperties.h"
#include "Engine_App.h"

BEGIN_MESSAGE_MAP(CScenePropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()


CScenePropertiesWnd::CScenePropertiesWnd() noexcept
{
}

CScenePropertiesWnd::~CScenePropertiesWnd()
{
}

void CScenePropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd() == nullptr || (AfxGetMainWnd() != nullptr && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}
	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndSceneToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndSceneToolBar.SetWindowPos(nullptr,
		rectClient.left,
		rectClient.top,
		rectClient.Width(),
		cyTlb,
		SWP_NOACTIVATE | SWP_NOZORDER);

	m_wndSceneProperties.SetWindowPos(nullptr,
		rectClient.left,
		rectClient.top,
		rectClient.Width(),
		rectClient.Height(),
		SWP_NOACTIVATE | SWP_NOZORDER);
}

int CScenePropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	//	add controls

	if (!m_wndSceneProperties.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 7))
	{
		TRACE0("Failed to create Scene properties pane\n");
		return -1;
	}

	m_wndSceneProperties.EnableHeaderCtrl(TRUE);
	m_wndSceneProperties.EnableDescriptionArea(TRUE);

	//	create the Scene toolbar
	m_wndSceneToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_SCENE_TOOLBAR);
	m_wndSceneToolBar.LoadToolBar(IDR_SCENE_TOOLBAR, 0, 0, TRUE /*Is locked*/);
	m_wndSceneToolBar.SetPaneStyle(m_wndSceneToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndSceneToolBar.SetPaneStyle(m_wndSceneToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndSceneToolBar.SetOwner(this);

	//	All commands will be routed via this control, not via the parent frame;
	m_wndSceneToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustDockingLayout();
	return 0;
}


void CScenePropertiesWnd::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: Add your message handler code here
}


void CScenePropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}


void CScenePropertiesWnd::AssertValid() const
{
	CDockablePane::AssertValid();

	// TODO: Add your specialized code here and/or call the base class
}


void CScenePropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndSceneProperties.SetFocus();
}
