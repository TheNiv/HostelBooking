#pragma once
#include <list>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "Guest.h"
#include "Visit.h"
#include "IVisitManagement.h"
using namespace std;
enum Year 
{
	ThisYear = 0 ,NextYear  // for better readability when using the occupation calender.
};
class Hostel : IVisitManagement
{
private:
    Date currentDate;
	list<Visit> m_currentVisits; // The current visits of people in the hotel details
	int m_currentGuests;  // Number of guests currently in the hostel
	float m_starReview; // The average review of the hostel
	const char* m_city; // The city that the hostel is in.
	int m_guestCapacity;  // The highest number of guests that can be in the hotel
	double m_pricePerNight;  // The price for 1 night in the hostel
	int m_occupationCalender[2][12][30];  // a calender that counts how many guests should be in each day of the current year.
	list<Visit> m_futureVisits;  // A list of the future visits that are booked.
public:
	Hostel(const char* city, int geustCap, double pricePerNight, int currentGuests = 0);
	Hostel();
	~Hostel();

	bool CanBook(Visit& visit)  // O(n)
	{ 
		if (visit.m_start.year != currentDate.year && visit.m_start.year != currentDate.year + 1)
			return false;
		if (visit.m_start.IsAfter(currentDate) && EnoughSpaceFor(visit)) 
		{
			return true;
		}
	}
	bool EnoughSpaceFor(Visit& visit) // O(n)
	{	
		//A function that returns true if there is enough space for the visit to occur in its dates 
		//and false otherwise.

		int temp_y = visit.m_start.year == currentDate.year ? ThisYear : NextYear;
		int temp_d = visit.m_start.day;
		int temp_m = visit.m_start.month;
		
		for (int i = 0; i < visit.m_days; i++)
		{
			if (m_occupationCalender[temp_y][temp_m][temp_d] + visit.m_guests > m_guestCapacity)
				return false;
		}
		return true;
	}
	void SetPricePerNight(double p) {
		m_pricePerNight = p;
	}
	void BookVisit(Visit& visit)  // O(n)
	{  
		// A function that books the visit in the coresponded dates.
		int temp_m = visit.m_start.month - 1;
		int temp_d = visit.m_start.day - 1;
		int temp_y = visit.m_start.year == currentDate.year ? ThisYear : NextYear;
		m_futureVisits.push_back(visit);
		for (int i = 0; i < visit.m_days; i++)
		{
			if (temp_d > 30) // the visit continues next month
			{
				temp_m++;
				temp_d = 1;
			}
			if (temp_m > 12) { // the visit continues next year
				temp_y++;
				temp_m = 1;
				temp_d = 1;
			}
			m_occupationCalender[temp_y][temp_m][temp_d] += visit.m_guests;
			temp_d++;		
		}
	}
	double GetVisitCost(Visit& v) const  //O(1)
	{   //A function that returns the calculates the cost of a visit of type(Visit)
		double amount = v.m_guests*((v.m_days-1)*m_pricePerNight); // the price is calculated by price per night so number of days -1 = number of nights
		return amount;
	}
	void PrintCalender(int month = 0,int year = ThisYear) {  // O(1)
		//A function that prints the data in the calender of a specific month and year or the whole occupation calender.

		if (month < 12 && month >0) 
		{
			for (int d = 0; d < 30; d++)
			{
				if(year)  //year = 0 or 1
					cout << d + 1 << "." << month << "." << currentDate.year + 1 << " : " << m_occupationCalender[NextYear][month-1][d] << endl;
				else
					cout << d + 1 << "." << month << "." << currentDate.year  << " : " << m_occupationCalender[ThisYear][month - 1][d] << endl;
			}
		}
		else // print the whole calender
		{
			for (int y = 0; y < 2; y++)
			{
				for (int m = 0; m < 12; m++)
				{
					for (int d = 0; d < 30; d++)
					{
						cout << d + 1 << "." << m + 1 << "." << currentDate.year + y << " : " << m_occupationCalender[y][m][d] << endl;
					}
				}
			}
		}
		
		
	}
	void UpdateCurrentDate() // O(1)
	{   // A function that updates the current dates and also the calender if the current year has passed.
		int current_y = currentDate.year;
		time_t now = time(0);
		tm ltm;
		localtime_s(&ltm, &now);
		currentDate = { ltm.tm_mday, ltm.tm_mon + 1, 1900+ltm.tm_year };
		if (currentDate.year > current_y)  // the current year has passed
		{
			ResetCalender();
		}
	}

	void ResetCalender() {  // O(1)
		//A function that moves next year's occupation calender to this year's and resets the the next year calender.
		for (int m = 0; m < 12; m++)
		{
			for (int d = 0; d < 30; d++)
			{
				m_occupationCalender[ThisYear][m][d] = m_occupationCalender[1][m][d];
				m_occupationCalender[NextYear][m][d] = 0;
			}
		}
	}
	

	void UpdateVisits()  // O(n)
	{   
		//A function that updates the current visits and the future visits according to the current local date

		list<Visit> ::iterator it;  // an iterator to iterate through the list.

		for (it = m_futureVisits.begin(); it != m_futureVisits.end(); it++) 
		{
			if (it->m_start.Equals(currentDate)) {
				m_currentVisits.push_back(*it);  // the iterator is a pointer to items in the list
				m_futureVisits.erase(it);   // removes the visit from the m_future_visit lists.
			}
		}

		for (it = m_currentVisits.begin(); it != m_currentVisits.end(); it++)
		{
			if (!it->m_end.IsAfter(currentDate)) {  //!IsAfter == true - the date is before the other date.
				m_currentVisits.erase(it);   // removes the visit from the m_currentVisits lists.
			}
		}
	}
	public: // get and set functions
		double GetPricePerNight() const
		{
			return m_pricePerNight;
		}
		int GetCurrentNumberOfGuests() const
		{
			return  m_currentGuests;
		}
		int GetCapacity() const
		{
			return m_guestCapacity;
		}
		void SetPricePerNight(double newPrice)
		{
			m_pricePerNight = newPrice;
		}
		void SetCapacity(int newCapacity) 
		{
			m_guestCapacity = newCapacity;
		}
};
