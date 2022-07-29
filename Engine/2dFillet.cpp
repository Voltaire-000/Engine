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
	gp_Ax1 axis = gp::OX();

	//	make the segments
	Handle(Geom2d_TrimmedCurve) aSegment1 = GCE2d_MakeSegment(aPnt1, aPnt2);
	Handle(Geom2d_TrimmedCurve) aSegment2 = GCE2d_MakeSegment(aPnt2, aPnt3);
	Handle(Geom2d_TrimmedCurve) aSegment3 = GCE2d_MakeSegment(aPnt3, aPnt4);
	Handle(Geom2d_TrimmedCurve) aSegment4 = GCE2d_MakeSegment(aPnt4, aPnt1);

	//	make the edges
	TopoDS_Edge anEdge1 = BRepBuilderAPI_MakeEdge2d(aSegment1);
	auto mEdge1 = anEdge1.TShape();
	TopoDS_Edge anEdge2 = BRepBuilderAPI_MakeEdge2d(aSegment2);
	auto mEdge2 = anEdge2.TShape();
	TopoDS_Edge anEdge3 = BRepBuilderAPI_MakeEdge2d(aSegment3);
	auto mEdge3 = anEdge3.TShape();
	TopoDS_Edge anEdge4 = BRepBuilderAPI_MakeEdge2d(aSegment4);
	auto mEdge4 = anEdge4.TShape();
	//	make wire
	TopoDS_Wire aWire = BRepBuilderAPI_MakeWire(anEdge1, anEdge2, anEdge3, anEdge4);

	//	make face
	TopoDS_Face faceProfile = BRepBuilderAPI_MakeFace(aWire);

	//	start revolve
	Standard_Real m_convert = (180 * (M_PI / 180)) / M_PI;
	Standard_Real angle = m_convert * M_PI;
	TopoDS_Shape revolve = BRepPrimAPI_MakeRevol(faceProfile, axis, angle);

	BRepFilletAPI_MakeFillet mkFillet(revolve);
	TopExp_Explorer anEdgeExplorer(revolve, TopAbs_EDGE);

	//	Fillet the edge
	
	//while (anEdgeExplorer.More())
	//{
	//	TopoDS_Edge anEdge = TopoDS::Edge(anEdgeExplorer.Current());
	//	mkFillet.Add(20, anEdge);
	//	//anEdgeExplorer.Next();
	//}


	TopoDS_Edge anEdge_1 = TopoDS::Edge(anEdgeExplorer.Current());
	anEdgeExplorer.Next();
	TopoDS_Edge anEdge_2 = TopoDS::Edge(anEdgeExplorer.Current());
	anEdgeExplorer.Next();
	TopoDS_Edge anEdge_3 = TopoDS::Edge(anEdgeExplorer.Current());
	anEdgeExplorer.Next();
	TopoDS_Edge anEdge_4 = TopoDS::Edge(anEdgeExplorer.Current());	// same as edge1
	anEdgeExplorer.Next();
	TopoDS_Edge anEdge_5 = TopoDS::Edge(anEdgeExplorer.Current());
	anEdgeExplorer.Next();
	TopoDS_Edge anEdge_6 = TopoDS::Edge(anEdgeExplorer.Current());
	anEdgeExplorer.Next();
	TopoDS_Edge anEdge_7 = TopoDS::Edge(anEdgeExplorer.Current());

	mkFillet.Add(20, anEdge_1);
	mkFillet.Add(20, anEdge_6);
	mkFillet.Add(20, anEdge_5);

	revolve = mkFillet.Shape();
	return revolve;
}
