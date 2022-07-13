
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

#include <Graphic3d_Camera.hxx>

// CEngineView

IMPLEMENT_DYNCREATE(CEngineView, CView)

BEGIN_MESSAGE_MAP(CEngineView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEngineView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()

	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CEngineView construction/destruction

CEngineView::CEngineView() noexcept
	:m_updateRequests(0),
	m_curZoom(0.0),
	m_currentMode(CurAction3d_Nothing)
{
	m_DefaultGestures = myMouseGestureMap;
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

void CEngineView::update3dView()
{
	if (!m_view.IsNull())
	{
		if (++m_updateRequests == 1)
		{
			Invalidate(FALSE);
			UpdateWindow();
		}
		FlushViewEvents(GetAISContext(), m_view, true);
	}
}

void CEngineView::redraw3dView()
{
	if (!m_view.IsNull())
	{
		FlushViewEvents(GetAISContext(), m_view, true);
	}
}

void CEngineView::handleViewRedraw(const Handle(AIS_InteractiveContext)& theCtx,
	const Handle(V3d_View)& theView)
{
	m_updateRequests = 0;
	AIS_ViewController::handleViewRedraw(theCtx, theView);
}

void CEngineView::OnSelectionChanged(const Handle(AIS_InteractiveContext)& theCtx,
	const Handle(V3d_View)& theView)
{
	AIS_ViewController::OnSelectionChanged(theCtx, theView);
	GetDocument()->OnSelectionChanged(theCtx, theView);
}

const Handle(AIS_InteractiveContext)& CEngineView::GetAISContext() const
{
	return ((CEngineDoc*)m_pDocument)->GetInteractiveContext();
}

void CEngineView::defineMouseGestures()
{
	myMouseGestureMap.Clear();
	AIS_MouseGesture aRot = AIS_MouseGesture_RotateOrbit;
	switch (m_currentMode)
	{

		case CurAction3d_Nothing:
		{
			myMouseGestureMap = m_DefaultGestures;
			break;
		}
		case CurAction3d_DynamicZooming:
		{
			myMouseGestureMap.Bind(Aspect_VKeyMouse_LeftButton, AIS_MouseGesture_Zoom);
			break;
		}
		case CurAction3d_GlobalPanning:
		{
			break;
		}
		case CurAction3d_WindowZooming:
		{
			myMouseGestureMap.Bind(Aspect_VKeyMouse_LeftButton, AIS_MouseGesture_ZoomWindow);
			break;
		}
		case CurAction3d_DynamicPanning:
		{
			myMouseGestureMap.Bind(Aspect_VKeyMouse_LeftButton, AIS_MouseGesture_Pan);
			break;
		}
		case CurAction3d_DynamicRotation:
		{
			myMouseGestureMap.Bind(Aspect_VKeyMouse_LeftButton, aRot);
			break;
		}

	}
}

void CEngineView::OnDraw(CDC* /*pDC*/)
{
	CEngineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	//TODO
	//pDoc->DrawSphere(50.0);
	//pDoc->DrawRevolve(180);
	// 
	//	TODO move this to a button
	//pDoc->DrawLiner(75, 10, 100, 180, Graphic3d_NameOfMaterial_Copper);

	m_view->MustBeResized();
	m_view->Update();


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
	//m_view = GetDocument()->GetViewer()->CreateView();
	m_view = GetAISContext()->CurrentViewer()->CreateView();
	m_view->SetImmediateUpdate(false);
	m_view->SetComputedMode(Standard_False);

	//m_view->SetShadingModel(V3d_PHONG);
	//m_view->SetShadingModel(V3d_GOURAUD);
	//m_view->SetShadingModel(V3d_FLAT);

	m_view->GeneratePBREnvironment(true);

	//=============================================================================
	//	Sky Dome
	BOOL skyDomeOn = false;
	if (skyDomeOn)
	{
		gp_Dir theSunDirection;
		gp_XYZ theXYZ(-300, 100, 0);
		theSunDirection.SetXYZ(theXYZ);
		Standard_ShortReal theCloudiness = 0.08;
		Standard_ShortReal theTime = 8;
		Standard_ShortReal theFogginess = 0.8;
		Standard_Integer theSize = 1800;
		const Aspect_SkydomeBackground theAspect = Aspect_SkydomeBackground(theSunDirection, theCloudiness, theTime, theFogginess, theSize);
		m_view->SetBackgroundSkydome(theAspect, true);
	}
	//============================================================================

	//	have to turn off background color to see skydome
	//m_view->SetBgGradientColors(Quantity_NOC_GRAY10, Quantity_NOC_GRAY99, Aspect_GradientFillMethod_Vertical);
	//Handle(Graphic3d_GraphicDriver) theGraphicDriver = ((CEngineApp*)AfxGetApp())->GetGraphicDriver();
	Handle(OpenGl_GraphicDriver) aDriver = Handle(OpenGl_GraphicDriver)::DownCast(m_view->Viewer()->Driver());
	m_view->Camera()->SetProjectionType(aDriver->Options().contextStereo 
										? Graphic3d_Camera::Projection_Stereo
										: Graphic3d_Camera::Projection_Orthographic);
	
	//Aspect_Handle aWindowHandle = (Aspect_Handle)GetSafeHwnd();
	Handle(WNT_Window) aWntWindow = new WNT_Window(GetSafeHwnd());
	m_view->SetWindow(aWntWindow);

	if (!aWntWindow->IsMapped())
	{
		aWntWindow->Map();
	}
	Standard_Integer w = 100;
	Standard_Integer h = 100;
	::PostMessage(GetSafeHwnd(), WM_SIZE, SIZE_RESTORED, w + static_cast<LPARAM>(h) * 65536);

	//	Configure rendering params
	Graphic3d_RenderingParams& RenderParams = m_view->ChangeRenderingParams();
	//RenderParams.Method = Graphic3d_RM_RAYTRACING;
	RenderParams.Method = Graphic3d_RM_RASTERIZATION;
	RenderParams.AdaptiveScreenSampling = false;
	RenderParams.CoherentPathTracingMode = false;
	RenderParams.IsGlobalIlluminationEnabled = false;
	RenderParams.NbRayTracingTiles = 1024;
	RenderParams.PbrEnvBakingSpecNbSamples = 256;
	RenderParams.PbrEnvSpecMapNbLevels = 6;
	RenderParams.RaytracingDepth = 6;
	RenderParams.RayTracingTileSize = 32;
	RenderParams.IsTransparentShadowEnabled = true;
	RenderParams.IsReflectionEnabled = true;
	RenderParams.IsAntialiasingEnabled = true;
	RenderParams.NbMsaaSamples = 8; // Anti-aliasing by multi-sampling
	RenderParams.IsShadowEnabled = true;
	RenderParams.CollectedStats = Graphic3d_RenderingParams::PerfCounters_Basic;

	m_view->Redraw();
	m_view->Invalidate();

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

void CEngineView::OnButtonFront()
{
	m_view->SetProj(V3d_Yneg);
	m_view->Redraw();
}

BOOL CEngineView::OnMouseWheel(UINT nFlags, short theDelta, CPoint point)
{
	const Standard_Real aDeltaF = Standard_Real(theDelta) / Standard_Real(WHEEL_DELTA);
	CPoint aCursorPnt = point;
	ScreenToClient(&aCursorPnt);
	const Graphic3d_Vec2i aPos(aCursorPnt.x, aCursorPnt.y);
	const Aspect_VKeyFlags aFlags = WNT_Window::MouseKeyFlagsFromEvent(nFlags);
	if (UpdateMouseScroll(Aspect_ScrollDelta(aPos, aDeltaF, aFlags)))
	{
		update3dView();
	}

	return true;
}

void CEngineView::OnMouseMove(UINT nFlags, CPoint point)
{
	//CView::OnMouseMove(nFlags, point);
	//if (nFlags && MK_LBUTTON)
	//{
	//	m_view->Rotation(point.x, point.y);
	//	m_view->StartRotation(point.x, point.y);
	//}
	TRACKMOUSEEVENT aMouseEvent;          // for WM_MOUSELEAVE
	aMouseEvent.cbSize = sizeof(aMouseEvent);
	aMouseEvent.dwFlags = TME_LEAVE;
	aMouseEvent.hwndTrack = m_hWnd;
	aMouseEvent.dwHoverTime = HOVER_DEFAULT;
	if (!::_TrackMouseEvent(&aMouseEvent)) { TRACE("Track ERROR!\n"); }

	const Aspect_VKeyFlags aFlags = WNT_Window::MouseKeyFlagsFromEvent(nFlags);
	if (UpdateMousePosition(Graphic3d_Vec2i(point.x, point.y), PressedMouseButtons(), aFlags, false))
	{
		update3dView();
	}
	
}

void CEngineView::OnLButtonDown(UINT nFlags, CPoint point)
{
	const Aspect_VKeyFlags aFlags = WNT_Window::MouseKeyFlagsFromEvent(nFlags);
	PressMouseButton(Graphic3d_Vec2i(point.x, point.y), Aspect_VKeyMouse_LeftButton, nFlags, false);
	update3dView();
}

void CEngineView::OnLButtonUp(UINT nFlags, CPoint point)
{
	const Aspect_VKeyFlags aFlags = WNT_Window::MouseKeyFlagsFromEvent(nFlags);
	ReleaseMouseButton(Graphic3d_Vec2i(point.x, point.y), Aspect_VKeyMouse_LeftButton, nFlags, false);
	if (m_currentMode == CurAction3d_GlobalPanning)
	{
		m_view->Place(point.x, point.y, m_curZoom);
		m_view->Invalidate();
	}
	if (m_currentMode != CurAction3d_Nothing)
	{
		setCurrentAction(CurAction3d_Nothing);
	}
	update3dView();
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

CEngineDoc* CEngineView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEngineDoc)));
	return (CEngineDoc*)m_pDocument;
}
#endif //_DEBUG


// CEngineView message handlers
