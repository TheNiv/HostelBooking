#pragma once
#include "Visit.h"

class Guest
{
private:
	const char* m_name;  // the name of the guest
	int m_age;  // the age of the guest
	const char* m_id; // the id of the guest

public:
	Guest(const char* name, int age, const char* id);
	Guest();
	~Guest();
};


