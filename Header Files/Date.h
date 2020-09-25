#pragma once
#include <cstdlib>
#include <ctime>
struct Date
{
	int day;
	int month;
	int year;
	Date(int d,int m,int y) {
		day = d;
		month = m;
		year = y;
	}
	Date() {
		day = 0;
		month = 0;
		year = 0;
	}

	static int CalculateDays(Date& start, Date& end) {
		int sum = abs((end.year - start.year) * 360 + (end.month - start.month) * 30 + (end.day - start.day));
		return sum;
	}
	bool IsAfter(Date& date) {
		if (year < date.year) {
			return false;
		}
		else if (month < date.month && year == date.year)
			return false;
		else if (day < date.day && month == date.month && year == date.year)
			return false;			
		return true;
	}
	bool Equals(Date& d) 
	{  //returns true if the dates are the same, false otherwise.
		if (day == d.day && month == d.month && year == d.year)
			return true;
		return false;
	}
};
