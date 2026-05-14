/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:03:27 by mweghofe          #+#    #+#             */
/*   Updated: 2026/05/14 15:38:15 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cerrno>
#include <cmath>
#include <climits>

// -----------------------------------------------------------------------------
// TESTING
// -----------------------------------------------------------------------------

namespace {
void prtInt(int n)
{
	std::cout << n << ' ';
}
}

// -----------------------------------------------------------------------------
// INTERFACE
// -----------------------------------------------------------------------------

void PmergeMe::execute(int argc, char** argv)
{
	cVec_.reserve(argc - 1);
	parseInput(argc, argv);
	// testing
	std::cout << "vector:\n";
	std::for_each(cVec_.begin(), cVec_.end(), prtInt);
	std::cout << '\n';
	std::cout << "List:\n";
	std::for_each(cLst_.begin(), cLst_.end(), prtInt);
	std::cout << '\n';
}

// -----------------------------------------------------------------------------
// SORTING
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// MERGE

// -----------------------------------------------------------------------------
// INSERT

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
