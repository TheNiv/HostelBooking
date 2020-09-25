#include "Hostel.h"
#include <ctime>
Hostel::Hostel(const char* city,int geustCap,double pricePerNight, int currentGuests = 0)
{
	Hostel::m_city = city;
	Hostel::m_guestCapacity = geustCap;
	Hostel::m_pricePerNight = pricePerNight;
	Hostel::m_currentGuests = currentGuests;
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

Hostel::Hostel()
{
	Hostel::m_city = "";
	Hostel::m_guestCapacity = 0;
	Hostel::m_pricePerNight = 0;
	Hostel::m_currentGuests = 0;
	currentDate = Date();
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


