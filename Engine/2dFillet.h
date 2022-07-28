#pragma once
#include <Standard_Macro.hxx>
#include <TopoDS_Shape.hxx>


class C2dFillet
{
public:
	C2dFillet() noexcept;
	virtual ~C2dFillet();

	TopoDS_Shape MkFilletProfile();
};

