#pragma once
#include "Date.h"
#include "Guest.h"
struct Visit {
	Date m_start;
	Date m_end;
	int m_days;
	int m_guests;  // number of guest in the visit
	Guest m_orderer;
	Visit(Date s, Date e,int n_guests,Guest orderer) {
		m_start = s;
		m_end = e;
		m_days = Date::CalculateDays(s, e);
		m_guests = n_guests;
		m_orderer = orderer;
	}
	Visit() {
		m_start = Date();
		m_end = Date();
		m_days = 0;
		m_guests = 0;
	}


};