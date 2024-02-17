#include "Workstation.h"


using namespace std;

namespace sdds {
	//each deque is accessble outside this module's translation unit
	std::deque<CustomerOrder> g_pending{};
	std::deque<CustomerOrder> g_completed{};
	std::deque<CustomerOrder> g_incomplete{};

	Workstation::Workstation(const std::string& str) : Station(str) {}
	//fills the order ar the front of the queue if there are CustomerOrders in the queue
	void Workstation::fill(std::ostream& os) {
		if (!m_orders.empty()) {
			// I should use fillItem function here
			m_orders[0].fillItem(*this, os); // it will make a problem. Let's check it later.
		}
		else {
			// do nothing
		}
	}

	bool Workstation::attemptToMoveOrder() {
		bool result = false;
		//if I try to access m_order when the size is 0, it makes an error says 'deque subscript out of range'
		if(m_orders.size() > 0) {
			//if the station doesn't have the order item, or if the station is out of inventory
			if (m_orders[0].isItemFilled(this->getItemName()) || this->getQuantity() <= 0) {
				//if this work station is not the last one
				if (m_pNextStation != nullptr) {
					m_pNextStation->m_orders.push_back(std::move(m_orders[0]));
					m_orders.pop_front();
				}
				else {
					//if all the items in the order are filled, the order should move to g_completed
					if (m_orders[0].isOrderFilled()) {
						g_completed.push_back(std::move(m_orders[0]));
						m_orders.pop_front();
					}
					else {
						g_incomplete.push_back(std::move(m_orders[0]));
						m_orders.pop_front();
					}

				}
				result = true;
			}
		}
		return result;
	}

	void Workstation::setNextStation(Workstation* station) {
		//Parameter defaults tp nullptr
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const {
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const {
		//if this work station not the last one
		if (m_pNextStation != nullptr) {
			os << this->getItemName() << " --> " << m_pNextStation->getItemName() << endl;
		} //if this work station is the last one
		else {
			os << this->getItemName() << " --> " << "End of Line" << endl;;
		}
	}
	// What is the advantage of using && here? I need to use move for it.
	Workstation& Workstation::operator+= (CustomerOrder&& newOrder) {
		m_orders.push_back(std::move(newOrder));

		return *this;
	}
}