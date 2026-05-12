/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:45:30 by mweghofe          #+#    #+#             */
/*   Updated: 2026/05/12 23:38:57 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <cstdlib>

// -----------------------------------------------------------------------------
// API
// -----------------------------------------------------------------------------

void BitcoinExchange::execute(const std::string& inputFile)
{
	loadPriceData();
	processInputData(inputFile);
}

// -----------------------------------------------------------------------------
// IMPLEMENTATION
// -----------------------------------------------------------------------------

void BitcoinExchange::loadPriceData()
{
	std::string line;
	std::ifstream file("data.csv");
	// ---
	if (!file.is_open())
	{
		file.open("../data.csv");
		if (!file.is_open())
			throw std::runtime_error("Error: could not open price data file.");
	}
	// ---
	std::getline(file, line);
	if (line != "date,exchange_rate")
		throw std::runtime_error("Error: bad database, line 1 >> " + line);
	// ---
	std::string key;
	double value;
	int lineNr = 2;
	while (std::getline(file, line))
	{
		key = line.substr(0,10);
		value = std::strtod(line.substr(11,line.length()).c_str(), NULL);
		data_.insert(std::make_pair(key, value));
		lineNr++;
	}
	std::map<std::string, double>::iterator it;
	for (it = data_.begin(); it != data_.end(); it++)
		std::cout << it->first << ": " << it->second << '\n';
}

void BitcoinExchange::processInputData(const std::string& inputFile)
{
	std::ifstream file(inputFile.c_str());
	std::string line;
	// ---
	if (!file.is_open())
		throw std::runtime_error("Error: could not open input file.");
	// ---
	std::getline(file, line);
	if (line != "date | value")
		std::cerr << "Error: bad input, line 1 >> " << line << '\n';
	// ---
	std::string date;
	double value;
	int lineNr = 1;
	while (std::getline(file, line))
	{
		lineNr++;
		if (line.length() < 13)
		{
			std::cout << "Error: bad input, line " << lineNr
					  << " >> " << line << '\n';
			continue ;
		}
		date = line.substr(0,10);
		value = std::strtod(line.substr(13,line.length()).c_str(), NULL);
		if (data_.find(date) != data_.end())
			std::cout << date << " => " << value << " = "
					  << data_[date] * value << '\n';
		else
			std::cout << "Error: bad input, line " << lineNr
					  << " >> " << line << '\n';
	}
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
