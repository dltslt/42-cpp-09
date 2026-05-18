/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:43:05 by mweghofe          #+#    #+#             */
/*   Updated: 2026/05/18 09:18:13 by mweghofe         ###   ########.fr       */
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

/* my test data
date | value
2021-01-03 | 1 
2021-01-03 |
2022-02-29 | 1
2022-03-01
2022-03-13    
2022-03-14 | 10
2022-03-15 | 20
2022-03-16 | 100
2022-03-17 | 123
2022-03-18 | 0
2022-03-19 |a01+
2022-03-22         |     
2022-03-25 | -1
2022-03-29 | 1
2000-12-01 | 1
2020-02-28 | 1
2020-02-29 | 1
2020-02-30 | 1
2020-03-32 | 1
2020-04-00 | 1
2020-04-01 | -012334
2020-04-02 | 1001
2020-04-03 | nan
2020-04-03 | NaN
2020-04-03 | inf
1990-12-06 | 123
*/
