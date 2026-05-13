/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:03:27 by mweghofe          #+#    #+#             */
/*   Updated: 2026/05/13 10:04:58 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// -----------------------------------------------------------------------------
// IMPLEMENTATION
// -----------------------------------------------------------------------------

void PmergeMe::execute(char** argv)
{
	(void) argv;
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
