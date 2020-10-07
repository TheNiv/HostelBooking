#pragma once
#include <list>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "IVisitManagment.h"
#include "linkedList.h";
using namespace std;
enum Year
{
	ThisYear = 0, NextYear  // for better readability when using the occupation calender.
};
class Hostel : IVisitManagement
{
private:
	LinkedList<Visit> m_currentVisits; // A list of the current visits in the hotel details,sorted by the end date. Visit with closest end date is first.
	int m_currentGuests;  // Number of guests currently in the hostel
	float m_starReview; // The average review of the hostel
	const char* m_city; // The city that the hostel is in.
	int m_guestCapacity;  // The highest number of guests that can be in the hotel
	double m_pricePerNight;  // The price for 1 night in the hostel
	int m_occupationCalender[2][12][30];  // A calender that counts how many guests should be in each day of the current year.
	Date currentDate;  // The current date in the hotel city
	LinkedList<Visit> m_futureVisits;  // A list of the future visits ,sorted by the start date. Visit with closest start date is first.
public:
	Hostel(const char* city, int geustCap, double pricePerNight, int currentGuests = 0);
	Hostel();
	~Hostel();

	bool CanBook(Visit& visit);  // Returns true if it is possible to book the visit and false otherwise.
	
	bool EnoughSpaceFor(Visit& visit) const; //Returns true if there is enough space for the visit to occur in its dates, false otherwise.

	void BookVisit(Visit& visit);  //Books the visit in the occupation calender and in the future vists list.
	
	double GetVisitCost(Visit& v) const;  //Returns the calculates the cost of a visit of type(Visit)
	
	void PrintCalender(int month = 0, int year = ThisYear) const;  //Prints the data in the calender of a specific month and year or the whole occupation calender.
	void UpdateCurrentDate(); //Updates the current dates and also the calender if the current year has passed.
	void ResetCalender();  //Moves next year's occupation calender to this year's and resets the the next year calender.
	void StartVisit(Visit& visit);  //Inserts the visit to the currentVisits list.
	void PrintCurrentVisits();  //Prints the current visits.
	void PrintFutureVisits();  //Prints the future visits.

public: // get and set functions
	double GetPricePerNight() const;
	int GetCurrentNumberOfGuests() const;
	int GetCapacity() const;
	void SetPricePerNight(double newPrice);
	void SetCapacity(int newCapacity);
	
};
