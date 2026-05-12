/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:38:31 by mweghofe          #+#    #+#             */
/*   Updated: 2026/05/12 23:26:34 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <string>

class BitcoinExchange
{
  private:
	// container
	std::map<std::string, double> data_;
	// internal control
	void loadPriceData();
	void processInputData(const std::string&);
	// internal helpers
  public:
	// external control
	void execute(const std::string&);
	// OCF
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	~BitcoinExchange();
	BitcoinExchange& operator=(const BitcoinExchange& other);
};
