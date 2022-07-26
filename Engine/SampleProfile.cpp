#include "pch.h"
#include "SampleProfile.h"

CSampleProfile::CSampleProfile() noexcept
{
}

CSampleProfile::~CSampleProfile()
{
}

TopoDS_Shape CSampleProfile::MkProfile(const Standard_Real Rc,
	const Standard_Real L_cyl,
	const Standard_Real b,
	const Standard_Real R2,
	const Standard_Real R1,
	const Standard_Real Rt,
	const Standard_Real Lc,
	const Standard_Real Rn,
	const Standard_Real Tn,
	const Standard_Real Te,
	const Standard_Real Re,
	const Standard_Real Le,
	const Standard_Real Wt,
	const Standard_Real L_Star)
{
	//	Origin
	Standard_Real xOrigin = 0;
	Standard_Real yOrigin = 0;
	Standard_Real zOrigin = 0;
	//	Z is up
	//	points for sketch
	gp_Pnt aPnt1(xOrigin, yOrigin, Lc + Le);
	gp_Pnt aPnt2(Rc, yOrigin, Lc + Le);
	gp_Pnt aPnt3(Rc, yOrigin, (Lc + Le) - L_cyl);	/*start of R2 radius*/

	//	begin radius 101.7

	gp_Pnt aPnt4(Rc - 20, yOrigin, aPnt3.Z() - 20);

	gp_Pnt aPnt5(xOrigin, yOrigin, aPnt3.Z() - 20);

	//GC_MakeArcOfCircle
	//	end points
	//	make segments from points
	Handle(Geom_TrimmedCurve) aSegment1 = GC_MakeSegment(aPnt1, aPnt2);
	Handle(Geom_TrimmedCurve) aSegment2 = GC_MakeSegment(aPnt2, aPnt3);
	Handle(Geom_TrimmedCurve) aSegment3 = GC_MakeSegment(aPnt3, aPnt4);
	Handle(Geom_TrimmedCurve) aSegment4 = GC_MakeSegment(aPnt4, aPnt5);

	//	profile: define the topology, make edges
	TopoDS_Edge anEdge1 = BRepBuilderAPI_MakeEdge(aSegment1);
	TopoDS_Edge anEdge2 = BRepBuilderAPI_MakeEdge(aSegment2);
	TopoDS_Edge anEdge3 = BRepBuilderAPI_MakeEdge(aSegment3);
	TopoDS_Edge anEdge4 = BRepBuilderAPI_MakeEdge(aSegment4);
	//	make wire
	TopoDS_Wire aWire = BRepBuilderAPI_MakeWire(anEdge1, anEdge2, anEdge3, anEdge4);

	//	Z axis revolve
	gp_Ax1 axis = gp::OZ();

	//	make face
	TopoDS_Face faceProfile = BRepBuilderAPI_MakeFace(aWire);

	//	start the revolve
	Standard_Real m_convert = (180 * (M_PI / 180)) / M_PI;
	Standard_Real angle = m_convert * M_PI;

	TopoDS_Shape revolve1 = BRepPrimAPI_MakeRevol(faceProfile, axis, angle);

	return TopoDS_Shape();
}

TopoDS_Shape CSampleProfile::Mk2Profile()
{
	Standard_Real Rc = 328.32/2;
	Standard_Real L_cyl = 369.04;
	Standard_Real Lc = 528.99;
	Standard_Real Le = 1322.07;
	//	Origin
	Standard_Real xOrigin = 0;
	Standard_Real yOrigin = 0;
	Standard_Real zOrigin = 0;
	//	Z is up
	//	points for sketch
	gp_Pnt aPnt1(xOrigin, yOrigin, Lc + Le);
	gp_Pnt aPnt2(Rc, yOrigin, Lc + Le);
	gp_Pnt aPnt3(Rc, yOrigin, (Lc + Le) - L_cyl);	/*start of R2 radius*/

	//	TODO working profile need to work on Fillet radius
	//	HACK
	//	Alert

	//	begin radius 101.7

	gp_Pnt aPnt4(Rc - 20, yOrigin, aPnt3.Z() - 20);
	gp_Pnt aPnt5(xOrigin, yOrigin, aPnt3.Z() - 20);

	//GC_MakeArcOfCircle
	//	end points
	//	make segments from points
	Handle(Geom_TrimmedCurve) aSegment1 = GC_MakeSegment(aPnt1, aPnt2);
	Handle(Geom_TrimmedCurve) aSegment2 = GC_MakeSegment(aPnt2, aPnt3);
	Handle(Geom_TrimmedCurve) aSegment3 = GC_MakeSegment(aPnt3, aPnt4);
	Handle(Geom_TrimmedCurve) aSegment4 = GC_MakeSegment(aPnt4, aPnt5);
	Handle(Geom_TrimmedCurve) aSegment5 = GC_MakeSegment(aPnt5, aPnt1);

	//	profile: define the topology, make edges
	TopoDS_Edge anEdge1 = BRepBuilderAPI_MakeEdge(aSegment1);
	TopoDS_Edge anEdge2 = BRepBuilderAPI_MakeEdge(aSegment2);
	TopoDS_Edge anEdge3 = BRepBuilderAPI_MakeEdge(aSegment3);
	TopoDS_Edge anEdge4 = BRepBuilderAPI_MakeEdge(aSegment4);

	TopoDS_Edge anEdge5 = BRepBuilderAPI_MakeEdge(aSegment5);
	//	make wire
	TopoDS_Wire aWire = BRepBuilderAPI_MakeWire(anEdge1, anEdge2, anEdge3, anEdge4);
	TopoDS_Wire lastWire = BRepBuilderAPI_MakeWire(anEdge4, anEdge5);

	//	Z axis revolve
	gp_Ax1 axis = gp::OZ();

	//	make face
	TopoDS_Face faceProfile = BRepBuilderAPI_MakeFace(aWire);

	TopoDS_Face zFace = BRepBuilderAPI_MakeFace(faceProfile, lastWire);

	//	start the revolve
	Standard_Real m_convert = (180 * (M_PI / 180)) / M_PI;
	Standard_Real angle = m_convert * M_PI;

	//TopoDS_Shape revolve1 = BRepPrimAPI_MakeRevol(faceProfile, axis, angle);
	TopoDS_Shape revolve1 = BRepPrimAPI_MakeRevol(zFace, axis, angle);

	return revolve1;
}
