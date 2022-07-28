#include "pch.h"
#include "2dFillet.h"

C2dFillet::C2dFillet() noexcept
{
}

C2dFillet::~C2dFillet()
{
}

TopoDS_Shape C2dFillet::MkFilletProfile()
{
	Standard_Real xOrigin = 0;
	Standard_Real yOrigin = 0;

	//	4 points of square
	gp_Pnt2d aPnt1(xOrigin, yOrigin);
	gp_Pnt2d aPnt2(xOrigin + 100, yOrigin);
	gp_Pnt2d aPnt3(aPnt2.X(), yOrigin + 100);
	gp_Pnt2d aPnt4(xOrigin, aPnt3.Y());

	//gp_Ax2d axis = gp::OY2d();
	gp_Ax1 axis = gp::OY();

	//	make the segments
	Handle(Geom2d_TrimmedCurve) aSegment1 = GCE2d_MakeSegment(aPnt1, aPnt2);
	Handle(Geom2d_TrimmedCurve) aSegment2 = GCE2d_MakeSegment(aPnt2, aPnt3);
	Handle(Geom2d_TrimmedCurve) aSegment3 = GCE2d_MakeSegment(aPnt3, aPnt4);
	Handle(Geom2d_TrimmedCurve) aSegment4 = GCE2d_MakeSegment(aPnt4, aPnt1);

	//	make the edges
	TopoDS_Edge anEdge1 = BRepBuilderAPI_MakeEdge2d(aSegment1);
	TopoDS_Edge anEdge2 = BRepBuilderAPI_MakeEdge2d(aSegment2);
	TopoDS_Edge anEdge3 = BRepBuilderAPI_MakeEdge2d(aSegment3);
	TopoDS_Edge anEdge4 = BRepBuilderAPI_MakeEdge2d(aSegment4);

	//	make wire
	TopoDS_Wire aWire = BRepBuilderAPI_MakeWire(anEdge1, anEdge2, anEdge3, anEdge4);

	//	make face
	TopoDS_Face faceProfile = BRepBuilderAPI_MakeFace(aWire);

	//	start revolve
	Standard_Real m_convert = (180 * (M_PI / 180)) / M_PI;
	Standard_Real angle = m_convert * M_PI;
	TopoDS_Shape revolve = BRepPrimAPI_MakeRevol(faceProfile, axis, angle);

	return revolve;
}
