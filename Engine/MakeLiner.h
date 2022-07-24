#pragma once

#include <Standard_Macro.hxx>
#include <TopoDS_Shape.hxx>



//	the Combustion chamber liner
TopoDS_Shape MakeLiner(const Standard_Real theRadius,
	const Standard_Real theThickness,
	const Standard_Real theLength,
	const Standard_Real m_angleDegrees = 360);

