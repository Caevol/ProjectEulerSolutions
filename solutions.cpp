#include "solutions.h"

#include <algorithm>
#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>


//takes a list of numbers abundantNums and removes any values from sieveValues that can be expressesd as the sum of 2 abundantNums
//this is a slow brute force implementation, this could have been better achieved with a map. (checking an array for pairs).
void clearSieve(std::vector<int>& sieveValues, std::vector<int>& abundantNums) {
	for (int i = 0; i < abundantNums.size(); ++i) {
		for (int j = i; j < abundantNums.size(); ++j) {
			auto fnd = std::find(sieveValues.begin(), sieveValues.end(), abundantNums[i] + abundantNums[j]);
			if (fnd != sieveValues.end()) {
				sieveValues.erase(fnd);
			}
		}
	}
}

int collatzSequence(long long val, std::map<long long, int>& chainCount) {
	if (val == 1) return 1;
	if (chainCount.find(val) != chainCount.end()) {
		return chainCount[val];
	}

	if (val % 2 == 0) {
		chainCount[val] = collatzSequence(val / 2, chainCount) + 1;
	}
	else {
		chainCount[val] = collatzSequence((val * 3) + 1, chainCount) + 1;
	}
	return chainCount[val];

}

int getDivisorTotal(long long i) {
	int count = 0;
	for (int j = 1; j <= (i / 2); ++j) {
		if (i % j == 0) {
			count++;
		}
	}
	return count + 1; //divisible by self
}

std::vector<long> getDivisorList(long long i) {
	std::vector<long> divisorList;
	for (int j = 1; j <= (i / 2); ++j) {
		if (i % j == 0) {
			divisorList.emplace_back(j);
		}
	}
	divisorList.emplace_back(i);
	return divisorList; //divisible by self
}

std::vector<int> getDivisors(long long i) {
	std::vector<int> divisors;
	for (int j = 1; j <= (i / 2); ++j) {
		if (i % j == 0) {
			divisors.emplace_back(j);
		}
	}
	return divisors; //ignores self
}

std::vector<std::string> getPermutationsInOrder(std::string currentState, std::vector<char> list) {
	std::stringstream ss;
	std::vector<std::string> possibleStrings;
	if (list.size() == 1) {
		ss << currentState << list[0];
		possibleStrings.emplace_back(ss.str());
		return possibleStrings;
	}

	for (auto && g : list) {
		std::vector<char> tmpList = list;
		auto iter = std::find(tmpList.begin(), tmpList.end(), g);
		tmpList.erase(iter);
		ss << currentState << g;

		for (auto && possibility : getPermutationsInOrder(ss.str(), tmpList)) {
			possibleStrings.emplace_back(possibility);
		}

		ss.str(""); //reset stringstream
	}

	if (possibleStrings.size() >= 1000000) {
		std::cout << possibleStrings.size();
	}

	return possibleStrings;

}

std::vector<long> getPossibleCombinations(long long product, int indexNum, int countLeft, std::vector<long>& divisors) {

	product *= divisors[indexNum];
	std::vector<long> combinations;

	if (countLeft == 1) {
		combinations.emplace_back(product);
		return combinations;
	}

	for (int i = indexNum + 1; i < divisors.size(); ++i) {
		for (auto && g : getPossibleCombinations(product, i, countLeft - 1, divisors)) {
			combinations.emplace_back(g);
		}
	}

	return combinations;


}

std::vector<long> getPrimeFactors(long long i, std::map<long, bool>& primeTable) {
	std::vector<long> returnVector = std::vector<long>();
	for (int j = 2; j <= pow(i, .5); ++j) {
		if (isPrime(j, primeTable) && i % j == 0) {
			while (i % j == 0) {
				returnVector.push_back(j);
				i /= j;
			}
			for (auto && g : getPrimeFactors(i, primeTable)) {
				returnVector.push_back(g);
			}
			return returnVector;
		}
	}
	returnVector.emplace_back(i); //i was prime
	return returnVector;
}





unsigned long long getPyramidTop(std::vector<std::vector<unsigned long long>> pyramid) {
	for (int i = pyramid.size() - 1; i > 0; --i) {

		for (int col = 0; col < pyramid[i].size() - 1; ++col) {
			pyramid[i - 1][col] += std::max(pyramid[i][col], pyramid[i][col + 1]); //take the larger of the two paths
		}

	}

	return pyramid[0][0];
}





int getTriangleDivisorTotal(long long countNum, std::map<long, bool>& primeTable) {
	long val1 = countNum;
	long val2 = countNum + 1;
	std::vector<long> divisors;
	std::vector<long> secondaryDivisors;
	if (val1 % 2 == 0) {
		val1 /= 2;
	}
	else {
		val2 /= 2;
	}
	for (auto && g : getPrimeFactors(val1, primeTable)) {
		if (g != 1) {
			divisors.push_back(g);
		}
	}
	for (auto && g : getPrimeFactors(val2, primeTable)) {
		if (g != 1) {
			divisors.push_back(g);
		}
	}

	for (int combCount = 2; combCount <= divisors.size(); ++combCount) {
		for (int index = 0; index <= divisors.size() - combCount + 1; ++index) {
			for (auto && g : getPossibleCombinations(1, index, combCount, divisors)) {
				if (std::find(std::begin(secondaryDivisors), std::end(secondaryDivisors), g) == secondaryDivisors.end()) {
					secondaryDivisors.emplace_back(g);
				}
			}
		}
	}

	for (auto && g : divisors) {
		if (std::find(std::begin(secondaryDivisors), std::end(secondaryDivisors), g) == secondaryDivisors.end()) {
			secondaryDivisors.emplace_back(g);
		}
	}

	return secondaryDivisors.size() + 1; //divisible by 1
}

bool isPalendrome(int value) {
	std::string stringVal = std::to_string(value);

	std::string revVal = stringVal;
	std::reverse(revVal.begin(), revVal.end());

	if (stringVal == revVal) {
		return true;
	}
	return false;

}

bool isPrime(long long i, std::map<long, bool>& primeTable) {
	if (i == 2) {
		primeTable[i] = true;
		return true;
	}

	if (primeTable.find(i) == primeTable.end()) {
		for (int j = 2; j <= pow(i, .5); ++j)
		{
			if (isPrime(j, primeTable)) {
				if (i % j == 0) {
					primeTable[i] = false;
					return false;
				}
			}
		}
		primeTable[i] = true;
		return true;
	}
	else {
		return primeTable[i];
	}
}

//get possible ways to combine numbers from options to get goalNum. Options must be provided in sorted order
//This is slow because it explores impossible possibilities and does not use memoization
int possibleCombinations(int goalNum, int currentTotal, std::vector<int>& options) {
	if (currentTotal == goalNum) {
		return 1;
	}
	if (currentTotal + options[0] > goalNum) { //verify that we can reach 200
		return 0;
	}

	int totalCombinations = 0;
	for (auto && g : options) {
		std::vector<int> tmpOptions = options;
		auto erasable = std::find(tmpOptions.begin(), tmpOptions.end(), g);
		tmpOptions.erase(tmpOptions.begin(), erasable);
		if (currentTotal + g <= goalNum) {
			totalCombinations += possibleCombinations(goalNum, currentTotal + g, tmpOptions);
		}
	}
	return totalCombinations;
}