/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:45:30 by mweghofe          #+#    #+#             */
/*   Updated: 2026/05/12 22:24:00 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <stdexcept>

// -----------------------------------------------------------------------------
// API
// -----------------------------------------------------------------------------

void BitcoinExchange::execute(const std::string& inputFile)
{
	loadPriceData();
	loadInputData(inputFile);
}

// -----------------------------------------------------------------------------
// IMPLEMENTATION
// -----------------------------------------------------------------------------

void BitcoinExchange::loadPriceData()
{
	std::ifstream file("data.csv");
	if (!file.is_open())
		throw std::runtime_error("Error: could not open price data file.");
}

void BitcoinExchange::loadInputData(const std::string& inputFile)
{
	std::ifstream file(inputFile.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not open input file.");
}

// -----------------------------------------------------------------------------
// OCF
// -----------------------------------------------------------------------------

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
	: data_(other.data_)
{}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	data_ = other.data_;
	return (*this);
}
