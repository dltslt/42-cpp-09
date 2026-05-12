/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:43:05 by mweghofe          #+#    #+#             */
/*   Updated: 2026/05/12 22:19:57 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	BitcoinExchange btc;
	if (argc > 2)
	{
		std::cout << "Usage: ./btc <filename>" << std::endl;
		return (1);
	}
	try
	{
		std::string inputFile;
		if (argv[1])
			inputFile = argv[1];
		btc.execute(inputFile);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (2);
	}
	return (0);
}
