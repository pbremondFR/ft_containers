/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:19:16 by pbremond          #+#    #+#             */
/*   Updated: 2022/09/11 16:26:45 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <map>

void	newtest(void)
{
	static int	i(1);

	std::cout << "\e[0;30;47m===============TEST " << i++ << "===============\e[0m"
		<< std::endl;
}

int	main(void)
{
	newtest();
	{
		std::map<int, int>	test;
		std::map<int, int>::iterator	it = test.begin();
		std::cout << it->first << std::endl;
		std::cout << it->second << std::endl;
	}
	newtest();
	{
		std::map<char, char>	test;
		std::map<char, char>::iterator	it = test.begin();
		std::cout << it->first << std::endl;
		std::cout << it->second << std::endl;
	}
	newtest();
	{
		std::map<int, int>	test;
		std::map<int, int>::iterator	it = test.begin();
		std::cout << it->first << std::endl;
		std::cout << it->second << std::endl;
		test.insert(std::make_pair(1, 1));
		std::cout << it->first << std::endl;
		std::cout << it->second << std::endl;
	}
	newtest();
	{ // Not value initialized !!!
		std::map<char, char>	test;
		std::map<char, char>::iterator	it = test.begin();
		std::cout << it->first << std::endl;
		std::cout << it->second << std::endl;
		test.insert(std::make_pair('a', 'a'));
		std::cout << it->first << std::endl;
		std::cout << it->second << std::endl;
	}
}
