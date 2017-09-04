#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include <map>
#include <vector>

/**
 * A series of equations used to solve problems from projecteuler.net
 * Did not include trivial questions and questions that were solved on paper
 *
 * @author Logan Pedersen
 */


 /**
 * clears any value from sieveValues that can be expressed as the sum of 2 abundantNums
 * Very inefficient, should have been implemented using maps instead of brute force checking
 *
 * Questions : 23
 */
void clearSieve(std::vector<int>& sieveValues, std::vector<int>& abundantNums);

/**
* Finds number of steps using Collatz sequence to get some value val to equal 1.
* Support memoization using a map Chaincount which maps values to Collatz Sequence counts.
*
* Questions : 14
*/
int collatzSequence(long long val, std::map<long long, int>& chainCount);

/**
 * Gets total divisors (including self) for value i
 * Brute force
 */
int getDivisorTotal(long long i);

/**
* Gets list of divisors (including self) for value i
* This is a brute force method that gets results slowly
*/
std::vector<long> getDivisorList(long long i);

/**
 * Gets list of divisors (excluding self) for value i
 * This is a brute force method that gets results slowly
 */
std::vector<int> getDivisors(long long i);

/**
 * finds all possible permutations of a list of characters based on order of list.
 * getPermutationsInOrder("", {0, 1, 2}) = {"012", "021", "102", "120", "201", "210"}
 *
 * Questions : 24
 */
std::vector<std::string> getPermutationsInOrder(std::string currentState, std::vector<char> list);

/**
 * Takes a list of values and gets all possible products of those numbers.
 * Useful for taking prime factors and getting all divisors from the bottom up
 * ensure the first value in divisors is 1.
 *
 * getPossibleCombinations(1, 0, divisors.size(), divisors)
 *
 * Questions : 12
 */
std::vector<long> getPossibleCombinations(long long product, int indexNum, int countLeft, std::vector<long>& divisors);

/**
 * Gets a list of prime factors for some long long i, includes multiples of same prime
 * getPrimeFactors(60. primeMap) would return {2, 2, 3, 5}
 * 
 * Questions : 3
 *
*/
std::vector<long> getPrimeFactors(long long, std::map<long, bool>&);

/**
 * Takes a pyramid of numbers (where each row is 1 larger than the last), and finds largest possible sum by taking a path through the pyramid
 * Method: Move from bottom up and compare two available paths for each column, taking the maximized path. Extremely fast
 *
 * Questions : 18, 67
 */
unsigned long long getPyramidTop(std::vector<std::vector<unsigned long long>> pyramid);

/**
 * Gets the total number of divisors for triangular number with index countNum
 * Takes index countNum and a primeMap.
 * Uses definition of triangular number as number = (n)(n-1)/2
 *
 * Questions : 12
 */
int getTriangleDivisorTotal(long long, std::map<long, bool>&);

/**
* Checks whether or not some int value is a palendrome
* Questions : 4
*/
bool isPalendrome(int value);

/**
* Discovers whether or not some number i is prime, uses a prime map
* Uses memoization, does not use sieve
*/
bool isPrime(long long, std::map<long, bool>&);

/**
 * Gets possible combinations from the list options (must be sorted from smallest to largest)
 * and returns the number of combinations to get the sum goalNum using any number of the items from options
 * possibleCombinations(200, 0, {1, 2, 5, 10, 20, 50, 100, 200}) = 73682
 * This is slow because it explored impossible options and rules them out
 *
 * Questions : 31
 */
int possibleCombinations(int goalNum, int currentTotal, std::vector<int>& options);



#endif