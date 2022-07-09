
// EngineDoc.cpp : implementation of the CEngineDoc class
//

#include "pch.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Engine_App.h"
#endif

#include "Engine_Doc_Viewer.h"

#include <propkey.h>

// CEngineDoc
//	Creates the Viewer

IMPLEMENT_DYNCREATE(CEngineDoc, CDocument)

BEGIN_MESSAGE_MAP(CEngineDoc, CDocument)
END_MESSAGE_MAP()


// CEngineDoc construction/destruction

CEngineDoc::CEngineDoc() noexcept
{
	static Handle(Aspect_DisplayConnection) displayConnection;
	if (displayConnection.IsNull())
			displayConnection = new Aspect_DisplayConnection();
	Handle(OpenGl_GraphicDriver) graphicDriver = new OpenGl_GraphicDriver(displayConnection, false);

	//	Initialize V3d_Viewer
	m_viewer = new V3d_Viewer(graphicDriver);

	//	create a new window over the existing window
	m_context = new AIS_InteractiveContext(m_viewer);

	////////////////////////////////////////////////////////////////////////////
	//	Prs3d_Drawer test TODO
	Handle(Prs3d_Drawer) selDrawer = new Prs3d_Drawer();
	//
	selDrawer->SetLink(m_context->DefaultDrawer());
	selDrawer->SetFaceBoundaryDraw(true);
	selDrawer->SetDisplayMode(1);	//	Shaded
	selDrawer->SetTransparency(0.5f);
	selDrawer->SetZLayer(Graphic3d_ZLayerId_Topmost);
	selDrawer->SetColor(Quantity_NOC_GOLD);
	selDrawer->SetBasicFillAreaAspect(new Graphic3d_AspectFillArea3d());

	//	Adjust fill area aspect
	const Handle(Graphic3d_AspectFillArea3d)& fillArea = selDrawer->BasicFillAreaAspect();
	//
	fillArea->SetInteriorColor(Quantity_NOC_GOLD);
	fillArea->SetBackInteriorColor(Quantity_NOC_GOLD);
	//
	fillArea->ChangeFrontMaterial().SetMaterialName(Graphic3d_NOM_NEON_GNC);
	fillArea->ChangeFrontMaterial().SetTransparency(0.4f);
	fillArea->ChangeBackMaterial().SetMaterialName(Graphic3d_NOM_NEON_GNC);
	fillArea->ChangeBackMaterial().SetTransparency(0.4f);

	selDrawer->UnFreeBoundaryAspect()->SetWidth(1.0);
	//	Update AIS context
	m_context->SetHighlightStyle(Prs3d_TypeOfHighlight_LocalSelected, selDrawer);
	//	end Prs3d
	///////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////
	//	set up grid
	Aspect_GridType aGridType = Aspect_GT_Rectangular;
	Aspect_GridDrawMode aGridDrawMode = Aspect_GDM_Lines;
	m_viewer->SetRectangularGridValues(0, 0, 10, 10, 0);
	Handle(Graphic3d_AspectMarker3d) aMarker = new Graphic3d_AspectMarker3d(Aspect_TOM_BALL, Quantity_NOC_BLUE4, 2);
	m_viewer->SetGridEcho(aMarker);
	m_viewer->ActivateGrid(aGridType, aGridDrawMode);
	//	end grid
	/////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////
	// ViewCube
	m_viewcube = new AIS_ViewCube();
	m_viewcube->SetTransformPersistence(new Graphic3d_TransformPers(Graphic3d_TMF_TriedronPers, Aspect_TOTP_RIGHT_UPPER, Graphic3d_Vec2i(100, 100)));
	Standard_Real theValue = 40;
	m_viewcube->SetSize(theValue);
	m_viewcube->SetBoxColor(Quantity_NOC_GRAY1);
	m_viewcube->SetBoxTransparency(0.25);
	m_viewcube->SetDrawAxes(TRUE);
	m_context->Display(m_viewcube, true);
	//	End ViewCube
	///////////////////////////////////////////////
	
	//	Lighting
	Handle(V3d_DirectionalLight)	LightDir = new V3d_DirectionalLight(V3d_Zneg, Quantity_Color(Quantity_NOC_GRAY97), 1);
	Handle(V3d_AmbientLight)		LightAmb = new V3d_AmbientLight();
	LightDir->SetDirection(1.0, -20.0, -10.0);
	LightDir->SetIntensity(0.15);
	LightAmb->SetIntensity(0.15);
	m_viewer->AddLight(LightDir);
	m_viewer->AddLight(LightAmb);
	m_viewer->SetLightOn(LightDir);
	m_viewer->SetLightOn(LightAmb);
	//	Lighting end
	/////////////////////////////////////////////

	m_context->SetDisplayMode(AIS_Shaded, true);
	m_context->SetAutomaticHilight(Standard_False);
	
}

CEngineDoc::~CEngineDoc()
{
}

void CEngineDoc::InputEvent(const Standard_Integer theMouseX,
	const Standard_Integer theMouseY,
	const Standard_Integer theState,
	const Handle(V3d_View)& theView)
{
	m_context->MoveTo(theMouseX, theMouseY, theView, Standard_False);
	m_context->SelectDetected();
	m_context->UpdateCurrentViewer();
}

void CEngineDoc::DrawSphere(double Radius)
{
	//	TODO add shape to m_shapes vector ??

	BRepPrimAPI_MakeSphere mkSphere(Radius);
	mkSphere.Build();
	TopoDS_Shape Sphere = mkSphere.Shape();
	Handle(AIS_Shape) shape = new AIS_Shape(Sphere);
	shape->SetMaterial(Graphic3d_NameOfMaterial_Copper);

	AddShape(Sphere);

	m_context->Display(shape, true);
	//myAISContext->Display(new AIS_Shape(Sphere), true);

}

void CEngineDoc::AddShape(const TopoDS_Shape& shape)
{
	m_shapes.push_back(shape);
}

BOOL CEngineDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

// CEngineDoc serialization

void CEngineDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CEngineDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CEngineDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CEngineDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CEngineDoc diagnostics

#ifdef _DEBUG
void CEngineDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEngineDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

// CEngineDoc commands
