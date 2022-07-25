#pragma once

#include <Standard_Macro.hxx>
#include <TopoDS_Shape.hxx>

class CSampleProfile
{
public:
	CSampleProfile()noexcept;
	virtual ~CSampleProfile();

	TopoDS_Shape MkProfile(const Standard_Real Rc,
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
		const Standard_Real L_Star = 500);

};

