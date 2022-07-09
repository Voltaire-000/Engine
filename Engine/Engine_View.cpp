
// EngineView.cpp : implementation of the CEngineView class
//	Creates the View

#include "pch.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Engine_App.h"
#endif

#include "Engine_Doc_Viewer.h"
#include "Engine_View.h"

// CEngineView

IMPLEMENT_DYNCREATE(CEngineView, CView)

BEGIN_MESSAGE_MAP(CEngineView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEngineView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()

	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
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
	m_view->MustBeResized();
	m_view->Update();
	//TODO
	pDoc->DrawSphere(10.0);
	//myView->FitAll();
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
	m_view = GetDocument()->GetViewer()->CreateView();
	//myView->SetShadingModel(V3d_PHONG);
	//myView->SetLightOn();
	m_view->SetBgGradientColors(Quantity_NOC_GRAY10, Quantity_NOC_GRAY99, Aspect_GradientFillMethod_Vertical);
	Handle(Graphic3d_GraphicDriver) theGraphicDriver = ((CEngineApp*)AfxGetApp())->GetGraphicDriver();
	Aspect_Handle aWindowHandle = (Aspect_Handle)GetSafeHwnd();
	Handle(WNT_Window) aWntWindow = new WNT_Window(GetSafeHwnd());
	m_view->SetWindow(aWntWindow);

	if (!aWntWindow->IsMapped())
	{
		aWntWindow->Map();
	}

	Standard_Integer w = 100;
	Standard_Integer h = 100;
	aWntWindow->Size(w, h);
	::PostMessage(GetSafeHwnd(), WM_SIZE, SIZE_RESTORED, w + h * 65536);
	m_view->FitAll();
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
		m_view->Rotation(point.x, point.y);
		m_view->StartRotation(point.x, point.y);
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
