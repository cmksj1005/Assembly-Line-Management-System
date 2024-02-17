#pragma once
#include <iostream>
#include <string>
#include <sstream>

namespace sdds {
	class Utilities {
	private:
		size_t m_widthField = 1; // instance variable
		static char m_delimiter; // class variable

	public:
		// member functions
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

		// class functions
		// Why I can access to another class's function without instance when I use static?
		static std::string trim(std::string input);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};
}