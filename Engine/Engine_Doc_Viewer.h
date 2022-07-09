
// EngineDoc.h : interface of the CEngineDoc class
//

#pragma once


class CEngineDoc : public CDocument
{

protected: // create from serialization only
	CEngineDoc() noexcept;
	DECLARE_DYNCREATE(CEngineDoc)

// Attributes
public:
	Handle(AIS_InteractiveContext)	m_context;
	Handle(V3d_Viewer)				m_viewer;

// Operations
public:
	Handle(V3d_Viewer) GetViewer()
	{
		return m_viewer;
	}
	void DrawSphere(double Radius);

	//////////////////////////////////////////////////
	CEngineDoc& operator<<(const TopoDS_Shape& shape)
	{
		this->AddShape(shape);
		return *this;
	}
	void AddShape(const TopoDS_Shape& shape);
	//////////////////////////////////////////////////
	void MessageLoop();

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CEngineDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

private:
	//	the shapes to visulize
	std::vector<TopoDS_Shape> m_shapes;

	//	opencascade things
private:
	Handle(AIS_ViewCube)		m_viewcube;

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
