#include "pch.h"
#include "framework.h"
#include "DeLaval.h"
#include "Engine_App.h"
#include "Engine_Doc_Viewer.h"
#include "Engine_View.h"
#include "BooleanOperations.h"

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
	//ON_COMMAND(IDC_BUTTON_PROFILE, &CEngineDoc::OnDrawLiner)
	ON_BN_CLICKED(IDC_BUTTON_PROFILE, &DeLaval::OnCreateProfile)
	ON_BN_CLICKED(IDC_BUTTON_CUT, &DeLaval::OnCut)
	//ON_BN_CLICKED(IDC_BUTTON_CUT, &DeLaval::OnFuse)
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
		rectClient.top + 0,
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
	CRect m_PropertyListRect;
	m_wndPropertyList.GetWindowRect(m_PropertyListRect);
	int m_propertyListHeight = m_PropertyListRect.Height();
	// end property list
	//================================================
	//	Boolean button position
	m_wndBooleanButton.SetWindowPos(
		nullptr,
		rectClient.left + ID_STYLE_MARGIN_LEFT,
		m_nComboHeight + m_PropellantComboHeight + m_ProfileButtonHeight + m_propertyListHeight + 10,
		ID_STYLE_RIBBON_WIDTH,
		ID_STYLE_MARGIN_TOP,
		SWP_NOACTIVATE | SWP_NOZORDER);
	//	end button Boolean
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
	//	Create Profile Button id # 3
	if (!m_wndProfileButton.Create(L"Make profile", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, rectDummy, this, IDC_BUTTON_PROFILE))
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
	//	end Properties list
	//===================================================
	
	//===================================================
	//	create Boolean button id 6
	if(!m_wndBooleanButton.Create(L"Cut shapes", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, rectDummy, this, IDC_BUTTON_CUT))
	{
		TRACE0("Failed to create Boolean button\n");
			return -1;
	}
	//	end Boolean button
	//===================================================

	InitPropList();
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
	int pcount =		m_wndPropertyList.GetPropertyCount();
	int subitemscount = m_wndPropertyList.GetProperty(0)->GetSubItemsCount();
	int theRadius =		m_wndPropertyList.GetProperty(0)->GetSubItem(0)->GetValue().intVal;
	int theThickness =	m_wndPropertyList.GetProperty(0)->GetSubItem(1)->GetValue().intVal;
	auto theLength =	m_wndPropertyList.GetProperty(0)->GetSubItem(2)->GetValue().intVal;

	auto theMaterial = m_wndPropertyList.GetProperty(0)->GetSubItem(3);
	auto mv = theMaterial->GetValue();
	CString cs = mv;

	//	Gets the document window
	CMDIFrameWndEx* pMainWndEx = (CMDIFrameWndEx*)AfxGetMainWnd();
	CFrameWnd* pChild = pMainWndEx->MDIGetActive();
	CEngineView* pView = (CEngineView*)pChild->GetActiveView();
	auto activeWnd = pView->GetActiveWindow();
	auto pDoc = pView->GetDocument();

	Graphic3d_NameOfMaterial nameOfMaterial;

	//	TODO change to switch statement??
	if (cs == "Copper")
	{
		nameOfMaterial = Graphic3d_NameOfMaterial_Copper;

	}
	else {
		nameOfMaterial = Graphic3d_NameOfMaterial_Steel;
	}
	pDoc->SetTitle(L"Chamber Liner");
	pDoc->DrawLiner(theRadius, theThickness, theLength, 180, nameOfMaterial);

}

void DeLaval::OnCut()
{
	CMDIFrameWndEx* pMainWndEx = (CMDIFrameWndEx*)AfxGetMainWnd();
	CFrameWnd* pChild = pMainWndEx->MDIGetActive();
	CEngineView* pView = (CEngineView*)pChild->GetActiveView();
	auto activeWnd = pView->GetActiveWindow();
	auto pDoc = pView->GetDocument();
	
	pDoc->MakeCut();
	pDoc->SetTitle(L"Cut chamber");
	
}

void DeLaval::OnFuse()
{

	//	Gets the document window
	CMDIFrameWndEx* pMainWndEx = (CMDIFrameWndEx*)AfxGetMainWnd();
	CFrameWnd* pChild = pMainWndEx->MDIGetActive();
	CEngineView* pView = (CEngineView*)pChild->GetActiveView();
	auto activeWnd = pView->GetActiveWindow();
	auto pDoc = pView->GetDocument();

	pDoc->Fuse();
	pDoc->SetTitle(L"Fused liner");
}

void DeLaval::InitPropList()
{
	SetPropListFont();

	m_wndPropertyList.EnableHeaderCtrl(TRUE);
	m_wndPropertyList.EnableDescriptionArea(TRUE);
	m_wndPropertyList.SetVSDotNetLook();

	//	first group and subitems
	CMFCPropertyGridProperty* pDimensions = new CMFCPropertyGridProperty(_T("Dimensions"));

	CMFCPropertyGridProperty* pTheRadius = new CMFCPropertyGridProperty(_T("Radius"), (_variant_t)30l, _T("Chamber radius"));
	pTheRadius->EnableSpinControl(TRUE, 30, 150);
	pDimensions->AddSubItem(pTheRadius);

	CMFCPropertyGridProperty* pTheThickness = new CMFCPropertyGridProperty(_T("Wall thickness"), (_variant_t)5l, _T("ChamberWall thickness"));
	pTheThickness->EnableSpinControl(TRUE, 5, 70);
	pDimensions->AddSubItem(pTheThickness);

	CMFCPropertyGridProperty* pTheLength = new CMFCPropertyGridProperty(_T("Chamber length"), (_variant_t)50l, _T("Chamber length"));
	pTheLength->EnableSpinControl(TRUE, 50, 300);
	pDimensions->AddSubItem(pTheLength);

	CMFCPropertyGridProperty* pTheMaterial = new CMFCPropertyGridProperty(_T("Material"), _T("Select"), _T("Select Material"));
	pTheMaterial->AddOption(_T("Steel"));
	pTheMaterial->AddOption(_T("Copper"));
	pTheMaterial->AllowEdit(FALSE);
	pDimensions->AddSubItem(pTheMaterial);

	m_wndPropertyList.AddProperty(pDimensions);
	m_wndPropertyList.ExpandAll();

	//m_wndPropertyList.AddProperty(pSize);
	//m_wndPropertyList.ExpandAll();

	//int pcount = m_wndPropertyList.GetPropertyCount();	//	2
	//int rowheight = m_wndPropertyList.GetRowHeight();	//	19
	//auto m0 = m_wndPropertyList.GetProperty(0);	// Dimensions caption
	//auto m1 = m_wndPropertyList.GetProperty(1)->GetSubItem(1)->GetValue();	//	Window size, and subitem value
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
