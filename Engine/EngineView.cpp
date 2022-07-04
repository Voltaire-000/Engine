
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
