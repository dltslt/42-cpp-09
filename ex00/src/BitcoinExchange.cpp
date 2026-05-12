/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:45:30 by mweghofe          #+#    #+#             */
/*   Updated: 2026/05/13 01:04:17 by mweghofe         ###   ########.fr       */
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
	// DEBUG OUTPUT FOR WHOLE MAP CONTAINER
	// std::map<std::string, double>::iterator it;
	// for (it = data_.begin(); it != data_.end(); it++)
	// 	std::cout << it->first << ": " << it->second << '\n';
	processInputData(inputFile);
}

// -----------------------------------------------------------------------------
// IMPLEMENTATION -- PRICE DATA
// -----------------------------------------------------------------------------

void BitcoinExchange::loadPriceData()
{
	std::ifstream file("data.csv");
	std::string line;
	std::string key;
	double value;
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
		throw std::runtime_error("Error: bad database >> " + line);
	// ---
	while (std::getline(file, line))
	{
		parsePriceData(line, key, value);
		data_.insert(std::make_pair(key, value));
	}
}

void BitcoinExchange::parsePriceData(
	const std::string& line,
	std::string& key,
	double& value)
{
	std::string::size_type sep;
	std::string valueString;

	sep = line.find(',');
	if (sep == std::string::npos || line.find(',', sep + 1) != std::string::npos)
		throw std::runtime_error("Error: bad database >> " + line);
	key = trimSpaces(line.substr(0, sep));
	valueString = trimSpaces(line.substr(sep + 1,line.length()));
	value = std::strtod(valueString.c_str(), NULL);
}

// -----------------------------------------------------------------------------
// IMPLEMENTATION -- INPUT DATA
// -----------------------------------------------------------------------------

void BitcoinExchange::processInputData(const std::string& inputFile)
{
	std::ifstream file(inputFile.c_str());
	std::string line;
	std::string date;
	double value;
	// ---
	if (!file.is_open())
		throw std::runtime_error("Error: could not open input file.");
	// ---
	std::getline(file, line);
	if (line != "date | value")
		std::cerr << "Error: bad input, line 1 >> " << line << '\n';
	// ---
	while (std::getline(file, line))
	{
		if (validInputData(line, date, value))
			std::cout << date << " => " << value << " = "
					  << data_[date] * value << '\n';
	}
}

bool BitcoinExchange::validInputData(
	const std::string& line,
	std::string& date,
	double& value)
{
	static int lineNr = 1;
	std::string::size_type sep;
	std::string valueString;
	lineNr++;
	if (line.length() < 13)
	{
		std::cerr << "Error: bad input, line " << lineNr<< " >> " << line << '\n';
		return (false);
	}
	sep = line.find('|');
	if (sep == std::string::npos || line.find('|', sep + 1) != std::string::npos)
	{
		std::cerr << "Error: bad input, line " << lineNr << " >> " << line << '\n';
		return (false);
	}
	date = trimSpaces(line.substr(0,sep));
	valueString = trimSpaces(line.substr(13,line.length()));
	value = std::strtod(valueString.c_str(), NULL);
	if (data_.find(date) == data_.end())
	{
		std::cerr << "Error: bad input, line " << lineNr << " >> " << line << '\n';
		return (false);
	}
	return (true);
}

// -----------------------------------------------------------------------------
// IMPLEMENTATION -- GENERAL HELPERS
// -----------------------------------------------------------------------------

std::string BitcoinExchange::trimSpaces(const std::string& line)
{
	std::string::size_type first, last;
	first = 0;
	while (first < line.size() && std::isspace(static_cast<unsigned char>(line[first])))
		first++;
	last = line.size();
	while (last > first && std::isspace(static_cast<unsigned char>(line[last - 1])))
		last--;
	return (line.substr(first, last));
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
