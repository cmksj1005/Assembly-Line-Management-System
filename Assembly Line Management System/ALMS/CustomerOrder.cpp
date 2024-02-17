#include "CustomerOrder.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
	size_t CustomerOrder::m_widthField{};

	CustomerOrder::CustomerOrder() {}

	CustomerOrder::CustomerOrder(const std::string& str) {
		//find positions of delimiters
		size_t CnamePos = str.find(Utilities::getDelimiter()); // Customer Name Position
		size_t OnamePos = str.find(Utilities::getDelimiter(), CnamePos + 1); // Order Name Position
		//size_t listPos = str.find(Utilities::getDelimiter(), OnamePos + 1); // List of items Position
		//using the position, subtract values from the str
		m_name = str.substr(0, CnamePos);
		m_product = str.substr(CnamePos + 1, OnamePos - CnamePos - 1);
		//trim spaces of both side of the value.
		m_name = Utilities::trim(m_name);
		m_product = Utilities::trim(m_product);

		//since last value of str is list of items, I need to use double pointer
		//first pointer will point str, and second pointers will point each value in str

		//find the last char of str
		char lastChar = str.back();
		//find the position of the last char from the end of str
		size_t lastCharPos = str.rfind(lastChar);
		//using the position, subtract list of items from the str, trim spaces
		std::string tempList = str.substr(OnamePos + 1, lastCharPos - OnamePos + 1);
		tempList = Utilities::trim(tempList);
		//find the number of delimiters
		m_cntItem = 1;
		for (size_t i = 0; i < tempList.length(); i++) {
			if (tempList[i] == Utilities::getDelimiter()) {
				++m_cntItem;
			}
		}
		//make dynamic memory with the numOfDel
		m_lstItem = nullptr;
		m_lstItem = new Item * [m_cntItem];
		//subtract each value in temp and assign it to each second pointer
		size_t startPos{};
		size_t endPos = -1;
		for (size_t i = 0; i < m_cntItem; i++) {
			std::string tempEach{};
			//start position and end position of each items in the list
			startPos = endPos + 1;
			endPos = tempList.find(Utilities::getDelimiter(), startPos);
			tempEach = tempList.substr(startPos, endPos - startPos);
			//dynamic memory for each items - composition
			m_lstItem[i] = new Item(tempEach);
		}
		//if the current value is smaller than the value stored in m_widthField, update it.
		if (m_product.length() > m_widthField) {
			m_widthField = m_product.length();
		}
	}
	//copy constructor
	CustomerOrder::CustomerOrder(const CustomerOrder& src) {
		throw "You shouldn't use copy constructor!";
	}
	//move constructor
	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
		*this = move(src);
	}
	//move assignment
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
		if (this != &src) {
			if (src.m_lstItem != nullptr) {
				for (size_t i = 0; i < m_cntItem; i++) {
					delete m_lstItem[i];
				}
				delete[] m_lstItem;
				m_lstItem = src.m_lstItem;
				src.m_lstItem = nullptr;
				m_name = src.m_name;
				m_product = src.m_product;
				m_cntItem = src.m_cntItem;
				src.m_name = "";
				src.m_product = "";
				src.m_cntItem = 0;
			}
		}
		return *this;
	}
	//destructor
	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}
	//return true if all m_isFilled is true in items.
	bool CustomerOrder::isOrderFilled() const {
		bool result = false;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_isFilled) {
				result = true;
			}
			else {
				result = false;
				break;
			}
		}
		return result;
	}
	//returns true if all items specified by itemName have been filled.
	//If the item doesn't exist in the order, this query returns true
	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool result = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName) {
				if (m_lstItem[i]->m_isFilled) {
					result = true;
				}
				else {
					result = false;
					break;
				}
			}
		}
		return result;
	}
	//pass item information from customer order to station
	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		if (m_cntItem > 0) {
			for (size_t i = 0; i < m_cntItem; i++) {
				if (m_lstItem[i]->m_itemName == station.getItemName()) {
					if (station.getQuantity() > 0) {
						if (!m_lstItem[i]->m_isFilled) {
							m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
							m_lstItem[i]->m_isFilled = true;
							//subtract the item.
							station.updateQuantity();
							os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
							break;
						}

					}
					else { //if we still have customer order but we don't have stock of the item
						os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
					}
				}
			}
		}
		else {
			//do nothing
		}
	}

	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << right << std::setfill('0') << std::setw(6) << m_lstItem[i]->m_serialNumber << "] " << std::left << std::setfill(' ') << std::setw(m_widthField) << m_lstItem[i]->m_itemName << " - ";
			if (m_lstItem[i]->m_isFilled) {
				os << "FILLED" << endl;
			}
			else {
				os << "TO BE FILLED" << endl;
			}
		}
	}

	size_t CustomerOrder::getCntItem() {
		return m_cntItem;
	}
}