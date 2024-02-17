#pragma once
#include <queue>
#include <iostream>
#include "CustomerOrder.h"
#include "Station.h"

namespace sdds {
	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

	class Workstation : public Station {
	private:
		std::deque<CustomerOrder> m_orders{};
		Workstation* m_pNextStation{}; // arrows pointing to next station

	public:
		// copy and move should be deleted
		Workstation(const std::string& str);
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station = nullptr);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+= (CustomerOrder && newOrder);
	};
}