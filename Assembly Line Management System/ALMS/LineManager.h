#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include "Workstation.h"

namespace sdds {
	class LineManager {
	private:
		std::vector<Workstation*> m_activeLine{}; // collection of workstations for the current assembly line
		//should keet the size of initial g_pending for checking whether all the orders are completed
		size_t m_cntCustomerOrder{}; // total number of CustomerOrder objects
		Workstation* m_firstStation{}; // points to the first active station on the current line

	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void reorderStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;
	};
}