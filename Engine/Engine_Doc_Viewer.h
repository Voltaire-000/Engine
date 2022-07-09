
// EngineDoc.h : interface of the CEngineDoc class
//

#pragma once


class CEngineDoc : public CDocument
{

public: // create from serialization only
	CEngineDoc() noexcept;
	virtual ~CEngineDoc();

	DECLARE_DYNCREATE(CEngineDoc)

public:
	const Handle(AIS_InteractiveContext)& GetAISContext() const
	{ 
		return m_context;
	}
	const Handle(AIS_InteractiveContext)& GetInteractiveContext()const
	{
		return m_context;
	}

public:
	Handle(V3d_Viewer) GetViewer()
	{
		return m_viewer;
	}

	//	events
public:
	virtual void OnSelectionChanged(const Handle(AIS_InteractiveContext)&,
		const Handle(V3d_View)&){}

// Attributes
protected:
	Handle(AIS_InteractiveContext)	m_context;
	Handle(V3d_Viewer)				m_viewer;

// Operations
public:
	void DrawSphere(double Radius);

	//////////////////////////////////////////////////
	CEngineDoc& operator<<(const TopoDS_Shape& shape)
	{
		this->AddShape(shape);
		return *this;
	}
	void AddShape(const TopoDS_Shape& shape);
	//////////////////////////////////////////////////

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

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
