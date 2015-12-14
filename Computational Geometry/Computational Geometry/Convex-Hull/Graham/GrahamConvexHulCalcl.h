#pragma once
#include"../Shared/ConvexHullBase.h"


class GrahamConvexHulCalcl : public ConvexHullBase
{
public:
	GrahamConvexHulCalcl();
	~GrahamConvexHulCalcl();

public:
	virtual void CalculateConvexHullPoints() override;

};

extern GrahamConvexHulCalcl *GCH;