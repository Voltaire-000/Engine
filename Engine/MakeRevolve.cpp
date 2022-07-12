#include "pch.h"
#include "MakeRevolve.h"

//#include <BRep_Tool.hxx>
//
//#include <GC_MakeSegment.hxx>
//
//#include <gp.hxx>
//#include <gp_Pnt.hxx>
//#include <gp_Ax1.hxx>
//#include <gp_Ax2.hxx>
//
//#include <TopoDS.hxx>
//#include <TopoDS_Face.hxx>
//#include <TopoDS_Wire.hxx>
//#include <TopoDS_Edge.hxx>
//#include <TopoDS_Shape.hxx>
//
//#include <BRepBuilderAPI_MakeFace.hxx>
//#include <BRepBuilderAPI_MakeWire.hxx>
//#include <BRepBuilderAPI_MakeEdge.hxx>
//#include <BRepPrimAPI_MakeRevol.hxx>
//#include <BRepSweep_Revol.hxx>
//#include <BRepLib.hxx>

TopoDS_Shape MakeRevolve(const Standard_Real theAngle)
{
	//	profile: define the support points
	//	inner revolve points
	gp_Pnt aPnt1(0.5, 0.0, 3.0);
	gp_Pnt aPnt2(1.0, 0.0, 3.0);
	gp_Pnt aPnt3(1.0, 0.0, 0.0);
	gp_Pnt aPnt4(0.5, 0.0, 0.0);

	//	make segments from points
	Handle(Geom_TrimmedCurve) aSegment1 = GC_MakeSegment(aPnt1, aPnt2);
	Handle(Geom_TrimmedCurve) asegment2 = GC_MakeSegment(aPnt2, aPnt3);
	Handle(Geom_TrimmedCurve) aSegment3 = GC_MakeSegment(aPnt3, aPnt4);
	Handle(Geom_TrimmedCurve) aSegment4 = GC_MakeSegment(aPnt4, aPnt1);

	// profile: define the topology , make edges
	TopoDS_Edge anEdge1 = BRepBuilderAPI_MakeEdge(aSegment1);
	TopoDS_Edge anEdge2 = BRepBuilderAPI_MakeEdge(asegment2);
	TopoDS_Edge anEdge3 = BRepBuilderAPI_MakeEdge(aSegment3);
	TopoDS_Edge anEdge4 = BRepBuilderAPI_MakeEdge(aSegment4);
	// make the wire
	TopoDS_Wire aWire = BRepBuilderAPI_MakeWire(anEdge1, anEdge2, anEdge3, anEdge4);

	// Y axis
	gp_Ax1 axis = gp::OZ();

	//	make the face
	TopoDS_Face myFaceProfile = BRepBuilderAPI_MakeFace(aWire);

	//	start the revolve
	Standard_Real angle = 1.0*M_PI;
	TopoDS_Shape revolve1 = BRepPrimAPI_MakeRevol(myFaceProfile, axis, angle);

	return revolve1;
}
