#pragma once
#include"Date.h"
#include"Guest.h"
struct Visit {
	Date m_start;  // The start date of the visit
	Date m_end;  // The end date of the visit
	int m_days;  // The amount of days of the visit
	int m_guests;  // number of guest in the visit
	Guest m_orderer;  // The guest who ordered the visit
	Visit(Date s, Date e, int n_guests, Guest orderer) : m_start(s), m_end(e), m_guests(n_guests), m_orderer(orderer)
	{

		m_days = Date::CalculateDays(s, e);

	}
	Visit() : m_start(Date()), m_end(Date()), m_days(0),m_guests(0)
	{

	}
	friend std::ostream& operator<< (std::ostream& os, const Visit& visit) {
		os << "Start date:" << visit.m_start << std::endl;
		os << "End date:" << visit.m_end << std::endl;
		os << "Number of days:" << visit.m_days << std::endl;
		os << "Number of guests:" << visit.m_guests << std::endl;
		os << "Orderer Details:" << std::endl<< visit.m_orderer;
		return os;
	}
};
