#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#include <afxdisp.h>        // MFC Automation classes



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

//	opencascade headers

#include <AIS_InteractiveContext.hxx>
#include <AIS_InteractiveObject.hxx>
#include <AIS_Shape.hxx>
#include <AIS_Trihedron.hxx>
#include <AIS_ListOfInteractive.hxx>
#include <AIS_ListIteratorOfListOfInteractive.hxx>
#include <AIS_Point.hxx>
#include <AIS_ViewCube.hxx>
#include <AIS_ViewController.hxx>

#include <Aspect_Background.hxx>
#include <Aspect_TypeOfLine.hxx>
#include <Aspect_WidthOfLine.hxx>
#include <Aspect_Window.hxx>
#include <Aspect_SkydomeBackground.hxx>

#include <BRep_Builder.hxx>
#include <BRep_Tool.hxx>
#include <BRepBuilderAPI.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_BooleanOperation.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepTools.hxx>

#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepBuilderAPI_Copy.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepLib.hxx>
#include <BRepOffsetAPI_MakeThickSolid.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepFeat_SplitShape.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <BRepAdaptor_Curve.hxx>

#include <BOPAlgo_Operation.hxx>
#include <BOPAlgo_Algo.hxx>
#include <BOPAlgo_Builder.hxx>

#include <Prs3d_IsoAspect.hxx>
#include <Prs3d_LineAspect.hxx>
#include <Prs3d_Text.hxx>
#include <Prs3d_PointAspect.hxx>

#include <DsgPrs_LengthPresentation.hxx>
#include <GCPnts_TangentialDeflection.hxx>

#include <gp_Vec.hxx>
#include <Graphic3d_NameOfMaterial.hxx>
#include <OSD_Environment.hxx>
#include <Precision.hxx>

#include <Quantity_NameOfColor.hxx>
#include <Quantity_PhysicalQuantity.hxx>
#include <Quantity_TypeOfColor.hxx>

#include <SelectMgr_EntityOwner.hxx>
#include <SelectMgr_SelectableObject.hxx>
#include <SelectMgr_Selection.hxx>
#include <SelectMgr_SelectionManager.hxx>
#include <SelectMgr_ListOfFilter.hxx>
#include <SelectMgr_Filter.hxx>

#include <StdSelect_EdgeFilter.hxx>
#include <StdSelect_ShapeTypeFilter.hxx>

#include <Standard_Boolean.hxx>
#include <Standard_CString.hxx>
#include <Standard_ErrorHandler.hxx>
#include <Standard_Integer.hxx>
#include <Standard_IStream.hxx>
#include <Standard_Macro.hxx>
#include <Standard_NotImplemented.hxx>
#include <Standard_OStream.hxx>
#include <Standard_Real.hxx>
#include <Standard_DefineHandle.hxx> 

#include <StdPrs_Curve.hxx>
#include <StdPrs_Point.hxx>
#include <StdPrs_PoleCurve.hxx>

#include <TCollection_AsciiString.hxx>

#include <TColgp_Array1OfPnt2d.hxx>
#include <TColgp_HArray1OfPnt2d.hxx>
#include <TColStd_HSequenceOfTransient.hxx>
#include <TColStd_MapIteratorOfMapOfTransient.hxx>
#include <TColStd_MapOfTransient.hxx>
#include <TColgp_HArray1OfPnt.hxx>

#include <TopExp_Explorer.hxx>
#include <TopExp.hxx>

#include <TopTools_ListOfShape.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <TopTools_DataMapOfShapeInteger.hxx>
#include <TopTools_DataMapOfShapeReal.hxx>
#include <TopTools_IndexedDataMapOfShapeAddress.hxx>
#include <TopTools_HSequenceOfShape.hxx>

#include <UnitsAPI.hxx>

#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>

#include <WNT_Window.hxx>

#include <GC_MakeArcOfCircle.hxx>
#include <GC_MakeSegment.hxx>
#include <GC_MakeCircle.hxx>

#include <GCE2d_MakeSegment.hxx>

#include <gp.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>
#include <gp_Ax2d.hxx>
#include <gp_Dir.hxx>
#include <gp_Dir2d.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Trsf.hxx>
#include <gp_Vec.hxx>

#include <GeomAPI_Interpolate.hxx>

#include <Geom_CylindricalSurface.hxx>
#include <Geom_Plane.hxx>
#include <Geom_Surface.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Geom_Line.hxx>
#include <Geom_Axis2Placement.hxx>
#include <Geom_CartesianPoint.hxx>

#include <Geom2d_Ellipse.hxx>
#include <Geom2d_TrimmedCurve.hxx>

#include <GeomAbs_CurveType.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <GeomTools_Curve2dSet.hxx>

#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_Vertex.hxx>

#include <GCPnts_AbscissaPoint.hxx>

#include <GeomLib.hxx>
#include <GeomConvert_CompCurveToBSplineCurve.hxx>

#include <V3d_PositionalLight.hxx>
#include <V3d_DirectionalLight.hxx>
#include <V3d_AmbientLight.hxx>

#include <IGESControl_Controller.hxx>
#include <IGESControl_Writer.hxx>

#include <Interface_Static.hxx>

#include <OpenGl_GraphicDriver.hxx>
#include <Graphic3d_GraphicDriver.hxx>