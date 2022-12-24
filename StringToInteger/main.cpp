#include <iostream>
#include <string>
#include <algorithm>

namespace leetcode {
	class Solution final {
	public:
		int myAtoi(const std::string& s) {
			bool hasPlus = false, hasMinus = false;
			bool numberStarted = false, numberFinished = false;
			bool digitNotZeroFound = false;

			std::uint8_t digitCounter = 0;
			constexpr std::uint8_t INT_MAX_LENGTH = 10;
			
			std::string buffer;
			std::copy_if(s.begin(), s.end(), std::back_inserter(buffer), [&](char character) {
				if (numberFinished) return false;
				if (hasPlus && hasMinus) return false;
				if (digitCounter > INT_MAX_LENGTH) return false;

				if (std::isalpha(character)) {
					numberFinished = true;
					return false;
				}

				if (character == '.') {
					numberFinished = true;
					return false;
				}

				if (character == '-' || character == '+') {
					(!numberStarted) ? numberStarted = true : numberFinished = true;

					if (!numberFinished)
						(character == '-') ? hasMinus = true : hasPlus = true;
					
					return false;
				}

				if (!std::isdigit(character)) {
					if (numberStarted)
						numberFinished = true;

					return false;
				}
				else if (character == '0' && !digitNotZeroFound) {
					numberStarted = true;
					return false;
				}
				else {
					numberStarted = true;
					digitNotZeroFound = true;
					digitCounter++;
					return true;
				}
			});
			
			if (digitCounter > INT_MAX_LENGTH)
				if (hasMinus)
					return std::numeric_limits<int>::min();
				else
					return std::numeric_limits<int>::max();

			if (digitCounter == INT_MAX_LENGTH) {
				std::string positiveMax = "2147483647";
				std::string negativeMax = "2147483648";

				if (buffer > negativeMax)
					if (hasMinus)
						return std::numeric_limits<int>::min();
					else
						return std::numeric_limits<int>::max();
				if (buffer > positiveMax)
					if (!hasMinus)
						return std::numeric_limits<int>::max();
					else
						return std::numeric_limits<int>::min();
			}

			long long positionCoefficient = 1;
			int result = 0;
			std::uint8_t digitSign;
			for (int i = buffer.size() - 1; i > -1; --i) {
				digitSign = static_cast<int>(buffer[i]) - '0';
				result += digitSign * positionCoefficient;
				positionCoefficient *= 10;
			}

			return (hasMinus) ? result * -1 : result;
		}
	};
}

int main() {
	leetcode::Solution solution;
	std::cout << solution.myAtoi("123-");
	return 0;
}