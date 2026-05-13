/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 09:44:41 by mweghofe          #+#    #+#             */
/*   Updated: 2026/05/13 11:45:22 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stack>

#ifndef DEBUG
# define DEBUG 0
#endif

class RPN
{
	private:
	// ---
	std::stack<int> stack_;
	void operation(char& c);
	public:
	// ---
	void execute(char*&);
	// ---
	RPN();
	RPN(const RPN&);
	~RPN();
	RPN& operator=(const RPN&);
};
