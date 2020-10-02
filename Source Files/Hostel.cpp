
#include "Hostel.h"
#include <ctime>
Hostel::Hostel(const char* city, int geustCap, double pricePerNight, int currentGuests ) : m_city(city), m_guestCapacity(geustCap),
																m_pricePerNight(pricePerNight), m_currentGuests(currentGuests)
{
	UpdateCurrentDate();
	for (int y = 0; y < 2; y++)
	{
		for (int m = 0; m < 12; m++)
		{
			for (int d = 0; d < 30; d++)
			{
				Hostel::m_occupationCalender[y][m][d] = 0;
			}
		}
	}

}

Hostel::Hostel() : m_city(""), m_guestCapacity(0), m_pricePerNight(0), m_currentGuests(0),currentDate(Date())
{
	for (int y = 0; y < 2; y++)
	{
		for (int m = 0; m < 12; m++)
		{
			for (int d = 0; d < 30; d++)
			{
				Hostel::m_occupationCalender[y][m][d] = 0;
			}
		}
	}

}

Hostel::~Hostel()
{

}


bool Hostel:: CanBook(Visit& visit)  // O(n)
{
	if (visit.m_start.m_year != currentDate.m_year && visit.m_start.m_year != currentDate.m_year + 1)
		return false;
	if (visit.m_start > currentDate && EnoughSpaceFor(visit))
	{
		return true;
	}
	return false;
}

bool Hostel::EnoughSpaceFor(Visit& visit) // O(n)
{
	//Returns true if there is enough space for the visit to occur in its dates 
	//and false otherwise.

	int temp_y = visit.m_start.m_year == currentDate.m_year ? ThisYear : NextYear;
	int temp_d = visit.m_start.m_day;
	int temp_m = visit.m_start.m_month;

	for (int i = 0; i < visit.m_days; i++)
	{
		if (m_occupationCalender[temp_y][temp_m][temp_d] + visit.m_guests > m_guestCapacity)
			return false;
	}
	return true;
}

void Hostel::BookVisit(Visit& visit)  // O(n)
{
	//Books the visit in the coresponded dates.
	int temp_m = visit.m_start.m_month - 1;
	int temp_d = visit.m_start.m_day - 1;
	int temp_y = visit.m_start.m_year == currentDate.m_year ? ThisYear : NextYear;
	m_futureVisits.push_back(visit);
	for (int i = 0; i <= visit.m_days; i++)
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

double Hostel:: GetVisitCost(Visit& v) const  //O(1)
{   //Returns the calculates the cost of a visit of type(Visit)
	double amount = v.m_guests*((v.m_days - 1)*m_pricePerNight); // the price is calculated by price per night so number of days -1 = number of nights
	return amount;
}

void Hostel:: PrintCalender(int month , int year) // O(1)
{
	//Prints the data in the calender of a specific month and year or the whole occupation calender.

	if (month < 12 && month >0)
	{
		for (int d = 0; d < 30; d++)
		{
			if (year)  //year = 0 or 1
				cout << d + 1 << "." << month << "." << currentDate.m_year + 1 << " : " << m_occupationCalender[NextYear][month - 1][d] << endl;
			else
				cout << d + 1 << "." << month << "." << currentDate.m_year << " : " << m_occupationCalender[ThisYear][month - 1][d] << endl;
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
					cout << d + 1 << "." << m + 1 << "." << currentDate.m_year + y << " : " << m_occupationCalender[y][m][d] << endl;
				}
			}
		}
	}
}

void Hostel:: UpdateCurrentDate() // O(1)
{   // Updates the current dates and also the calender if the current year has passed.
	int current_y = currentDate.m_year;
	time_t now = time(0);
	tm ltm;
	localtime_s(&ltm, &now);
	currentDate = { ltm.tm_mday, ltm.tm_mon + 1, 1900 + ltm.tm_year };
	if (currentDate.m_year > current_y)  // the current year has passed
	{
		ResetCalender();
	}
}

void Hostel:: ResetCalender() // O(1)
{   //Moves next year's occupation calender to this year's and resets the the next year calender.
	for (int m = 0; m < 12; m++)
	{
		for (int d = 0; d < 30; d++)
		{
			m_occupationCalender[ThisYear][m][d] = m_occupationCalender[1][m][d];
			m_occupationCalender[NextYear][m][d] = 0;
		}
	}
}

void Hostel:: UpdateVisits()  // O(n)
{
	//Updates the current visits and the future visits according to the current local date

	list<Visit> ::iterator it;  // an iterator to iterate through the list.

	for (it = m_futureVisits.begin(); it != m_futureVisits.end(); it++)
	{
		if (it->m_start == currentDate) {
			m_currentVisits.push_back(*it);  // the iterator is a pointer to items in the list
			m_futureVisits.erase(it);   // removes the visit from the m_future_visit lists.
		}
	}

	for (it = m_currentVisits.begin(); it != m_currentVisits.end(); it++)
	{
		if (!(it->m_end > currentDate)) {  //!IsAfter == true - the date is before the other date.
			m_currentVisits.erase(it);   // removes the visit from the m_currentVisits lists.
		}
	}
}

double Hostel::GetPricePerNight() const
{
	return m_pricePerNight;
}

int Hostel :: GetCurrentNumberOfGuests() const
{
	return  m_currentGuests;
}

int Hostel:: GetCapacity() const
{
	return m_guestCapacity;
}

void Hostel:: SetPricePerNight(double newPrice)
{
	m_pricePerNight = newPrice;
}

void Hostel:: SetCapacity(int newCapacity)
{
	m_guestCapacity = newCapacity;
}
