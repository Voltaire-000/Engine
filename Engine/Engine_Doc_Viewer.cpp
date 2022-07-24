
// EngineDoc.cpp : implementation of the CEngineDoc class
//

#include "pch.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Engine_App.h"
#endif

#include "Engine_Doc_Viewer.h"
#include "Engine_View.h"

#include <propkey.h>

// CEngineDoc
//	Creates the Viewer

IMPLEMENT_DYNCREATE(CEngineDoc, CDocument)

BEGIN_MESSAGE_MAP(CEngineDoc, CDocument)
	//ON_COMMAND(ID_PROFILE, &CEngineDoc::OnDrawLiner)

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
	//m_context->DefaultDrawer();

	//=============================================================================
	//	Projection type
	m_viewer->SetDefaultTypeOfView(V3d_PERSPECTIVE);

	//=============================================================================

	///////////////////////////////////////////////////////////////////////////////
	//	Default Background
	Quantity_Color theColor1 = Quantity_NOC_LIGHTSLATEGRAY;
	Quantity_Color theColor2 = Quantity_NOC_LIGHTBLUE;
	Aspect_GradientFillMethod theFillStyle = Aspect_GradientFillMethod_Vertical;

	m_viewer->SetDefaultBgGradientColors(theColor1, theColor2, theFillStyle);
	//=============================================================================
	///////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////
	//	GRID
	Aspect_GridType aGridType = Aspect_GT_Rectangular;
	Aspect_GridDrawMode aGridDrawMode = Aspect_GDM_Lines;
	m_viewer->SetRectangularGridValues(0, 0, 10, 10, 0);
	Handle(Graphic3d_AspectMarker3d) aMarker = new Graphic3d_AspectMarker3d(Aspect_TOM_BALL, Quantity_NOC_BLUE4, 2);
	m_viewer->SetGridEcho(aMarker);
	m_viewer->ActivateGrid(aGridType, aGridDrawMode);
	//	end GRID
	/////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////
	// ViewCube
	m_viewcube = new AIS_ViewCube();
	m_viewcube->SetTransformPersistence(new Graphic3d_TransformPers(Graphic3d_TMF_TriedronPers, Aspect_TOTP_RIGHT_UPPER, Graphic3d_Vec2i(100, 100)));
	Standard_Real theValue = 70;
	m_viewcube->SetSize(theValue);
	m_viewcube->SetColor(Quantity_NOC_SLATEGRAY4);

	m_context->Display(m_viewcube, true);
	//	End ViewCube
	///////////////////////////////////////////////
	
	///////////////////////////////////////////////////
	//	Plane test
	//=================================================
	m_viewer->DisplayPrivilegedPlane(true, 50);

	//=================================================

	///////////////////////////////////////////////
	//	Lighting
	//=========================================
	//	Directional light
	Handle(V3d_DirectionalLight) LightDir_1 = new V3d_DirectionalLight(V3d_XposYposZpos, Quantity_Color(Quantity_NOC_WHITE), 0);
	LightDir_1->SetDirection(10.0, 0.0, 100.0);
	LightDir_1->SetCastShadows(TRUE);
	LightDir_1->SetIntensity(15.0);
	m_viewer->AddLight(LightDir_1);
	m_viewer->SetLightOn(LightDir_1);
	//=========================================
	//	Directional light
	Handle(V3d_DirectionalLight) LightDir_2 = new V3d_DirectionalLight();
	LightDir_2->SetDirection(0.0, 100, -100.0);
	LightDir_2->SetCastShadows(TRUE);
	LightDir_2->SetIntensity(15.0);
	m_viewer->AddLight(LightDir_2);
	m_viewer->SetLightOn(LightDir_2);
	//=========================================
	//=========================================
	//	Positional light
	gp_Pnt thePos(0, 100, 0);
	Handle(V3d_PositionalLight)	LightPositional_1 = new V3d_PositionalLight(thePos);
	LightPositional_1->SetIntensity(1.0);
	m_viewer->AddLight(LightPositional_1);
	m_viewer->SetLightOn(LightPositional_1);
	//=========================================
	//	Ambient light
	Handle(V3d_AmbientLight) LightAmb = new V3d_AmbientLight();
	LightAmb->SetIntensity(2.0);
	m_viewer->AddLight(LightAmb);
	m_viewer->SetLightOn(LightAmb);
	//	end Lighting
	/////////////////////////////////////////////

	m_context->SetDisplayMode(AIS_Shaded, true);
	//m_context->SetDisplayMode(AIS_WireFrame, true);
	m_context->SetAutomaticHilight(Standard_True);

	/////////////////////////////////////////////
	// 
	//	Set selection modes
	//m_context->Activate(4, true);
	//m_context->Activate(2, true);
	m_context->Activate(m_viewcube);
	//
	/////////////////////////////////////////////
	
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

void CEngineDoc::DrawRevolve(Standard_Real theAngle)
{
	//theAngle = 180;
	TopoDS_Shape shape = MakeRevolve(theAngle);
	AddShape(shape);
	m_context->Display(new AIS_Shape(shape), true);
}

void CEngineDoc::DrawLiner(const Standard_Real theRadius, const Standard_Real theThickness, const Standard_Real theLength, const Standard_Real theAngle, const Graphic3d_MaterialAspect theMaterial)
{
	BOOL shapeAdded = false;
	//	TODO inherit from BRepBuilderAPI_MakeShape() ?? Probably not needed

		TopoDS_Shape liner = MakeLiner(theRadius, theThickness, theLength, theAngle);
		
		Handle(AIS_Shape) shape = new AIS_Shape(liner);

		auto matShape = shape->Material();
		
		if (!shapeAdded)
		{
			shape->SetMaterial(theMaterial);

			auto xmat = shape->Material();

			//	TODO should be adding an AIS_Shape here not a TopoDS_Shape
			
			//AddShape(liner);
			AddAISshape(shape->Shape());
			//AddShape(shape);

			//m_context->SetDisplayMode(AIS_Shaded, true);
			//m_context->SetAutomaticHilight(Standard_True);
			//m_context->Activate(4, true);
			//m_context->Activate(2, true);
			//m_context->Activate(shape);
			//shapeAdded = true;
		}
		m_context->Display(shape, true);


}

void CEngineDoc::MakeCut()
{
	BOOL shapeAdded = false;

	//TopoDS_Shape S1 = m_shapes.at(0);
	//TopoDS_Shape S2 = m_shapes.at(1);

	TopoDS_Shape S1 = m_AISshapes.at(0).Shape();
	TopoDS_Shape S2 = m_AISshapes.at(1).Shape();

	//Handle(AIS_Shape) S1shape = new AIS_Shape(S1);
	//auto S1Matname = S1shape->Material();

	auto S1MatName = m_AISshapes.at(1).Material();
	
	BRepAlgoAPI_Cut cut(S2, S1);
	cut.Build();
	TopoDS_Shape aResult = cut.Shape();
	
	Handle(AIS_Shape) shape = new AIS_Shape(aResult);

	//shape->SetMaterial(S1MatName);

	auto xmat = shape->Material();
	
	//auto matname = shape->Material();
	shape->SetMaterial(xmat);

	//if (!shapeAdded)
	//{
	//	AddShape(aResult);

	//	shapeAdded = true;
	//}
	
	//AddShape(aResult);
	AddAISshape(shape->Shape());

	//auto mShapeList = ShapeList();

	//m_context->Erase(, true);
	m_context->EraseAll(true);
	m_context->Display(shape, true);
	m_context->Display(m_viewcube, true);

}

void CEngineDoc::Fuse()
{
	BOPAlgo_Builder aBuilder;
	TopTools_ListOfShape aLSObjects = m_listOfShapes;
	aBuilder.SetArguments(aLSObjects);
	Standard_Boolean bRunParallel = Standard_True;
	aBuilder.SetRunParallel(bRunParallel);
	Standard_Real aFuzzyValue = 1.e-5;
	aBuilder.SetFuzzyValue(aFuzzyValue);
	Standard_Boolean bSafeMode = Standard_False;
	aBuilder.SetNonDestructive(bSafeMode);
	BOPAlgo_GlueEnum aGlue = BOPAlgo_GlueShift;
	aBuilder.SetGlue(aGlue);

	aBuilder.Perform();
	if (aBuilder.HasErrors())
	{
		return;
	}
	if (aBuilder.HasWarnings())
	{
		return;
	}

	const TopoDS_Shape& aResult = aBuilder.Shape();

	m_listOfShapes.Clear();

	AddShape(aResult);

	Handle(AIS_Shape) shape = new AIS_Shape(aResult);

	m_context->EraseAll(true);
	
	m_context->Display(shape, true);

	m_context->Display(m_viewcube, true);
}

//void CEngineDoc::OnDrawLiner()
//{
//
//	//	TODO pass in values from edit box
//	//	gets the document view
//	CMDIFrameWndEx* pMainWndEx = (CMDIFrameWndEx*)AfxGetMainWnd();
//	CFrameWnd* pChild = pMainWndEx->MDIGetActive();
//	CEngineView* pView = (CEngineView*)pChild->GetActiveView();
//	auto activeWnd = pView->GetActiveWindow();
//	auto pDoc = pView->GetDocument();
//
//	//	this works and changes doc name TODO
//	pDoc->SetTitle(L"Chamber Liner");
//	pDoc->DrawLiner(200, 10, 300, 180, Graphic3d_NameOfMaterial_Copper);
//	//DrawLiner(75, 10, 300, 180);
//}

void CEngineDoc::AddShape(const TopoDS_Shape& shape)
{
	m_shapes.push_back(shape);
	auto shapeslist = ShapeList();

	for (auto sh : m_shapes)
	{
		Handle(AIS_Shape) shape = new AIS_Shape(sh);
		m_context->Display(shape, true);
		m_context->SetDisplayMode(shape, AIS_Shaded, true);
		//AdjustSelectionStyle(m_context);
	}

	m_context->Activate(2, true);
	//m_context->Display(m_viewcube, true);
}

void CEngineDoc::AddAISshape(AIS_Shape theShape)
{
	m_AISshapes.push_back(theShape);

	auto zmat = theShape.Material();

	for (auto aisShape : m_AISshapes)
	{
		Handle(AIS_Shape) shape = new AIS_Shape(aisShape);
		m_context->Display(shape, true);
		m_context->SetDisplayMode(shape, AIS_Shaded, true);

	}
}

std::vector<TopoDS_Shape> CEngineDoc::ShapeList()
{
	return m_shapes;
}

void CEngineDoc::AdjustSelectionStyle(const Handle(AIS_InteractiveContext)& m_context)
{
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

	m_context->SetDefaultDrawer(selDrawer);
	//	end Prs3d
	///////////////////////////////////////////////////////////////////////////////
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

void CEngineDoc::OnProfile()
{
	auto frame = (CFrameWnd*)AfxGetApp()->m_pMainWnd;
	auto mactive = (CEngineDoc*)frame->GetActiveDocument();
	auto mc = mactive->CreateObject();

	TopoDS_Shape liner = MakeLiner(70, 10, 100, 180);
	Handle(AIS_Shape) shapeLiner = new AIS_Shape(liner);
	m_context->SetMaterial(shapeLiner, Graphic3d_NOM_PLASTIC, Standard_False);
	m_context->SetColor(shapeLiner, Quantity_NOC_GREEN, Standard_False);
	AddShape(liner);
	m_context->Display(shapeLiner, Standard_True);
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
