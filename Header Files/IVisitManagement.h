#pragma once
class IVisitManagement
{
	virtual bool EnoughSpaceFor(Visit visit) = 0;
	virtual void BookVisit(Visit visit) = 0;
	virtual void UpdateVisits() = 0;
	virtual bool CanBook(Visit visit) = 0;
	virtual double GetVisitCost(Visit visit) = 0;

};