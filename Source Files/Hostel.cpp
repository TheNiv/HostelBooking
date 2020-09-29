
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


