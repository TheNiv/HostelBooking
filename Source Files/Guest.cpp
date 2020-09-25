#include "Guest.h"

Guest::Guest(const char* name,int age,const char* id)
{
	Guest::m_name = name;
	Guest::m_age = age;
	Guest:m_id = id;
}
Guest::Guest() {
	Guest::m_name = "";
	Guest::m_age = 0;
}

Guest::~Guest()
{
}
