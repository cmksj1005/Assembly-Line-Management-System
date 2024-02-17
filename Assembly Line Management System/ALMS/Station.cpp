#include "Station.h"

using namespace std;

namespace sdds {
	//Why I have to declare it here?
	size_t Station::m_widthField{};
	int Station::id_generator{};

	Station::Station(const std::string& input) {
		size_t namePos = input.find(Utilities::getDelimiter());
		size_t seriPos = input.find(Utilities::getDelimiter(), namePos + 1);
		size_t quanPos = input.find(Utilities::getDelimiter(), seriPos + 1);
		size_t descPos = input.find(Utilities::getDelimiter(), quanPos + 1);

		m_id = ++id_generator;
		m_name = input.substr(0, namePos);
		m_nextSerialNum = stoi(input.substr(namePos + 1, seriPos - namePos));
		m_numOfItem = stoi(input.substr(seriPos + 1, quanPos - seriPos));
		m_desc = input.substr(quanPos + 1, descPos - quanPos);

		m_name = Utilities::trim(m_name);
		m_desc = Utilities::trim(m_desc);

		if (m_name.length() > m_widthField) {
			m_widthField = m_name.length();
		}
	}

	const std::string& Station::getItemName() const {
		return m_name;
	}

	size_t Station::getNextSerialNumber() {
		unsigned int currentNum = m_nextSerialNum; //to return current value of m_nextSerialNum
		m_nextSerialNum++; // increase m_nextSerialNum

		return currentNum;
	}

	size_t Station::getQuantity() const {
		return m_numOfItem;
	}

	void Station::updateQuantity() {
		if (m_numOfItem > 0) {
			--m_numOfItem;
		}
	}

	void Station::display(std::ostream& os, bool full) const {
		if (full) {
			os << std::right << std::setfill('0') << std::setw(3) << m_id << std::setfill(' ') << " | " << std::left << std::setw(m_widthField) << m_name << " | " << std::right << std::setfill('0') << std::setw(6) << m_nextSerialNum << " | " << std::right << std::setfill(' ') << std::setw(4) << m_numOfItem << " | " << m_desc << endl;
		}
		else {
			os << std::right << std::setfill('0') << std::setw(3) << m_id << std::setfill(' ') << " | " << std::left << std::setw(m_widthField) << m_name << " | " << std::right << std::setfill('0') << std::setw(6) << m_nextSerialNum << " | " << endl;
		}
	}
}