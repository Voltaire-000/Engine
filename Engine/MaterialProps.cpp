#include "pch.h"
#include "MaterialProps.h"
#include "Engine_App.h"

//	TODO add class ViewMenuButton here


CMaterialPropsWnd::CMaterialPropsWnd() noexcept
{

}

CMaterialPropsWnd::~CMaterialPropsWnd()
{
}

//========================================
//	Message map
BEGIN_MESSAGE_MAP(CMaterialPropsWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()
//========================================
int CMaterialPropsWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	//	Create views
	//const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndMaterialProperties.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("Failed to create Material properties pane\n");
			return -1;
	}

	m_wndMaterialProperties.EnableHeaderCtrl(FALSE);
	m_wndMaterialProperties.EnableDescriptionArea(TRUE);

	m_wndMaterialProperties.SetVSDotNetLook(TRUE);
	//InitMaterialPropertiesList();

	// Load images for toolbar
	//
	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_MAT_TOOLBAR);
	m_wndToolBar.LoadToolBar(IDR_MAT_TOOLBAR, 0, 0, TRUE /*Is locked*/);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	//	All commands will be routed via this control, not via the parent frame;
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustDockingLayout();
	return 0;
}

void CMaterialPropsWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CMaterialPropsWnd::OnContextMenu(CWnd* pWnd, CPoint point)
{
	//	TODO
}

void CMaterialPropsWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndMaterialProperties.SetFocus();
	//	TODO
}

void CMaterialPropsWnd::AdjustLayout()
{
	if (GetSafeHwnd() == nullptr || (AfxGetMainWnd() != nullptr && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}
	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(nullptr,
		rectClient.left,
		rectClient.top,
		rectClient.Width(),
		cyTlb,
		SWP_NOACTIVATE | SWP_NOZORDER);

	m_wndMaterialProperties.SetWindowPos(nullptr,
		rectClient.left,
		rectClient.top ,
		rectClient.Width(),
		rectClient.Height(),
		SWP_NOACTIVATE | SWP_NOZORDER);
}

//void CMaterialPropsWnd::OnChangeVisualStyle()
//{
//	//m_wndToolBar.LoadBitmapEx(theApp.m_bHiColorIcons ? IDB_TODO_A : IDB_TODO_B, 0, 0, TRUE);
//}

BOOL CMaterialPropsWnd::PreTranslateMessage(MSG* pMsg)
{
	return CDockablePane::PreTranslateMessage(pMsg);
}






