#pragma once
class C2dFillet
{
public:
	C2dFillet() noexcept;
	virtual ~C2dFillet();

	TopoDS_Shape MkFilletProfile();
};

