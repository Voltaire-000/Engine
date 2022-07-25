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
	gp_Pnt aPnt1(xOrigin, yOrigin, Lc + Le);
	gp_Pnt aPnt2(Rc, yOrigin, Lc + Le);
	gp_Pnt aPnt3(Rc, yOrigin, (Lc + Le) - L_cyl);	/*start of R2 radius*/
	// begin contraction radius at aPnt2
	// end radius at aPnt4
	gp_Pnt aPnt4(Rc - (101.7), yOrigin, (Lc + Le) - L_cyl - (Rc - (101.7)));	/*end of R2 radius*/

	//gp_Pnt aPntR1Start()
	//gp_Pnt aPntR1Center()
	//gp_Pnt aPntR1End()

	return TopoDS_Shape();
}
