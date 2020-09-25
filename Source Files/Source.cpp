#include <iostream>
#include <ctime>
#include <list>
#include <fstream>
#include "Date.h"
#include "Visit.h"
#include "Guest.h"
#include "Hostel.h"


int main() {

	Hostel DavidHostel = Hostel("Jerusalem", 200, 30);
	Date start = Date(24, 10, 2020);
	Date end = Date(28, 10, 2020);
	Guest guest1 = Guest("Niv Lifshitz", 17, "123456");
	Visit vis = Visit(start, end, 3,guest1);
	cout << start.month << endl;
	DavidHostel.BookVisit(vis);
	DavidHostel.PrintCalender(10);
	cout << DavidHostel.GetVisitCost(vis) << endl;
	cin.get();
	return 0;
}


