/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:45:30 by mweghofe          #+#    #+#             */
/*   Updated: 2026/05/13 02:16:44 by mweghofe         ###   ########.fr       */
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
	if (!validDate(key))
		throw std::runtime_error("Error: bad database >> " + line);
	valueString = trimSpaces(line.substr(sep + 1,line.length()));
	value = std::strtod(valueString.c_str(), NULL); // FIXME add proper strtoX validation
	// TODO value validation
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
	double price;
	int lineNr = 1;
	// ---
	if (!file.is_open())
		throw std::runtime_error("Error: could not open input file.");
	// ---
	std::getline(file, line);
	if (line != "date | value")
		std::cerr << "Error: bad input, line " << lineNr++ << " >> " << line << '\n';
	// ---
	while (std::getline(file, line))
	{
		if (!validInputData(line, date, value, lineNr))
			continue ;
		if (havePriceData(date, price))
			std::cout << date << " => " << value << " = " << price * value << '\n';
		else
			std::cerr << "Error: bad input, line " << lineNr << " >> " << line << '\n';
	}
}

bool BitcoinExchange::validInputData(const std::string& line, std::string& date,
	double& value, int &lineNr)
{
	std::string::size_type sep;
	std::string valueString;
	lineNr++;
	sep = line.find('|');
	if (sep == std::string::npos || line.find('|', sep + 1) != std::string::npos)
	{
		std::cerr << "Error: bad input, line " << lineNr << " >> " << line << '\n';
		return (false);
	}
	date = trimSpaces(line.substr(0,sep));
	if (!validDate(date))
	{
		std::cerr << "Error: bad input date, line " << lineNr << " >> " << line << '\n';
		return (false);
	}
	valueString = trimSpaces(line.substr(13,line.length()));
	value = std::strtod(valueString.c_str(), NULL); // FIXME add proper strtoX validation
	// TODO value validation
	return (true);
}

bool BitcoinExchange::havePriceData(std::string& date, double& price)
{
	std::map<std::string, double>::const_iterator it;
	// search for key (date), finds exact or NEXT element
	it = data_.lower_bound(date);
	// exact match found
	if (it != data_.end() && it->first == date)
	{
		price = it->second;
		return (true);
	}
	// no match found, date is outside price data
	if (it == data_.begin())
		return (false);
	// no match found, date is in price data range, take previous entry
	--it;
	price = it->second;
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

bool BitcoinExchange::validDate(const std::string& date)
{
	int year, month, day;
	const int dayMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	// basic character check
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return (false);
	// transformation with advanced character check
	// FIXME add proper strtoX validation
	year = std::strtol(date.substr(0, 4).c_str(), NULL, 10);
	month = std::strtol(date.substr(5, 2).c_str(), NULL, 10);
	day = std::strtol(date.substr(8, 2).c_str(), NULL, 10);
	// individual checks
	if (year < 2009 || month < 1 || month > 12 || day < 1)
		return (false);
	if (month == 2 && day == 29)
	{
		if (year % 400 != 0 || year % 100 == 0 || year % 4 != 0)
			return (false);
	}
	if (day > dayMonth[month - 1])
		return (false);
	return (true);
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
