#include "pch.h"
#include "MaterialProps.h"
#include "Engine_App.h"

//	TODO add class ViewMenuButton here


CMaterialProps::CMaterialProps() noexcept
{

}

CMaterialProps::~CMaterialProps()
{
}

//========================================
//	Message map
BEGIN_MESSAGE_MAP(CMaterialProps, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()
//========================================
int CMaterialProps::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	//	All commands will be routed via this control, not via the parent frame;
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	return 0;
}

void CMaterialProps::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CMaterialProps::OnContextMenu(CWnd* pWnd, CPoint point)
{
	//	TODO
}

void CMaterialProps::OnPaint()
{
	//	TODO
}

void CMaterialProps::OnSetFocus(CWnd* pOldWnd)
{
	//	TODO
}

void CMaterialProps::AdjustLayout()
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

void CMaterialProps::OnChangeVisualStyle()
{
	//m_wndToolBar.LoadBitmapEx(theApp.m_bHiColorIcons ? IDB_TODO_A : IDB_TODO_B, 0, 0, TRUE);
}

BOOL CMaterialProps::PreTranslateMessage(MSG* pMsg)
{
	return CDockablePane::PreTranslateMessage(pMsg);
}






