/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:01:15 by mweghofe          #+#    #+#             */
/*   Updated: 2026/05/17 23:00:45 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <deque>
#include <string>

#ifndef DEMONSTRATION
# define DEMONSTRATION 0
#endif

class PmergeMe
{
	private:
	// ---
	std::vector<unsigned int> cVec_;
	std::deque<unsigned int> cDeq_;
	std::vector<std::size_t> jacobsthal_;
	// ---
	void parsing(int, char**);
	void parseChunk(const char*);
	// ---
	void createJacobsthalSequence();
	// -- main execution
	template <typename T>
	void buildJacobsthalIndex(const std::size_t&, T&);
	template <
		template <typename, typename> class Container,
		typename T,
		typename A>
	void FordJohnsonSort(const Container<T, std::allocator<A> >&, Container<T, std::allocator<A> >&);
	// -- utility
	static void prtInt(const unsigned int&);
	template <typename T>
	void prtContainer(const T&, const std::string&);
	template <typename T>
	void prtDemoContainer(const T&, const unsigned int&, const std::string& what, const bool = false, const bool = false);
	// -- DEPRECATED (archive only)
	void FordJohnsonVec(std::vector<unsigned int>&, std::vector<unsigned int>&);
	public:
	// ---
	void execute(int, char**);
	// ---
	PmergeMe();
	PmergeMe(const PmergeMe&);
	~PmergeMe();
	PmergeMe& operator=(const PmergeMe&);
};

#include "template/PmergeMe.tpp"

/*

•  •  •  •  •  •  •  •  •  •  •  •  •  •  •  •  •  •  •

[• •] [• •] [• •] [• •] [• •] [• •] [• •] [• •] [• •] •

 a b   a b   a b   ...

 a = bigger (winners)
 b = smaller (losers)


   ●  ●  ●  ●  ●  ●  ●  ●  ●
  /  /  /  /  /  /  /  /  / 
 /  /  /  /  /  /  /  /  /  
●  ●  ●  ●  ●  ●  ●  ●  ●  ●


[• •] [• •] [• •] [• •] •

...

================================================================================

   ●––●––●––●––●––●––●––●––●––●––●––●––●––●––●––●––●––●––●
  /  /  /  /  /  /  /  /  /  /  /  /  /  /  /  /  /  /  /
 /  /  /  /  /  /  /  /  /  /  /  /  /  /  /  /  /  /  /
●  ●  ●  ●  ●  ●  ●  ●  ●  ●  ●  ●  ●  ●  ●  ●  ●  ●  ●


●  ●––●––●––●––●––●––●––●––●––●––●––●––●––●––●––●––●––●––●
     /  /  /  /  /  /  /  /  /  /  /  /  /  /  /  /  /  /
    /  /  /  /  /  /  /  /  /  /  /  /  /  /  /  /  /  /
   ●  ●  ●  ●  ●  ●  ●  ●  ●  ●  ●  ●  ●  ●  ●  ●  ●  ●
   ‾  ‾‾‾‾  ‾‾‾‾  ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾  ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
*/
