#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "Utilities.h"

namespace sdds {
	class Station {
	private:
		//Instance Variables
		int m_id{};
		std::string m_name{};
		std::string m_desc{};
		unsigned int m_nextSerialNum{};
		unsigned int m_numOfItem{};
		//Class Variables
		static size_t m_widthField;
		static int id_generator;

	public:
		Station(const std::string& input);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}