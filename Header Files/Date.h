#pragma once
#include <cstdlib>
#include <ctime>
struct Date
{

	int m_day;  // The number of the day in the month
	int m_month;  // The number of the month in the year
	int m_year;  // The year
	Date(int d, int m, int y) : m_day(d),m_month(m), m_year(y)
	{

	}
	Date() : m_day(0), m_month(0) , m_year(0)
	{

	}

	static int CalculateDays(Date& start, Date& end)  // O(1)
	{  //Calculates the amount of days between 2 dates.
		int sum = abs((end.m_year - start.m_year) * 360 + (end.m_month - start.m_month) * 30 + (end.m_day - start.m_day));
		return sum;
	}
	bool IsAfter(Date& other) const // O(1)
	{  // Returns true if this date is after the date other and false otherwise.
		if (m_year < other.m_year) 
		{
			return false;
		}
		else if (m_month < other.m_month && m_year == other.m_year)
			return false;
		else if (m_day < other.m_day && m_month == other.m_month && m_year == other.m_year)
			return false;
		return true;
	}
	bool Equals(Date& other) const // O(1)
	{  //Returns true if the dates are the same, and false otherwise.
		if (m_day == other.m_day && m_month == other.m_month && m_year == other.m_year)
			return true;
		return false;
	}
	bool IsBefore(Date& other) const
	{   //Returns true if this date is before the date other and false otherwise.
		if (m_year > other.m_year)
			return false;
		else if (m_month > other.m_month && m_year == other.m_year)
			return false;
		else if (m_day > other.m_day && m_month == other.m_month && m_year == other.m_year)
			return false;
		return true;
	}
	friend std::ostream& operator<< (std::ostream& os, const Date& date)
	{
		os << date.m_day << "." << date.m_month << "." << date.m_year;
		return os;
	}
	bool operator>(Date& other) const
	{
		return IsAfter(other);
	}
	bool operator==(Date& other) const 
	{
		return Equals(other);
	}
	bool operator<(Date& other) const
	{
		return IsBefore(other);
	}
};
