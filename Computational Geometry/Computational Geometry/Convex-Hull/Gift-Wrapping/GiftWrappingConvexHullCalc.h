#pragma once
#include"../Shared/ConvexHullBase.h"

class GiftWrappingConvexHullCalc : public ConvexHullBase
{
public:
	GiftWrappingConvexHullCalc();
	~GiftWrappingConvexHullCalc();

public:
	virtual void CalculateConvexHullPoints() override;

};

extern GiftWrappingConvexHullCalc *GWC;