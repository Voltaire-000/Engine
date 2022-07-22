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
	ON_WM_PAINT()
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
	m_wndToolBar.SetFocus();
	//	TODO
}

void CMaterialPropsWnd::OnPaint()
{
	//	TODO not working
	CPaintDC dc(this);

	CRect rectWnd;
	rectWnd = GetPaneRect();
	//m_wndToolBar.GetPaneRect();
	ScreenToClient(rectWnd);

	rectWnd.InflateRect(1, 200);
	dc.Draw3dRect(rectWnd, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CMaterialPropsWnd::AdjustLayout()
{
	if (GetSafeHwnd() == nullptr)
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
}

void CMaterialPropsWnd::OnChangeVisualStyle()
{
	//m_wndToolBar.LoadBitmapEx(theApp.m_bHiColorIcons ? IDB_TODO_A : IDB_TODO_B, 0, 0, TRUE);
}

BOOL CMaterialPropsWnd::PreTranslateMessage(MSG* pMsg)
{
	return CDockablePane::PreTranslateMessage(pMsg);
}






