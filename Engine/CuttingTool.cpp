#include "pch.h"
#include "CuttingTool.h"

void CuttingTool::CylinderCutter(double radius, double height, const Graphic3d_MaterialAspect theMaterial)
{
	//TopoDS_MakCy
}

Graphic3d_MaterialAspect CuttingTool::GetMaterial()
{
	return m_NameOfMaterial;
}
