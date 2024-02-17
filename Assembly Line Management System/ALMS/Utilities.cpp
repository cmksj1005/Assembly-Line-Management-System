#include "Utilities.h"
using namespace std;

namespace sdds {
	char Utilities::m_delimiter{};

	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		string result{};

		size_t delimiterPos = str.find(m_delimiter, next_pos);
		result = str.substr(next_pos, delimiterPos - next_pos);
		trim(result);

		next_pos = delimiterPos + 1;

		// if str has more delimiter, more is true
		if (next_pos < str.length() && next_pos > 0) {
			more = true;
		}
		else {
			more = false;
		}

		if (result.length() > m_widthField) {
			m_widthField = result.length();
		}

		if (result.length() == 0) {
			more = false; // is it right way to finish displaying Token: blah blah?
			throw "error";
		}

		return result;
	}

	// class functions
	std::string Utilities::trim(std::string input) {
		size_t startPos{};
		size_t endPos{};
		string result{};
		bool checkSpace{};

		for (size_t i = 0; i < input.length(); i++) {
			if (input[i] == ' ') {
				checkSpace = false;
			}
			else {
				checkSpace = true;
				break;
			}
		}

		if (!input.empty() && checkSpace) { // **should fix to handle empty and space
			startPos = input.find_first_not_of(" "); // find the position of first letter
			endPos = input.find_last_not_of(" "); // find the position of last letter
			result = input.substr(startPos, endPos - startPos + 1); // trim spaces in front of, behind of the word
		}

		return result;
	}

	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter() {
		return m_delimiter;

	}
}