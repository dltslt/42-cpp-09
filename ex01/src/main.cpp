/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 09:47:40 by mweghofe          #+#    #+#             */
/*   Updated: 2026/05/13 11:15:36 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
#include <exception>

int main(int argc, char** argv)
{
	RPN	rpn;
	if (argc != 2 || argv[1][0] == '\0')
	{
		std::cout << "Usage:\t./RPN <a reverse polish notation>\nexamples:\n";
		std::cout << "\t./RPN \"1 1 +\"\n"
				  << "\t./RPN \"1 2 3 4 + / * 9 +\"\n";
		return (1);
	}
	else
	{
		try
		{
			rpn.execute(argv[1]);
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			return (2);
		}
	}
	return (0);
}
