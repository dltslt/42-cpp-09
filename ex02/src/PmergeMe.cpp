/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:03:27 by mweghofe          #+#    #+#             */
/*   Updated: 2026/05/17 13:49:35 by mweghofe         ###   ########.fr       */
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
void prtInt(unsigned int n)
{
	std::cout << n << ' ';
}
void prtVecInt(std::vector<unsigned int>& v)
{
	std::for_each(v.begin(), v.end(), prtInt);
}

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
	std::cout << "\n\nTime to sort data stored in <" << type << ">: ";
	std::cout << runtime / CLOCKS_PER_SEC << " sec "
			  << ms << " ms "
			  << us << " us "
			  << "\t(clocks: " << runtime << ")\n";
}
}

// -----------------------------------------------------------------------------
// INTERFACE
// -----------------------------------------------------------------------------

void PmergeMe::execute(int argc, char** argv)
{
	std::vector<unsigned int> sortedVec;
	std::clock_t start;
	std::clock_t stop;
	std::clock_t runtimeVec;
	// std::clock_t runtimeLst;
	// preperation
	cVec_.reserve(argc - 1);
	parseInput(argc, argv);
	createJacobsthalSequence();
	// Output Line #1
	std::cout << "Unsorted Set:\n"; // TODO consider a wrapper for these
	std::for_each(cVec_.begin(), cVec_.end(), prtInt);
	std::cout << '\n';
	if (DEMONSTRATION)
	{
		std::cout << "List:\n";
		std::for_each(cLst_.begin(), cLst_.end(), prtInt);
		std::cout << '\n';
		std::cout << "\nJacobsthal sequence for this set:\n";
		std::for_each(jacobsthal_.begin(), jacobsthal_.end(), prtInt);
		std::cout << "\n\n";
	}
	// sorting VECTOR
	start = std::clock();
	sortedVec = FordJohnsonVec(cVec_);
	stop = std::clock();
	runtimeVec = stop - start;
	// sorting LIST
	// TODO second container, consider using deque and make sort() a template
	// Output Line #2
	std::cout << "\nSorted Set:\n";
	std::for_each(sortedVec.begin(), sortedVec.end(), prtInt);
	// Output Line #3
	prtRuntime(runtimeVec, "std::vector");
	// Output Line #4
	// TODO time container 2
	// Some Validation
	std::cout << std::endl;
	std::for_each(sortedVec.begin(), sortedVec.end(), checkSorted);
	if (sortedVec.size() < cVec_.size())
		throw std::runtime_error("Error: some numbers got lost...");
	else if (sortedVec.size() > cVec_.size())
		throw std::runtime_error("Error: some numbers got duplicated...");
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

void PmergeMe::buildJacobsthalIndex(const std::size_t& numPairs, std::vector<std::size_t>& output)
{
	std::size_t size = std::max(numPairs, static_cast<std::size_t>(1));
	output.resize(size);
	output[0] = static_cast<std::size_t>(0);
	if (size >= 2)
	{
		output[1] = static_cast<std::size_t>(1);
	}
	if (size == 3)
		output[2] = static_cast<std::size_t>(2);
	for (std::size_t i = 2; i < jacobsthal_.size(); i++)
	{
		std::size_t revStop = std::min(jacobsthal_[i], size - 1);
		std::size_t revStart = jacobsthal_[i - 1] + 1;
		std::size_t jSeqInd = revStop;
		for (; revStart <= revStop; revStart++)
		{
			output[revStart] = jSeqInd--;
		}
	}
}

// TODO check if this is faster if i use an output parameter instead
std::vector<unsigned int> PmergeMe::FordJohnsonVec(std::vector<unsigned int>& data)
{
	static unsigned int recursion;
	recursion++;
	if (DEMONSTRATION)
	{
		std::cout << '[' << recursion << ']' << " current recursion data set: ";
		std::for_each(data.begin(), data.end(), prtInt);
		std::cout << '\n';
	}
	// -----------------------
	//  baseline
	// -----------------------
	if (data.size() <= 1)
	{
		recursion--;
		return (data);
	}
	// -----------------------
	//  pairing
	// -----------------------
	unsigned int numPairs = data.size() / 2;
	unsigned int currPair = 0;
	// fetch unpaired value
	bool hasUnpaired = data.size() & 1 ? true : false ;
	unsigned int unpaired = data.back();
	std::vector<std::pair<unsigned int, unsigned int> > pairs(numPairs);
	if (DEMONSTRATION)
		std::cout <<'[' << recursion << ']' << " Pairs: | ";
	// build the pairs
	for (unsigned int i = 0; i + 1 < data.size(); i += 2)
	{
		if (data[i] >= data [i + 1]) // TODO test if directly assigning first & second makes any difference
			pairs[currPair] = std::make_pair(data[i], data[i + 1]);
		else
			pairs[currPair] = std::make_pair(data[i + 1], data[i]);
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
	std::vector<unsigned int> sortedLarger = FordJohnsonVec(larger);
	// -----------------------
	//  reorder pairs
	// -----------------------
	std::vector<std::pair<unsigned int, unsigned int> > sortedPairs(numPairs);
	std::vector<bool> consumed(numPairs, false);
	if (DEMONSTRATION)
	{
		std::cout << "\n" << '[' << recursion << ']' << " numbers: " << data.size() 
				   << "   pairs: " << numPairs;
		std::cout << "\n" << '[' << recursion << ']' << " sorted Larger: ";
		prtVecInt(sortedLarger);
		std::cout << "\n" << '[' << recursion << ']' << " sorted Pairs: | ";
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
	if (DEMONSTRATION && hasUnpaired)
		std::cout << "\n" << '[' << recursion << ']' << " unpaired value: " << unpaired;
	// -----------------------
	//  build sorted chain
	// -----------------------
	std::vector<unsigned int> sorted;
	sorted.reserve(data.size()); // reserve needs push_back, resize can do []
	sorted.push_back(sortedPairs[0].second);
	for (unsigned int i = 0; i < numPairs; i++)
	{
		sorted.push_back(sortedPairs[i].first);
	}
	if (DEMONSTRATION)
	{
		std::cout << '\n' << '[' << recursion << ']' << " sorted (before insertion): ";
		prtVecInt(sorted);
		std::cout << '\n';
	}
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
	{
		std::cout << '[' << recursion << ']' << " sorted (after insertion): ";
		prtVecInt(sorted);
		std::cout << '\n';
	}
	// -----------------------
	//  insert odd left over value
	// -----------------------
	if (hasUnpaired)
	{
		// locate position where to insert the unpaired value
		where = std::lower_bound(sorted.begin(), sorted.end(), unpaired);
		sorted.insert(where, unpaired);
		if (DEMONSTRATION)
		{
			std::cout << '[' << recursion << ']' << " sorted (with unpaired value): ";
			prtVecInt(sorted);
			std::cout << '\n';
		}
	}
	recursion--;
	return (sorted);
}

// -----------------------------------------------------------------------------
// PARSING
// -----------------------------------------------------------------------------

void PmergeMe::parseInput(int argc, char**argv)
{
	int num;
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '\0')
			continue ;
		if (!isValid(argv[i]))
			throw std::runtime_error("Error: Invalid input.");
		num = getInputNumber(argv[i]);
		cVec_.push_back(num);
		cLst_.push_back(num);
	}
}

bool PmergeMe::isValid(char* item)
{
	while (*item)
	{
		if (!std::isdigit(static_cast<unsigned char>(*item)))
			return (false);
		item++;
	}
	return (true);
}

int PmergeMe::getInputNumber(char* item)
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

PmergeMe::PmergeMe(const PmergeMe& other) : cVec_(other.cVec_), cLst_(other.cLst_)
{}

PmergeMe::~PmergeMe() {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	this->cVec_ = other.cVec_;
	this->cLst_ = other.cLst_;
	return (*this);
}
