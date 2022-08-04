
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

//#include <ft2build.h>
//#include FT_FREETYPE_H

#include <propkey.h>

using namespace std;

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

	/// <summary>
	/// Initialize V3d_Viewer
	/// </summary>
	/// <returns>new V3d_Viewer</returns>
	m_viewer = new V3d_Viewer(graphicDriver);
	//=============================================================================

	/// <summary>
	/// Initialize AIS_InteractiveContext
	/// </summary>
	/// <returns>new AIS_InteractiveContext</returns>
	m_context = new AIS_InteractiveContext(m_viewer);
	//=============================================================================

	/// <summary>
	/// Set DefaultType of View -- V3d_PERSPECTIVE or V3d_ORTHOGRAPHIC
	/// </summary>
	/// <returns>void</returns>
	m_viewer->SetDefaultTypeOfView(V3d_PERSPECTIVE);
	//=============================================================================

	//=============================================================================
	//	Default Background
	Quantity_Color theColor1 = Quantity_NOC_LIGHTSLATEGRAY;
	Quantity_Color theColor2 = Quantity_NOC_LIGHTBLUE;
	Aspect_GradientFillMethod theFillStyle = Aspect_GradientFillMethod_Vertical;
	m_viewer->SetDefaultBgGradientColors(theColor1, theColor2, theFillStyle);
	//=============================================================================

	//=============================================================================
	//	Set up the GRID
	Aspect_GridType aGridType = Aspect_GT_Rectangular;
	Aspect_GridDrawMode aGridDrawMode = Aspect_GDM_Lines;
	m_viewer->SetRectangularGridValues(0, 0, 10, 10, 0);
	Handle(Graphic3d_AspectMarker3d) aMarker = new Graphic3d_AspectMarker3d(Aspect_TOM_BALL, Quantity_NOC_BLUE4, 2);
	m_viewer->SetGridEcho(aMarker);
	m_viewer->ActivateGrid(aGridType, aGridDrawMode);
	//=============================================================================

	//=============================================================================
	// ViewCube
	m_viewcube = new AIS_ViewCube();
	m_viewcube->SetTransformPersistence(new Graphic3d_TransformPers(Graphic3d_TMF_TriedronPers, Aspect_TOTP_RIGHT_UPPER, Graphic3d_Vec2i(100, 100)));
	Standard_Real theValue = 70;
	m_viewcube->SetSize(55);
	m_viewcube->SetFontHeight(12);
	m_viewcube->SetColor(Quantity_NOC_GRAY57);
	m_context->Display(m_viewcube, true);
	//=============================================================================

	//	Plane test trihedron size 50
	//=============================================================================
	//m_viewer->DisplayPrivilegedPlane(true, 50);

	///////////////////////////////////////////////
	//	Lighting
	//=============================================================================
	//	Directional light
	Handle(V3d_DirectionalLight) LightDir_1 = new V3d_DirectionalLight(V3d_XposYposZpos, Quantity_Color(Quantity_NOC_WHITE), 0);
	LightDir_1->SetDirection(10.0, 0.0, 100.0);
	LightDir_1->SetCastShadows(TRUE);
	LightDir_1->SetIntensity(15.0);
	m_viewer->AddLight(LightDir_1);
	m_viewer->SetLightOn(LightDir_1);
	//=============================================================================
	//	Directional light
	Handle(V3d_DirectionalLight) LightDir_2 = new V3d_DirectionalLight();
	LightDir_2->SetDirection(0.0, 100, -100.0);
	LightDir_2->SetCastShadows(TRUE);
	LightDir_2->SetIntensity(15.0);
	m_viewer->AddLight(LightDir_2);
	m_viewer->SetLightOn(LightDir_2);
	//=============================================================================
	//=============================================================================
	//	Positional light
	gp_Pnt thePos(0, 100, 0);
	Handle(V3d_PositionalLight)	LightPositional_1 = new V3d_PositionalLight(thePos);
	LightPositional_1->SetIntensity(1.0);
	//LightPositional_1->SetCastShadows(TRUE);	//	setting this will cause crash
	m_viewer->AddLight(LightPositional_1);
	m_viewer->SetLightOn(LightPositional_1);
	//=============================================================================
	//	Ambient light
	Handle(V3d_AmbientLight) LightAmb = new V3d_AmbientLight();
	LightAmb->SetIntensity(2.0);
	//LightAmb->SetCastShadows(TRUE);	// setting this will cause crash
	m_viewer->AddLight(LightAmb);
	m_viewer->SetLightOn(LightAmb);
	//=============================================================================
	// 	End Lighting
	/////////////////////////////////////////////

	//=============================================================================
	//	Shading Mode AIS_Shaded or AIS_WireFrame
	m_context->SetDisplayMode(AIS_Shaded, true);
	//m_context->SetDisplayMode(AIS_WireFrame, true);
	//=============================================================================

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

	//BRepPrimAPI_MakeCylinder cyl(30, 60);
	//cyl.Build();
	//TopoDS_Shape resultCyl = cyl.Shape();
	//Handle(AIS_Shape) cylShape = new AIS_Shape(resultCyl);
	//cylShape->SetMaterial(theMaterial);


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
	//m_context->Display(cylShape, true);


}

void CEngineDoc::DrawSampleProfile()
{
	auto mx = new CSampleProfile();
	//CSampleProfile::Mk2Profile(Rc, L_cyl, Lc, Le);
	TopoDS_Shape delavalShape = mx->Mk2Profile();

	Handle(AIS_Shape) shape = new AIS_Shape(delavalShape);
	AddAISshape(shape->Shape());
	m_context->Display(shape, true);
}

//void CEngineDoc::DrawFillet()
//{
//	auto liner = new C2dFillet();
//	TopoDS_Shape revolveShape = liner->MkFilletProfile();
//
//	Handle(AIS_Shape) shape = new AIS_Shape(revolveShape);
//	AddAISshape(shape->Shape());
//	m_context->Display(shape, true);
//}

void CEngineDoc::DrawCircle()
{
	gp_Pnt centerPoint_1(0, 0, 0);
	gp_Dir theDir_1(0, 1, 0);	// draws on the Y plane
	Standard_Real radius_1 = 100;
	gp_Circ circle_1(gp_Ax2(centerPoint_1, theDir_1), radius_1);
	BRepBuilderAPI_MakeEdge makeEdge_1(circle_1);
	Handle(AIS_Shape) shape_1 = new AIS_Shape(TopoDS_Edge());

	//TopoDS_Wire aWire = BRepBuilderAPI_MakeWire(makeEdge_1.Edge());
	//shape->SetShape(aWire);
	//TopoDS_Face aFace = BRepBuilderAPI_MakeFace(aWire);
	//shape->SetShape(aFace);

	gp_Pnt centerPoint_2(centerPoint_1.X() + 0, 0, 0);
	gp_Circ circle_2(gp_Ax2(centerPoint_2, theDir_1), 20);
	BRepBuilderAPI_MakeEdge makeEdge_2(circle_2);
	Handle(AIS_Shape) shape_2 = new AIS_Shape(TopoDS_Edge());

	// make points for lines
	gp_Pnt aVertLinePnt1(20, 0, 0);
	gp_Pnt aVertLinePnt2(20, 0, 40);

	gp_Pnt aHorzLinePnt1(0, 0, -20);
	gp_Pnt aHorzLinePnt2(-40, 0, -20);
	//	make segments
	// GC_MakeArcOfCircle
	//GC_MakeArcOfCircle mkArc()
	Handle(Geom_TrimmedCurve) aSegment1 = GC_MakeSegment(aVertLinePnt2, aVertLinePnt1);
	Handle(Geom_TrimmedCurve) aSegment2 = GC_MakeSegment(aHorzLinePnt1, aHorzLinePnt2);

	Handle(Geom_TrimmedCurve) arcSegment1 = GC_MakeSegment(aVertLinePnt1, aHorzLinePnt1);
	//	make edges
	TopoDS_Edge anEdge1 = BRepBuilderAPI_MakeEdge(aSegment1);
	TopoDS_Edge anEdge2 = BRepBuilderAPI_MakeEdge(aSegment2);

	TopoDS_Edge anArc1 = BRepBuilderAPI_MakeEdge(circle_2, aVertLinePnt1, aHorzLinePnt1);
	//	make wire
	//TopoDS_Wire aLineWire = BRepBuilderAPI_MakeWire(anEdge1, anEdge2);
	TopoDS_Wire arcWire1 = BRepBuilderAPI_MakeWire(anArc1);

	Handle(AIS_Shape) shape_lines = new AIS_Shape(TopoDS_Edge());

	//	Dimensions test
	//Handle(Prs3d_TextAspect) aTextAspect = new Prs3d_TextAspect();
	//aTextAspect->SetHeight(25);
	//aTextAspect->SetFont(Font_NOF_ASCII_MONO);
	//aTextAspect->SetColor(Quantity_NOC_CYAN);

	//AIS_TextLabel alabel;
	//Handle(Font_TextFormatter) tform = new Font_TextFormatter();
	//
	//TCollection_ExtendedString aString(L"Test");
	//alabel.SetTextFormatter(tform);
	//alabel.SetText(aString);
	//alabel.SetContext(m_context);
	//alabel.SetPosition(centerPoint_1);
	//alabel.SetDisplayType(Aspect_TODT_NORMAL);
	//alabel.SetFont(Font_NOF_ASCII_MONO);

	//Brep font
	Font_BRepFont aBRepFont("C:\\Windows\\Fonts\\cour.ttf", 20);
	aBRepFont.FTFont();
	Font_BRepTextBuilder aTextBuilder;
	TopoDS_Shape Text_Shape = aTextBuilder.Perform(aBRepFont, NCollection_String("my text"));

	Handle(AIS_Shape) ais_shape_text = new AIS_Shape(Text_Shape);
	// end brep test

	Handle(PrsDim_RadiusDimension) theCircle_1Radius = new PrsDim_RadiusDimension(circle_1);
	Handle(PrsDim_RadiusDimension) theShape_LinesRadius = new PrsDim_RadiusDimension(anArc1);
	//Handle(Prs3d_DimensionAspect) theDimensionAspect = new Prs3d_DimensionAspect();
	////theDimensionAspect->SetTextAspect(aTextAspect);
	//theDimensionAspect->MakeArrows3d(false);
	//theDimensionAspect->MakeUnitsDisplayed(true);

	//theDimensionAspect->MakeText3d(true);	//	this crashes with bounding box void TODO

	Standard_Real anArc1Radius = theShape_LinesRadius->GetValue(); //	returns 20 as expected

	//theShape_LinesRadius->SetDimensionAspect(theDimensionAspect);
	theShape_LinesRadius->SetTextPosition(aVertLinePnt1);
	theShape_LinesRadius->SetFlyout(50);
	//auto mx = theShape_LinesRadius->DimensionAspect();

	shape_1->SetShape(makeEdge_1.Edge());
	shape_2->SetShape(makeEdge_2.Edge());
	shape_lines->SetShape(arcWire1);

	//Prs3d_Text::Draw(aPresentation(), aTextAspect, aString, centerPoint_1);

	//m_context->Display(ais_shape_text, true);
	m_context->Display(shape_1, true);
	//m_context->Display(shape_2, true);
	m_context->Display(shape_lines, true);
	m_context->Display(theCircle_1Radius, true);
	m_context->Display(theShape_LinesRadius, true);



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
	shape->SetMaterial(Graphic3d_NameOfMaterial_Copper);

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
	//	sensitive to the order in which these are placed
	m_context->Activate(2, true);
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
	//auto shapeslist = ShapeList();

	for (TopoDS_Shape sh : m_shapes)
	{
		Handle(AIS_Shape) shape = new AIS_Shape(sh);
		m_context->Display(shape, true);
		m_context->SetDisplayMode(shape, AIS_Shaded, true);

	}
	//	this adds edges visibility
	AdjustSelectionStyle(m_context);
	m_context->Activate(2, true);

	//m_context->Display(m_viewcube, true);
}

void CEngineDoc::AddAISshape(AIS_Shape theShape)
{
	//	TODO
	//TopoDS_ListIteratorOfListOfShape aShapeIter

	m_AISshapes.push_back(theShape);

	m_context->Activate(2, true);

	//auto zmat = theShape.Material();

	for (AIS_Shape aisShape : m_AISshapes)
	{
		Handle(AIS_Shape) shape = new AIS_Shape(aisShape);
		m_context->Display(shape, true);
		m_context->SetDisplayMode(shape, AIS_Shaded, true);
	}

	//	TODO iter test
	m_viewer->ActiveLights();
	for (V3d_ListOfLightIterator aLightIter(m_viewer->ActiveLightIterator()); aLightIter.More(); aLightIter.Next())
	{
		Handle(V3d_Light) aCurrentLight = aLightIter.Value();
		bool toSkip = false;
		std::string aType = "UnKnown";
		unsigned int aImageTexture = 0;

		switch (aCurrentLight->Type())
		{
		case V3d_AMBIENT:
		{
			toSkip = true;
			break;
		}
		case V3d_DIRECTIONAL:
		{
			aType = ("Directional");
			//aImageTexture = 
			break;
		}
		case V3d_POSITIONAL:
		{
			aType = ("Positional");
			//aImageTexture = 
			break;
		}
		case V3d_SPOT:
		{
			toSkip = true;
			break;
		}
		default:
			break;
		}
		if (toSkip)
		{
			continue;
		}


	}


	//	this adds edges visibility
	AdjustSelectionStyle(m_context);
	m_context->Activate(2, true);
	//	viewcube needs to be redisplayed to get selection
	m_context->Display(m_viewcube, true);

}

std::vector<TopoDS_Shape> CEngineDoc::ShapeList()
{
	return m_shapes;
}

void CEngineDoc::AdjustSelectionStyle(const Handle(AIS_InteractiveContext)& m_context)
{
	//================================================================================
	//	Prs3d_Drawer
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

	selDrawer->UnFreeBoundaryAspect()->SetWidth(2.0);
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

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
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
		CMFCFilterChunkValueImpl* pChunk = nullptr;
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
