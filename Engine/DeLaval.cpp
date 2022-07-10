#include "pch.h"
#include "framework.h"
#include "DeLaval.h"
#include "Engine_App.h"

#ifdef DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // DEBUG

const int nBorderSize = 10;

//////////////////////////////////////////
//	DeLaval

DeLaval::DeLaval()
{
	m_nMyDeLavalY = 0;
}

DeLaval::~DeLaval()
{

}

BEGIN_MESSAGE_MAP(DeLaval, CWnd)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////
//	DeLaval message handlers

int DeLaval::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy(0, 0, 0, 0);
	//	m_wndDeLaval is CPane, check if correct
	m_wndDeLaval.Create( WS_CHILD | WS_VISIBLE, rectDummy, this, 1);

	CBitmap bmp;
	//bmp.LoadBitmap(IDB_PAGES_SMALL_HC);

	m_Images.Create(16, 16, ILC_COLOR24 | ILC_MASK, 0, 0);
	m_Images.Add(&bmp, RGB(255, 0, 255));

	return 0;
}

BOOL DeLaval::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		//	Ensure that kewboard focus is set to DeLaval
		m_wndDeLaval.SetFocus();
	}

	return CWnd::PreTranslateMessage(pMsg);
}

BOOL DeLaval::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

void DeLaval::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);
	m_wndDeLaval.SetFocus();
}

void DeLaval::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	int nMyDeLavalPaneHeight = 70;

	if (m_wndDeLaval.GetSafeHwnd() != nullptr)
	{
		m_wndDeLaval.SetWindowPos(nullptr, nBorderSize, nBorderSize, cx - 2 * nBorderSize, cy - 2 * nMyDeLavalPaneHeight - 10, SWP_NOZORDER | SWP_NOACTIVATE);
	}

	m_nMyDeLavalY = cy - nMyDeLavalPaneHeight;
}

BOOL DeLaval::Create(const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CWnd::Create(nullptr, _T(""), WS_CHILD | WS_VISIBLE, rect, pParentWnd, nID);
}

void DeLaval::OnPaint()
{
	CPaintDC dc(this);	//	device context for painting

	CRect rectClient;
	GetClientRect(rectClient);

	dc.FillRect(rectClient, &afxGlobalData.brWindow);

	if (rectClient.bottom - m_nMyDeLavalY > 0)
	{
		CRect rectMyDeLavalCaption = rectClient;
		rectMyDeLavalCaption.top = m_nMyDeLavalY;
		rectMyDeLavalCaption.bottom = rectMyDeLavalCaption.top + afxGlobalData.GetTextHeight(TRUE) * 3 / 2;

		COLORREF clrText = CMFCVisualManager::GetInstance()->OnDrawPaneCaption(&dc, nullptr, FALSE, rectMyDeLavalCaption, CRect(0, 0, 0, 0));

		CPen* pOldPen = dc.SelectObject(&afxGlobalData.penBarShadow);

		dc.MoveTo(rectMyDeLavalCaption.left - 1, rectMyDeLavalCaption.top);
		dc.LineTo(rectMyDeLavalCaption.right, rectMyDeLavalCaption.top);

		dc.SelectStockObject(BLACK_PEN);

		dc.MoveTo(rectMyDeLavalCaption.left - 1, rectMyDeLavalCaption.bottom);
		dc.LineTo(rectMyDeLavalCaption.right, rectMyDeLavalCaption.bottom);

		dc.SelectObject(pOldPen);

		CRect rectText = rectMyDeLavalCaption;
		rectText.DeflateRect(10, 0);

		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(clrText);

		CFont* pOldFont = dc.SelectObject(&afxGlobalData.fontRegular);

		BOOL bNameValid;
		CString str;

		bNameValid = str.LoadString(IDS_SHORTCUTS);	//	TODO
		ASSERT(bNameValid);
		dc.DrawText(str, rectText, DT_VCENTER | DT_LEFT | DT_SINGLELINE);

		CRect rectDeLaval = rectClient;
		rectDeLaval.top = rectMyDeLavalCaption.bottom + 5;
		rectDeLaval.bottom = rectDeLaval.top + afxGlobalData.GetTextHeight(TRUE) * 3 / 2 - 5;

		dc.FillSolidRect(rectDeLaval, RGB(255, 255, 213));

		rectDeLaval.left += 20;
		m_Images.Draw(&dc, 3, rectDeLaval.TopLeft(), 0);

		rectDeLaval.left += 20;

		bNameValid = str.LoadString(IDS_SHORTCUTS);		//	TODO
		ASSERT(bNameValid);

		dc.SetTextColor(afxGlobalData.clrHotLinkNormalText);
		dc.DrawText(str, rectDeLaval, DT_VCENTER | DT_LEFT | DT_SINGLELINE);

		dc.SelectObject(pOldFont);
	}
}