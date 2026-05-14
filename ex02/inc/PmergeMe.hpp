/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:01:15 by mweghofe          #+#    #+#             */
/*   Updated: 2026/05/14 15:01:57 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <list>

class PmergeMe
{
	private:
	// ---
	std::vector<unsigned int> cVec_;
	std::list<unsigned int> cLst_;
	// ---
	void parseInput(int, char**);
	bool isValid(char*);
	int getInputNumber(char*);
	public:
	// ---
	void execute(int, char**);
	// ---
	PmergeMe();
	PmergeMe(const PmergeMe&);
	~PmergeMe();
	PmergeMe& operator=(const PmergeMe&);
};
