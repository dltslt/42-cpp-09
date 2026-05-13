/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 09:46:35 by mweghofe          #+#    #+#             */
/*   Updated: 2026/05/13 11:54:46 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <stdexcept>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>

// -----------------------------------------------------------------------------
// IMPLEMENTATION
// -----------------------------------------------------------------------------

void RPN::execute(char*& argv)
{
	std::string expression(argv);
	for (std::string::size_type i = 0; i < expression.size(); i++)
	{
		// 1) skip leading spaces before the character
		while (expression[i] == ' ')
			i++;
		// 2) check if still inside string
		if (i == expression.size())
			break ;
		// 3) validate that every character is separated by spaces
		if (i > 0 && expression[i - 1] != ' ')
			throw std::runtime_error(
				"Error: bad input >> " + expression.substr(i-1));
		// 4) process the current character
		if (std::isdigit(static_cast<unsigned char>(expression[i])))
			stack_.push(std::atoi(&expression.c_str()[i]));
		else if (std::strchr("+-/*", expression[i]))
		{
			if (stack_.size() > 1)
				operation(expression[i]);
			else
				throw std::runtime_error("Error: too many operators");
		}
		else
			throw std::runtime_error(
				"Error: bad input >> " + expression.substr(i));
		// 5) skip trailing spaces after the character
		while (expression[i] == ' ')
			i++;
	}
	if (stack_.size() > 1)
		throw std::runtime_error("Error: too many digits");
	else if (stack_.size() == 0)
		throw std::runtime_error("Error: no digits");
	std::cout << stack_.top() << std::endl;
}

void RPN::operation(char& c)
{
	int result, right, left;
	right = stack_.top();
	stack_.pop();
	left = stack_.top();
	stack_.pop();
	if (c == '+')
		result = left + right;
	else if (c == '-')
		result = left - right;
	else if (c == '*')
		result = left * right;
	else if (c == '/')
		result = left / right;
	if (DEBUG && stack_.size())
		std::cout << "last stack & calculcation: " << stack_.top() << " | "
				  << result << " = " << left << ' ' << c << ' ' << right
				  << std::endl;
	else if (DEBUG)
		std::cout << "last stack & calculcation: ... | "
				  << result << " = " << left << ' ' << c << ' ' << right
				  << std::endl;
	stack_.push(result);
}


// -----------------------------------------------------------------------------
// OCF
// -----------------------------------------------------------------------------

RPN::RPN() {}

RPN::RPN(const RPN& other) : stack_(other.stack_)
{}

RPN::~RPN() {}

RPN& RPN::operator=(const RPN& other)
{
	this->stack_ = other.stack_;
	return (*this);
}
