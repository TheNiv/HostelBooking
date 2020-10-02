#pragma once
#include<iostream>
class Guest
{
private:
	const char* m_name;  // The name of the guest
	int m_age;  // The age of the guest
	const char* m_id; // The id of the guest

public:
	Guest(const char* name, int age, const char* id);
	Guest();
	~Guest();
	const char* GetName();
	int GetAge();
	const char* GetId();
	friend std::ostream& operator<< (std::ostream& , Guest guest);
};


