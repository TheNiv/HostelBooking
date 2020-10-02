#include "Guest.h"

Guest::Guest(const char* name, int age, const char* id) : m_name(name), m_age(age),m_id(id)
{

}
Guest::Guest() : m_name(""),m_age(0)
{
}

Guest::~Guest()
{
}
const char* Guest::GetName() 
{
	return m_name;
}
int Guest::GetAge() 
{
	return m_age;
}
const char* Guest::GetId()
{
	return m_id;
}

std::ostream& operator<< (std::ostream& os , Guest guest)
{
	os<< "name:" << guest.GetName() << std::endl;
	os << "Age:" << guest.GetAge() << std::endl;
	os<< "Id:" << guest.GetId() << std::endl;
	return os;
}
