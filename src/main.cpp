/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:44:17 by pbremond          #+#    #+#             */
/*   Updated: 2022/06/27 21:25:40 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iterator>
#include <string>
// #include <type_traits>
#include <vector>
#include "vector.hpp"

#define NAMESP	ft

void	newtest(void)
{
	static int	i(1);

	std::cout << "\e[0;30;47m===============TEST " << i++ << "===============\e[0m"
		<< std::endl;
}

template < class T >
void	fillWithAscii(T container)
{
	char	truc = '0';
	for (typename T::iterator itr = container.begin(); itr != container.end(); ++itr)
		*itr = truc++;
}

template < class T >
void	printContainer(std::string const& name, T container)
{
	std::cout << name << ": " << std::endl;
	for (typename T::const_iterator itr = container.begin(); itr != container.end(); ++itr)
		std::cout << "- " << *itr << std::endl;
}

int	main(void)
{
	try
	{
		NAMESP::vector<char>	test(9, 'a');
		NAMESP::vector<char>	test2(8);
		std::cout << "Capacity: " << test.capacity() << std::endl;
		test.assign(test.begin(), test.end());
		std::cout << "Capacity: " << test2.capacity() << std::endl;
		// test2.push_back('b');
		std::cout << "Capacity: " << test2.capacity() << std::endl;
		test2.insert(test2.begin(), '0');
		std::cout << "Capacity: " << test2.capacity() << std::endl;
		// std::cout << "prout " << sizeof(char) << std::endl;
		// test.reserve(ULLONG_MAX);
		// std::iterator_traits
	}
	catch (std::exception &e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}
	newtest();
	try
	{
		std::vector<char>	test(9, 'a');
		ft::vector<char>	test2(8);
		std::cout << "Capacity: " << test.capacity() << std::endl;
		test2.assign(test.begin(), test.end());
		std::cout << "Capacity: " << test2.capacity() << std::endl;
		// test2.push_back('b');
		std::cout << "Capacity: " << test2.capacity() << std::endl;
		// test.insert(test2.begin(), '0');
		test.insert(test.begin(), '0');
		test2.insert(test2.begin(), '0');
		std::cout << "Capacity: " << test2.capacity() << std::endl;
		// std::cout << "prout " << sizeof(char) << std::endl;
		// test.reserve(ULLONG_MAX);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}
	newtest();
	try
	{
		NAMESP::vector<char>	test(8, '0');

		char	truc = 'a';
		for (NAMESP::vector<char>::iterator itr = test.begin(); itr != test.end(); ++itr) {
			*itr = truc++;
			std::cout << *itr << std::endl;
		}
		std::cout << "---------------------------------" << std::endl;
		for (NAMESP::vector<char>::const_iterator itr = test.end() - 1; itr != test.begin() - 1; --itr)
			std::cout << (*itr) << std::endl;
		std::cout << "---------------------------------" << std::endl;
		test.push_back('j');
		test.insert(test.end() - 1, 'i');
		test.insert(test.begin(), '0');
		std::cout << "capacity: " << test.capacity() << std::endl;
		for (NAMESP::vector<char>::const_iterator itr = test.begin(); itr != test.end(); ++itr)
			std::cout << *itr << std::endl;
		std::cout << "begin: " << *test.begin() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}
	newtest();
	try
	{
		NAMESP::vector<char>	test(8, '-');
		NAMESP::vector<char>	test2;

		char	truc = '0';
		for (NAMESP::vector<char>::iterator itr = test.begin(); itr != test.end(); ++itr)
			std::cout << (*itr = truc++) << std::endl;
		test2.assign(test.begin(), test.end());
		std::cout << "------------" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	newtest();
	try
	{
		std::string			truc = "0123456789";
		NAMESP::vector<char>	test(truc.begin(), truc.end());

		fillWithAscii(test);
		NAMESP::vector<char>::iterator	itr1 = test.begin();
		// ft::vector<char>::iterator	itr2 = itr1 + 5;
		NAMESP::vector<char>::iterator	itr2 = 5 + itr1;
		std::cout << "itr1: " << *itr1 << '\n'
			<< "itr2: " << *itr2 << std::endl;
		
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}	
	newtest();
	try
	{
		NAMESP::vector<char>	test1(3, 'a');
		NAMESP::vector<char>	test2(3, 'b');

		printContainer("test1", test1);
		printContainer("test2", test2);
		std::swap(test1, test2);
		// using std::swap;
		// swap(test1, test2);
		printContainer("test1", test1);
		printContainer("test2", test2);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}	
	
	return (0);
}
