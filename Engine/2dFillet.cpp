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

	gp_Ax2d axis = gp::OY2d();

	//	make the segments
	Handle(Geom2d_TrimmedCurve) aSegment1 = GCE2d_MakeSegment(aPnt1, aPnt2);
	Handle(Geom2d_TrimmedCurve) aSegment1 = GCE2d_MakeSegment(aPnt2, aPnt3);
	Handle(Geom2d_TrimmedCurve) aSegment1 = GCE2d_MakeSegment(aPnt3, aPnt4);
	Handle(Geom2d_TrimmedCurve) aSegment1 = GCE2d_MakeSegment(aPnt4, aPnt4);

	//	make the edges
	TopoDS_Edge anEdge1 = BRepBuilderAPI_MakeEdge(aSegment1);


	return TopoDS_Shape();
}
