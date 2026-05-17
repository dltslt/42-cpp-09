/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:03:27 by mweghofe          #+#    #+#             */
/*   Updated: 2026/05/17 22:47:29 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cerrno>
#include <cmath>
#include <climits>
#include <ctime>

// -----------------------------------------------------------------------------
// UTILIY
// -----------------------------------------------------------------------------

namespace {
void checkSorted(unsigned int n)
{
	static unsigned int last;

	if (n < last)
		throw (std::runtime_error("Error: not sorted correctly"));
	last = n;
}

void prtRuntime(const std::clock_t& runtime, const std::string& type)
{
	// s => ms => us => ns
	unsigned int ms, us;
	ms = runtime / 1000 % 1000;
	us = runtime % 1000;
	std::cout << "Time to sort data stored in <" << type << ">: ";
	std::cout << runtime / CLOCKS_PER_SEC << " sec "
			  << ms << " ms "
			  << us << " us "
			  << "    (clocks: " << runtime << ")\n";
}

void someValidation(const std::vector<unsigned int>& sorted, std::vector<unsigned int>& raw)
{
	std::cout << std::endl;
	std::for_each(sorted.begin(), sorted.end(), checkSorted);
	if (sorted.size() < raw.size())
		throw std::runtime_error("Error: some numbers got lost...");
	else if (sorted.size() > raw.size())
		throw std::runtime_error("Error: some numbers got duplicated...");
}
}

void PmergeMe::prtInt(const unsigned int& n)
{
	std::cout << n << ' ';
}

// -----------------------------------------------------------------------------
// INTERFACE
// -----------------------------------------------------------------------------

void PmergeMe::execute(int argc, char** argv)
{
	// preperation
	std::vector<unsigned int> sortedVec;
	std::deque<unsigned int> sortedDeq;
	std::clock_t start;
	std::clock_t stop;
	cVec_.reserve(argc - 1);
	parseInput(argc, argv);
	createJacobsthalSequence();
	prtContainer(cVec_, "Unsorted Set");		// Output Line #1
	if (DEMONSTRATION)
	{
		prtContainer(cDeq_, "Deque");
		prtContainer(jacobsthal_, "Jacobsthal sequence for this set");
	}
	// sorting VECTOR
	start = std::clock();
	FordJohnsonSort(cVec_, sortedVec);
	stop = std::clock();
	prtContainer(sortedVec, "Sorted Set");		// Output Line #2
	prtRuntime(stop - start, "std::vector");	// Output Line #3
	// sorting DEQUE
	start = std::clock();
	FordJohnsonSort(cDeq_, sortedDeq);
	stop = std::clock();
	prtRuntime(stop - start, "std::deque");		// Output Line #4
	// Some Validation
	someValidation(sortedVec, cVec_);
}

// -----------------------------------------------------------------------------
// SORTING
// -----------------------------------------------------------------------------

void PmergeMe::createJacobsthalSequence()
{
	std::size_t size = std::max(cVec_.size() / 2, static_cast<std::size_t>(1));
	jacobsthal_.reserve(size);
	jacobsthal_.push_back(0);
	if (size >= 2)
	{
		jacobsthal_.push_back(1);
	}
	for (std::size_t i = 2; i < size; i++)
	{
		jacobsthal_.push_back(jacobsthal_[i - 1] + 2 * jacobsthal_[i - 2]);
		if (jacobsthal_[i] > size)
		 break ;
	}
}

// DEPRECATED -- this is left here for comparison
void PmergeMe::FordJohnsonVec(std::vector<unsigned int>& rawSet, std::vector<unsigned int>& sorted)
{
	static unsigned int recursion;
	recursion++;
	if (DEMONSTRATION)
		prtDemoContainer(rawSet, recursion, "current recursion set");
	// -----------------------
	//  baseline
	// -----------------------
	if (rawSet.size() <= 1)
	{
		recursion--;
		if (DEMONSTRATION)
			std::cout << '\n';
		sorted = rawSet;
		return ;
	}
	// -----------------------
	//  pairing
	// -----------------------
	unsigned int numPairs = rawSet.size() / 2;
	unsigned int currPair = 0;
	// fetch unpaired value
	bool hasUnpaired = rawSet.size() & 1 ? true : false ;
	unsigned int unpaired = rawSet.back();
	std::vector<std::pair<unsigned int, unsigned int> > pairs(numPairs);
	if (DEMONSTRATION)
		std::cout <<'[' << recursion << ']' << " Pairs: | ";
	// build the pairs
	for (unsigned int i = 0; i + 1 < rawSet.size(); i += 2)
	{
		if (rawSet[i] >= rawSet [i + 1])
			pairs[currPair] = std::make_pair(rawSet[i], rawSet[i + 1]);
		else
			pairs[currPair] = std::make_pair(rawSet[i + 1], rawSet[i]);
		if (DEMONSTRATION)
			std::cout << pairs[currPair].first << ' ' << pairs[currPair].second << " | ";
		currPair++;
	}
	if (DEMONSTRATION)
		std::cout << "\n\n";
	// -----------------------
	//  sort larger values
	// -----------------------
	std::vector<unsigned int> larger(numPairs);
	// construct the set of larger values
	for (unsigned int i = 0; i < numPairs; i++)
		larger[i] = pairs[i].first;
	// sort the larger values
	std::vector<unsigned int> sortedLarger;
	FordJohnsonVec(larger, sortedLarger);
	// -----------------------
	//  reorder pairs
	// -----------------------
	std::vector<std::pair<unsigned int, unsigned int> > sortedPairs(numPairs);
	std::vector<bool> consumed(numPairs, false);
	if (DEMONSTRATION)
	{
		std::cout << '[' << recursion << "] recursion level: " << recursion
				  << "   numbers: " << rawSet.size() 
				  << "   pairs: " << numPairs << '\n';
		prtDemoContainer(sortedLarger, recursion, "sorted Larger", false, hasUnpaired);
		std::cout << '[' << recursion << ']' << " sorted Pairs: | ";
	}
	// order the pairs according to the sorted list of larger values
	for (unsigned int i = 0; i < numPairs; i++)
	{
		for (unsigned int k = 0; k < numPairs; k++)
		{
			if (!consumed[k] && pairs[k].first == sortedLarger[i])
			{
				sortedPairs[i] = pairs[k];
				consumed[k] = true;
				if (DEMONSTRATION)
					std::cout << sortedPairs[i].first << ' ' << sortedPairs[i].second << " | ";
				break ;
			}
		}
	}
	if (DEMONSTRATION)
	{
		std::cout << '\n';
		if (hasUnpaired)
			std::cout << '[' << recursion << ']' << " unpaired value: " << unpaired << '\n';
	}
	// -----------------------
	//  build sorted chain
	// -----------------------
	sorted.reserve(rawSet.size()); // reserve needs push_back, resize can do []
	sorted.push_back(sortedPairs[0].second);
	for (unsigned int i = 0; i < numPairs; i++)
	{
		sorted.push_back(sortedPairs[i].first);
	}
	if (DEMONSTRATION)
		prtDemoContainer(sorted, recursion, "sorted (before insertion)");
	// -----------------------
	//  insert smaller values
	// -----------------------
	std::vector<std::size_t> sequence;
	buildJacobsthalIndex(numPairs, sequence);
	std::vector<unsigned int>::iterator stop;
	std::vector<unsigned int>::iterator where;
	for (std::size_t iJ = 1; iJ < numPairs; iJ++)
	{
		std::size_t what = sequence[iJ];
		if (DEMONSTRATION)
		{
			std::size_t group = std::lower_bound(
				jacobsthal_.begin(), jacobsthal_.end(), what) - jacobsthal_.begin();
			if (group > 1)
				group--;
			std::cout << "\tjacobsthal insertion, group #" << group;
			std::cout << ": insert " << sortedPairs[what].second << " from pair #" << what << '\n';
		}
		// locate larger value of the pair in sorted set
		stop = std::find(sorted.begin(), sorted.end(), sortedPairs[what].first);
		// to do the proper insertion binary search from begion to larger value
		where = std::lower_bound(sorted.begin(), stop, sortedPairs[what].second);
		// insert before the found position
		sorted.insert(where, sortedPairs[what].second);
	}
	if (DEMONSTRATION)
		prtDemoContainer(sorted, recursion, "sorted (after insertion)", true, hasUnpaired);
	// -----------------------
	//  insert unpaired value
	// -----------------------
	if (hasUnpaired)
	{
		// locate position where to insert the unpaired value
		where = std::lower_bound(sorted.begin(), sorted.end(), unpaired);
		sorted.insert(where, unpaired);
		if (DEMONSTRATION)
			prtDemoContainer(sorted, recursion, "sorted (with unpaired value)", true, false);
	}
	recursion--;
}

// -----------------------------------------------------------------------------
// PARSING
// -----------------------------------------------------------------------------

namespace {
bool isValid(const char* item)
{
	while (*item)
	{
		if (!std::isdigit(static_cast<unsigned char>(*item)))
			return (false);
		item++;
	}
	return (true);
}

int getInputNumber(const char* item)
{
	char* end;
	double num;
	errno = 0;
	num = std::strtod(item, &end);
	// only accept a complete transformation - whole string of digits consumed
	// if (*end != '\0')
	// 	return (false);
	// check for out of bounds
	if (errno == ERANGE)
		throw std::out_of_range("Error: Number out of range.");
	if (num == HUGE_VAL || num == -HUGE_VAL)
		throw std::out_of_range("Error: Number out of range.");
	if (num < INT_MIN || INT_MAX < num)
		throw std::out_of_range("Error: Number out of range.");
	// check for NaN
	// if (num != num)
	// 	return (false);
	return (static_cast<int>(num));
}

std::string nextNumber(const std::string& str, std::string::size_type& pos)
{
	while (pos < str.size() && str[pos] == ' ')
		pos++;
	std::string::size_type start = pos;
	pos = str.find(' ', start);
	if (pos == std::string::npos)
		pos = str.size();
	return (str.substr(start, pos - start));
}
}

void PmergeMe::parseInput(int argc, char**argv)
{
	int num;
	if (argc == 2)
	{
		if (argv[1][0] == '\0')
				return ;
		std::string str(argv[1]);
		std::string next;
		std::string::size_type pos = 0;
		while (pos < str.size())
		{
			next = nextNumber(str, pos);
			if (!isValid(next.c_str()))
				throw std::runtime_error("Error: Invalid input.");
			if (next.empty())
				continue ;
			num = getInputNumber(next.c_str());
			cVec_.push_back(num);
			cDeq_.push_back(num);
		}

	}
	else
		for (int i = 1; i < argc; i++)
		{
			if (argv[i][0] == '\0')
				continue ;
			if (!isValid(argv[i]))
				throw std::runtime_error("Error: Invalid input.");
			num = getInputNumber(argv[i]);
			cVec_.push_back(num);
			cDeq_.push_back(num);
		}
}

// -----------------------------------------------------------------------------
// TIME
// -----------------------------------------------------------------------------

/*
	1 second (s) = 1.000 ms = 1.000.000 µs = 1.000.000.000 ns
	1 millisecond (ms) = 1.000 µs = 1.000.000 ns
	1 microsecond (µs) = 1.000 nanoseconds
	
	old C notes:
	usleep() takes MICROseconds (µs) as input
	nanosleep() takes nanoseconds (ns) as input
	clock_gettime() returns time in seconds (s) and nanoseconds (ns)
	struct timespec stores time in seconds (tv_sec) and nanoseconds (tv_nsec)
	CLOCKMONOTONIC is not affected by changes in system time

	new C++ approach of C solutions comes only with C++11: <chrono> !!

	C++98 must use C implementations
		via <ctime>
			- std::clock()		CPU time consumed
			- std::time()		wall-time in seconds
		via <sys/time.h>
			- gettimeofday()	wall-time in microseconds
		via <time.h>
			- clock_gettime()	real time in nanoseconds
*/

// -----------------------------------------------------------------------------
// OCF
// -----------------------------------------------------------------------------

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) : cVec_(other.cVec_), cDeq_(other.cDeq_)
{}

PmergeMe::~PmergeMe() {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	this->cVec_ = other.cVec_;
	this->cDeq_ = other.cDeq_;
	return (*this);
}
