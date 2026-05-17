/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 18:08:01 by mweghofe          #+#    #+#             */
/*   Updated: 2026/05/17 21:44:02 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <algorithm>

/*
	NOTE ON THE CONTAINER TEMPLATES 

	typically a container is defined like this (see reference):
	template<
		class T,
		class Allocator = std::allocator<T>
	> class deque;

	thus std::vector<int> defaults to std::vector<int, std::allocator<int> >
*/

// -----------------------------------------------------------------------------
// UTILITY
// -----------------------------------------------------------------------------

template <typename T>
void PmergeMe::prtContainer(const T& c, const std::string& what)
{
	std::cout << what << ":\n";
	std::for_each(c.begin(), c.end(), PmergeMe::prtInt);
	std::cout << "\n\n";
}

template <typename T>
void PmergeMe::prtDemoContainer(const T& c, const unsigned int& recL, const std::string& what, const bool nl, const bool unP)
{
	std::cout << '[' << recL << "] " << what << ": ";
	std::for_each(c.begin(), c.end(), PmergeMe::prtInt);
	std::cout << '\n';
	if (nl && !unP)
		std::cout << '\n';
}

// -----------------------------------------------------------------------------
// JACOBSTHAL TEMPLATE
// -----------------------------------------------------------------------------

template <
		template <typename, typename> class Container,
		typename T,
		typename A
>
void PmergeMe::buildJacobsthalIndex(const std::size_t& numPairs, Container<T, std::allocator<A> >& output)
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

// -----------------------------------------------------------------------------
// SORTING TEMPLATE
// -----------------------------------------------------------------------------

template <
		template <typename, typename> class Container,
		typename T,
		typename A
>
void PmergeMe::FordJohnsonSort(const Container<T, std::allocator<A> >& rawSet, Container<T, std::allocator<A> >& sorted)
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
	//  setup
	// -----------------------
	unsigned int numPairs = rawSet.size() / 2;
	unsigned int currPair = 0;
	unsigned int unpaired = rawSet.back();
	bool hasUnpaired = rawSet.size() & 1 ? true : false ;
	Container<T, std::allocator<A> > sortedLarger;
	Container<T, std::allocator<A> > larger(numPairs);
	Container<std::pair<T, T>, std::allocator<std::pair<A, A> > > pairs(numPairs);
	Container<std::pair<T, T>, std::allocator<std::pair<A, A> > > sortedPairs(numPairs);
	Container<bool, std::allocator<bool> > consumed(numPairs, false);
	Container<std::size_t, std::allocator<std::size_t> > sequence;
	typename Container<T, std::allocator<A> >::iterator stop;
	typename Container<T, std::allocator<A> >::iterator where;
	if (DEMONSTRATION)
		std::cout <<'[' << recursion << ']' << " Pairs: | ";
	// -----------------------
	//  pairing
	// -----------------------
	for (unsigned int i = 0; i + 1 < rawSet.size(); i += 2)
	{
		if (rawSet[i] >= rawSet [i + 1]) // TODO test if directly assigning first & second makes any difference
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
	// construct the set of larger values
	for (unsigned int i = 0; i < numPairs; i++)
		larger[i] = pairs[i].first;
	FordJohnsonSort(larger, sortedLarger);
	// -----------------------
	//  reorder pairs
	// -----------------------
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
	// due to the template, i cannot use .reserve anymore
	// using .resize has the problem, that .insert doesn't work correctly
	// because .resize also initializes with zero
	sorted.push_back(sortedPairs[0].second);
	for (unsigned int i = 0; i < numPairs; i++)
		sorted.push_back(sortedPairs[i].first);
	if (DEMONSTRATION)
		prtDemoContainer(sorted, recursion, "sorted (before insertion)");
	// -----------------------
	//  insert smaller values
	// -----------------------
	buildJacobsthalIndex(numPairs, sequence);
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
