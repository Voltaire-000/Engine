#include "pch.h"
#include "framework.h"
#include "DeLaval.h"
#include "Engine_App.h"
#include "Engine_Doc_Viewer.h"

#ifdef DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // DEBUG

const int nBorderSize = 10;

//////////////////////////////////////////
//	DeLaval

DeLaval::DeLaval() noexcept
	:m_nComboHeight(24)
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
	ON_COMMAND(IDC_BUTTON_PROFILE, &CEngineDoc::OnDrawLiner)
END_MESSAGE_MAP()

void DeLaval::AdjustLayout()
{
	if (GetSafeHwnd() == nullptr || (AfxGetMainWnd() != nullptr && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	//=================================================
	//	Combo dropdown position
	m_wndPropellantCombo.SetWindowPos(
		nullptr,
		rectClient.left + ID_STYLE_MARGIN_LEFT,
		rectClient.top,
		ID_STYLE_RIBBON_WIDTH,
		m_nComboHeight,
		SWP_NOACTIVATE | SWP_NOZORDER);
	CRect m_ComboRect;
	m_wndPropellantCombo.GetWindowRect(m_ComboRect);
	int m_PropellantComboHeight = m_ComboRect.Height();
	// end combo position
	//================================================
	// 
	//================================================
	//	Button position
	m_wndProfileButton.SetWindowPos(
		nullptr,
		rectClient.left + ID_STYLE_MARGIN_LEFT,
		m_PropellantComboHeight + 10,
		ID_STYLE_RIBBON_WIDTH,
		ID_STYLE_MARGIN_TOP,
		SWP_NOACTIVATE | SWP_NOZORDER);
	CRect m_ButtonRect;
	m_wndProfileButton.GetWindowRect(m_ButtonRect);
	int m_ProfileButtonHeight = m_ButtonRect.Height();
	//	end button position
	//================================================
	//
	//================================================
	//	Property list position
	m_wndPropertyList.SetWindowPos(
		nullptr,
		rectClient.left + ID_STYLE_MARGIN_LEFT,
		m_nComboHeight + m_PropellantComboHeight + m_ProfileButtonHeight + 10,
		ID_STYLE_RIBBON_WIDTH,
		250,
		SWP_NOACTIVATE | SWP_NOZORDER);
	// end
	//================================================
}

//====================================================
//	DeLaval message handlers

int DeLaval::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CRect rectDummy(0, 0, 0, 0);
	rectDummy.SetRectEmpty();

	//	create main pane
	m_wndDeLaval.Create(WS_CHILD | WS_VISIBLE, rectDummy, this, 1);

	CBitmap bmp;
	//bmp.LoadBitmap(IDB_PAGES_SMALL_HC);

	m_Images.Create(16, 16, ILC_COLOR24 | ILC_MASK, 0, 0);
	m_Images.Add(&bmp, RGB(255, 0, 255));

	//=================================================================
	// Creates the Propellant Combobox
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	if (!m_wndPropellantCombo.Create(dwViewStyle, rectDummy, this, 2))
	{
		TRACE0("Failed to create DeLaval Combobox\n");
		return -1;
	}

	//	add the items to the combobox
	m_wndPropellantCombo.AddString(_T("Prop Specs"));
	m_wndPropellantCombo.AddString(_T("Fuel Type"));
	m_wndPropellantCombo.SetCurSel(1);

	CRect rectCombo;
	m_wndPropellantCombo.GetClientRect(&rectCombo);
	int m_nComboHeight = rectCombo.Height();
	//	end combobox
	//===================================================

	//===================================================
	//	Create Button id # 3
	if (!m_wndProfileButton.Create(L"Make profile", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, rectDummy, this, 3))
	{
		TRACE0("Failed to create Button\n");
		return -1;
	}

	CRect rectButton;
	m_wndProfileButton.GetClientRect(&rectButton);
	int m_nButtonHeight = rectButton.Height();
	//	end Button
	//===================================================

	//===================================================
	//	Create Properties list
	if (!m_wndPropertyList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 4))
	{
		TRACE0("Failed to create property grid\n");
		return -1;
	}
	InitPropList();
	//	end Properties list
	//===================================================

	AdjustLayout();
	return 0;
}

BOOL DeLaval::PreTranslateMessage(MSG* pMsg)
{
	//if (pMsg->message == WM_LBUTTONDOWN)
	//{
	//	//	Ensure that kewboard focus is set to DeLaval
	//	m_wndDeLaval.SetFocus();
	//}

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

void DeLaval::OnCreateProfile()
{

}

void DeLaval::InitPropList()
{
	SetPropListFont();

	m_wndPropertyList.EnableHeaderCtrl(TRUE);
	m_wndPropertyList.EnableDescriptionArea(TRUE);
	m_wndPropertyList.SetVSDotNetLook();

	//	first group and subitems
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Dimensions"));
														/// NAME // default value false	// description area text	
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("3D Look"), (_variant_t)false, _T("Font non-bold")));
																	///	NAME  //						//	description area text
	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("Border"), _T("Dialog Frame"), _T("One of: None, Thin, Resizable, or Dialog Frame"));
	pProp->AddOption(_T("None"));
	pProp->AddOption(_T("Thin"));
	pProp->AddOption(_T("Resizable"));
	pProp->AddOption(_T("Dialog Frame"));
	pProp->AllowEdit(FALSE);

	pGroup1->AddSubItem(pProp);
														//	NAME  //////						//	description area text
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Caption"), (_variant_t)_T("About"), _T("Specifies the text that will be displayed in the window's title bar")));

	m_wndPropertyList.AddProperty(pGroup1);
	//	end first group and subitems
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//	second group and subitems
	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("Window Size"), 0, TRUE);

	pProp = new CMFCPropertyGridProperty(_T("Height"), (_variant_t)250l, _T("Specifies the window's height"));
	pProp->EnableSpinControl(TRUE, 50, 300);
	pSize->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("Width"), (_variant_t)150l, _T("Specifies the window's width"));
	pProp->EnableSpinControl(TRUE, 50, 200);
	pSize->AddSubItem(pProp);

	m_wndPropertyList.AddProperty(pSize);
	m_wndPropertyList.ExpandAll();

	int pcount = m_wndPropertyList.GetPropertyCount();	//	2
	int rowheight = m_wndPropertyList.GetRowHeight();	//	19
	auto m0 = m_wndPropertyList.GetProperty(0);	// Dimensions caption
	auto m1 = m_wndPropertyList.GetProperty(1)->GetSubItem(1)->GetValue();	//	Window size, and subitem value
}

void DeLaval::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirectW(&lf);

	m_wndPropertyList.SetFont(&m_fntPropList);

}

void DeLaval::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	int nMyDeLavalPaneHeight = 70;

	if (m_wndDeLaval.GetSafeHwnd() != nullptr)
	{
		m_wndDeLaval.SetWindowPos(nullptr,
			nBorderSize, nBorderSize,
			cx - 2 * nBorderSize,
			cy - 2 * nMyDeLavalPaneHeight - 10,
			SWP_NOZORDER | SWP_NOACTIVATE);
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
