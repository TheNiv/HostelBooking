
#include "Hostel.h"
#include <ctime>
#include "linkedList.h";
Hostel::Hostel(const char* city, int geustCap, double pricePerNight, int currentGuests ) : m_city(city), m_guestCapacity(geustCap), m_pricePerNight(pricePerNight), m_currentGuests(currentGuests)
																
{
	time_t now = time(0);
	tm ltm;
	localtime_s(&ltm, &now);
	currentDate = { ltm.tm_mday, ltm.tm_mon + 1, 1900 + ltm.tm_year };
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
{	// Returns true if the visit can be booked and false otherwise.
	if (visit.m_start.m_year != currentDate.m_year && visit.m_start.m_year != currentDate.m_year + 1)
		return false;
	if (visit.m_start > currentDate && EnoughSpaceFor(visit))
	{
		return true;
	}
	return false;
}

bool Hostel::EnoughSpaceFor(Visit& visit) const // O(n)
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
	//Books the visit in the occupation calender and in the future vists list.
	

	node<Visit> *temp = m_futureVisits.tail;
	if (m_futureVisits.tail == nullptr)  //1 node case
	{
		m_futureVisits.head = new node<Visit>(&visit);
		m_futureVisits.tail = m_futureVisits.head;
	}
	else if (visit.m_start <= temp->m_data->m_start)  //first node
	{
		m_futureVisits.InsertFirst(visit);
	}
	else if (visit.m_start <= m_futureVisits.head->m_data->m_start)  //checking if its start date is after the last node's start date.
	{
		m_futureVisits.InsertLast(visit);
	}
	else if (m_currentVisits.tail == m_currentVisits.head)  // 1 node case
	{
		m_futureVisits.head = new node<Visit>(&visit);
		m_futureVisits.tail->next = m_futureVisits.head;
	}
	else
	{
		while (temp->next != nullptr)  // iterating over the rest of the nodes.
		{
			if (visit.m_start < (temp->next->m_data->m_start))
			{
				m_futureVisits.InsertAfter(temp, visit);
				break;
			}
			temp = temp->next;
		}
	}

	int temp_m = visit.m_start.m_month - 1;
	int temp_d = visit.m_start.m_day - 1;
	int temp_y = visit.m_start.m_year == currentDate.m_year ? ThisYear : NextYear;
	
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

void Hostel:: PrintCalender(int month , int year) const // O(1)
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

	while (m_futureVisits.tail!= nullptr && currentDate > m_futureVisits.tail->m_data->m_end) //remove the visits that had ended.
	{
		m_currentVisits.DeleteFirst();
	}
	while (m_futureVisits.tail != nullptr && m_futureVisits.tail->m_data->m_start == currentDate)
	{
		StartVisit(*(m_futureVisits.tail->m_data));
		m_futureVisits.DeleteFirst();
	}
}
void Hostel:: StartVisit(Visit& visit)
{   //Inserts the visit to the currentVisits list.
	node<Visit> *temp = m_currentVisits.tail;
	if (temp == nullptr)  //It is the first node
	{
		m_currentVisits.head = new node<Visit>(&visit);
		m_currentVisits.tail = m_currentVisits.head;
		return;
	}
	else if (visit.m_end <= temp->m_data->m_end)  //checking if it's end date is after the last node's end date.
	{
		m_currentVisits.InsertFirst(visit);
	}
	else if (m_currentVisits.tail == m_currentVisits.head)  // 1 node case
	{
		m_currentVisits.head = new node<Visit>(&visit);
		m_currentVisits.tail->next = m_currentVisits.head;
	}
	else
	{
		while (temp->next != nullptr)  // iterating over the rest of the nodes.
		{
			if (visit.m_end < temp->next->m_data->m_end)
			{
				m_currentVisits.InsertAfter(temp, visit);
				break;
			}
			temp = temp->next;
		}
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

void Hostel :: PrintCurrentVisits() 
{
	m_currentVisits.PrintList();
}
void Hostel:: PrintFutureVisits()
{
	m_futureVisits.PrintList();
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


