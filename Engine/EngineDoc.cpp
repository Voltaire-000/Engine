
// EngineDoc.cpp : implementation of the CEngineDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Engine.h"
#endif

#include "EngineDoc.h"

#include <propkey.h>

// CEngineDoc

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
	myViewer = new V3d_Viewer(graphicDriver);
	//	create a new window over the existing window
	myAISContext = new AIS_InteractiveContext(myViewer);


	///////////////////////////////////////////////
	//	Lighting
	Handle(V3d_DirectionalLight)	LightDir = new V3d_DirectionalLight(V3d_Zneg, Quantity_Color(Quantity_NOC_GRAY97), 1);
	Handle(V3d_AmbientLight)		LightAmb = new V3d_AmbientLight();
	LightDir->SetDirection(1.0, -2.0, -10.0);
	myViewer->AddLight(LightDir);
	myViewer->AddLight(LightAmb);
	myViewer->SetLightOn(LightDir);
	myViewer->SetLightOn(LightAmb);
	//	Lighting end
	/////////////////////////////////////////////
	myAISContext->SetDisplayMode(AIS_Shaded, true);
	myAISContext->SetAutomaticHilight(Standard_False);

}

CEngineDoc::~CEngineDoc()
{
}

void CEngineDoc::DrawSphere(double Radius)
{
	BRepPrimAPI_MakeSphere mkSphere(Radius);
	mkSphere.Build();
	TopoDS_Shape Sphere = mkSphere.Shape();
	
	myAISContext->Display(new AIS_Shape(Sphere), true);
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
