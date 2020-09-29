#pragma once

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
};


