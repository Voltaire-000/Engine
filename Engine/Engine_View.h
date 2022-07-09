
// EngineView.h : interface of the CEngineView class
//

#pragma once
#include "framework.h"
#include <AIS_InteractiveContext.hxx>
#include <AIS_ViewController.hxx>

enum CurAction3d
{
	CurAction3d_Nothing,
	CurAction3d_DynamicZooming,
	CurAction3d_WindowZooming,
	CurAction3d_DynamicPanning,
	CurAction3d_GlobalPanning,
	CurAction3d_DynamicRotation
};

class Standard_EXPORT CEngineView : public CView, public AIS_ViewController
{
	DECLARE_DYNCREATE(CEngineView)
public: // create from serialization only
	CEngineView() noexcept;
	virtual ~CEngineView();

	CEngineDoc* GetDocument();

	//	request view redraw
	void update3dView();

	//	flush events and redraw view
	void redraw3dView();

	//	return the view
	const Handle(V3d_View)& GetView() const
	{
		return m_view;
	}

	void FitAll() { if (!m_view.IsNull()) m_view->FitAll();  m_view->ZFitAll(); };
	void Redraw() { if (!m_view.IsNull()) m_view->Redraw(); };

	void SetZoom(const Standard_Real& Coef) { m_view->SetZoom(Coef); };

protected:
	Handle(V3d_View)	m_view;
	AIS_MouseGestureMap	m_DefaultGestures;
	Graphic3d_Vec2i		m_clickPos;
	Standard_Real		m_curZoom;
	unsigned int		m_updateRequests;

	void defineMouseGestures();
	CurAction3d getCurrentAction()const { return m_currentMode; }
	//	set the current action
	void setCurrentAction(CurAction3d theAction)
	{
		m_currentMode = theAction;
		defineMouseGestures();
	}

private:
	CurAction3d			m_currentMode;
protected:
	//	handle view redraw
	virtual void handleViewRedraw(const Handle(AIS_InteractiveContext)& theCtx,
		const Handle(V3d_View)& theView) Standard_OVERRIDE;

	//	called by handleMoveTo() on Selection in 3D Viewer
	virtual void OnSelectionChanged(const Handle(AIS_InteractiveContext)& theCtx,
		const Handle(V3d_View)& theView) Standard_OVERRIDE;

	//	return the interactive context
	virtual const Handle(AIS_InteractiveContext)& GetAISContext() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	// Override


// Implementation

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	afx_msg void OnButtonFront();
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate() Standard_OVERRIDE;
	virtual void OnDraw(CDC* /*pDC*/) Standard_OVERRIDE;  // overridden to draw this view
	afx_msg BOOL OnMouseWheel(UINT nFlags, short theDelta, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//afx_msg void OnLButtonDown(UINT theFlags, CPoint thePoint);
	//afx_msg void OnLButtonUp(UINT theFlags, CPoint thePoint);
	//afx_msg void OnMButtonDown(UINT theFlags, CPoint thePoint);
	//afx_msg void OnMButtonUp(UINT theFlags, CPoint thePoint);
	//afx_msg void OnRButtonDown(UINT theFlags, CPoint thePoint);
	afx_msg void OnRButtonUp(UINT theFlags, CPoint thePoint);
};

#ifndef _DEBUG  // debug version in EngineView.cpp
inline CEngineDoc* CEngineView::GetDocument() const
   { return reinterpret_cast<CEngineDoc*>(m_pDocument); }
#endif

