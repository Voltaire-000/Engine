
// EngineView.cpp : implementation of the CEngineView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Engine.h"
#endif

#include "EngineDoc.h"
#include "EngineView.h"

// CEngineView

IMPLEMENT_DYNCREATE(CEngineView, CView)

BEGIN_MESSAGE_MAP(CEngineView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEngineView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CEngineView construction/destruction

CEngineView::CEngineView() noexcept
{
	// TODO: add construction code here

}

CEngineView::~CEngineView()
{
}

BOOL CEngineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEngineView drawing

void CEngineView::OnDraw(CDC* /*pDC*/)
{
	CEngineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	myView->MustBeResized();
	myView->Update();
	pDoc->DrawSphere(10.0);
	myView->FitAll();
}


// CEngineView printing


void CEngineView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CEngineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEngineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEngineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CEngineView::OnInitialUpdate()
{
	myView = GetDocument()->GetViewer()->CreateView();
	myView->SetShadingModel(V3d_PHONG);
	myView->SetLightOn();
	myView->SetBgGradientColors(Quantity_NOC_GRAY10, Quantity_NOC_GRAY99, Aspect_GradientFillMethod_Vertical);
	Handle(Graphic3d_GraphicDriver) theGraphicDriver = ((CEngineApp*)AfxGetApp())->GetGraphicDriver();
	Aspect_Handle aWindowHandle = (Aspect_Handle)GetSafeHwnd();
	Handle(WNT_Window) aWntWindow = new WNT_Window(GetSafeHwnd());
	myView->SetWindow(aWntWindow);

	if (!aWntWindow->IsMapped())
	{
		aWntWindow->Map();
	}

	Standard_Integer w = 100;
	Standard_Integer h = 100;
	aWntWindow->Size(w, h);
	::PostMessage(GetSafeHwnd(), WM_SIZE, SIZE_RESTORED, w + h * 65536);
	myView->FitAll();
	myView->ZBufferTriedronSetup(Quantity_NOC_RED, Quantity_NOC_GREEN, Quantity_NOC_BLUE1, 0.8, 0.05, 12);
	myView->TriedronDisplay(Aspect_TOTP_LEFT_LOWER, Quantity_NOC_WHITE, 0.2, V3d_ZBUFFER);
}

void CEngineView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CEngineView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

void CEngineView::OnMouseMove(UINT nFlags, CPoint point)
{
	CView::OnMouseMove(nFlags, point);
	if (nFlags && MK_LBUTTON)
	{
		myView->Rotation(point.x, point.y);
		myView->StartRotation(point.x, point.y);
	}
}


// CEngineView diagnostics

#ifdef _DEBUG
void CEngineView::AssertValid() const
{
	CView::AssertValid();
}

void CEngineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEngineDoc* CEngineView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEngineDoc)));
	return (CEngineDoc*)m_pDocument;
}
#endif //_DEBUG


// CEngineView message handlers
