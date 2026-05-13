/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 10:05:04 by mweghofe          #+#    #+#             */
/*   Updated: 2026/05/13 10:10:44 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	PmergeMe	PmergeMe;
	if (argc == 1)
	{
		std::cout << "Usage:\t./PmergeMe <positive numbers>\nexamples:\n";
		std::cout << "\t./PmergeMe \"1 3 597 21 1 367 \"\n"
				  << "\t./PmergeMe 982 845 9 352 1597 11\n"
				  << "\t./PmergeMe `shuf -i 1-100000 -n 3000 | tr \"\\n\" \" \"`";
		return (1);
	}
	else
	{
		try
		{
			PmergeMe.execute(argv);
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			return (2);
		}
	}
	return (0);
}