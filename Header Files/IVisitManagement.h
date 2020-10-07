#pragma once
#include "Visit.h"
class IVisitManagement
{
	virtual bool EnoughSpaceFor(Visit& visit) const = 0;
	virtual void BookVisit(Visit& visit) = 0;
	virtual bool CanBook(Visit& visit) = 0;
	virtual double GetVisitCost(Visit& visit) const = 0;

};
