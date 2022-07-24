#pragma once


class CuttingTool
{
public:
	void CylinderCutter(double radius, double height, const Graphic3d_MaterialAspect theMaterial);

	Graphic3d_MaterialAspect GetMaterial();

private:

	Graphic3d_MaterialAspect	m_NameOfMaterial;
};

