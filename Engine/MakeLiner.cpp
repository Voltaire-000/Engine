#include "pch.h"
#include "MakeLiner.h"

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

TopoDS_Shape MakeLiner(const Standard_Real theRadius, Standard_Real theThickness, Standard_Real theLength, Standard_Real m_angleDegrees)
{
	//	test points
	Standard_Real yOrigin = 0;
	Standard_Real zOrigin = 0;

	gp_Pnt aPnt1(theRadius, yOrigin, theLength);
	gp_Pnt aPnt2(theRadius + theThickness, yOrigin, theLength);
	gp_Pnt aPnt3(theRadius + theThickness, yOrigin, zOrigin);
	gp_Pnt aPnt4(theRadius, yOrigin, zOrigin);

	//	make segments from the points
	Handle(Geom_TrimmedCurve) aSegment1 = GC_MakeSegment(aPnt1, aPnt2);
	Handle(Geom_TrimmedCurve) asegment2 = GC_MakeSegment(aPnt2, aPnt3);
	Handle(Geom_TrimmedCurve) aSegment3 = GC_MakeSegment(aPnt3, aPnt4);
	Handle(Geom_TrimmedCurve) aSegment4 = GC_MakeSegment(aPnt4, aPnt1);

	//	profile: define the topology, make edges
	TopoDS_Edge anEdge1 = BRepBuilderAPI_MakeEdge(aSegment1);
	TopoDS_Edge anEdge2 = BRepBuilderAPI_MakeEdge(asegment2);
	TopoDS_Edge anEdge3 = BRepBuilderAPI_MakeEdge(aSegment3);
	TopoDS_Edge anEdge4 = BRepBuilderAPI_MakeEdge(aSegment4);
	//	make wire
	TopoDS_Wire aWire = BRepBuilderAPI_MakeWire(anEdge1, anEdge2, anEdge3, anEdge4);

	//	Y axis
	gp_Ax1 axis = gp::OZ();

	//	make face
	TopoDS_Face myFaceProfile = BRepBuilderAPI_MakeFace(aWire);

	//	start the revolve
	//m_percent = 2.0;
	Standard_Real m_convert = (m_angleDegrees * (M_PI/180))/M_PI;

	Standard_Real angle = m_convert*M_PI;
	TopoDS_Shape revolve1 = BRepPrimAPI_MakeRevol(myFaceProfile, axis, angle);
	
	
	//	TODO start at origin with points list

	return revolve1;
}
