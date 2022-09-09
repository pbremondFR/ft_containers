/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:44:17 by pbremond          #+#    #+#             */
/*   Updated: 2022/09/09 21:00:52 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include <vector>
#include "vector.hpp"

#include <utility>
#include "utility.hpp"

#include <map>
#include "map.hpp"

#include "optional.hpp"

#ifndef NAMESP
# define NAMESP	ft
#endif

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
void	printContainer(std::string const& name, T const& container)
{
	std::cout << name << ": " << std::endl;
	for (typename T::const_iterator itr = container.begin(); itr != container.end(); ++itr)
		std::cout << "- " << *itr << std::endl;
}

template < class T >
void	printMap(std::string const& name, T const& container)
{
	std::cout << name << ": " << std::endl;
	for (typename T::const_iterator itr = container.begin(); itr != container.end(); ++itr)
		std::cout << "- " << itr->first << " | " << itr->second << std::endl;
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
	newtest();
	try
	{
		NAMESP::vector<char>	test1(10, 'o');
		NAMESP::vector<char>	test2(test1);

		test1.erase(test1.begin() + 1, test1.end() - 1);
		printContainer("test1", test1);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	newtest();
	try
	{
		NAMESP::pair<int, char>		pair1('a', 'a');
		NAMESP::pair<int, char>		pair2(pair1);
		
		std::cout << "First: " << pair1.first << '\n'
			<< "Second: " << pair1.second << std::endl;
		std::cout << (pair1 == pair2 ? "TRUE" : "FALSE") << std::endl;
		pair2.first++;
		std::cout << (pair1 == pair2 ? "TRUE" : "FALSE") << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	newtest();
	{
		ft::optional<int>	opt(21);
		std::cout << "Has value: " << opt.has_value() << std::endl;
		std::cout << "value_or(-42): " << opt.value_or(-42) << std::endl;
		opt = ft::nullopt;
		std::cout << "Has value: " << opt.has_value() << std::endl;
		opt.reset();
		std::cout << "Has value: " << opt.has_value() << std::endl;
	}
	newtest();
	{
		ft::optional<std::string>	opt("Hello world");
		std::cout << "Has value: " << opt.has_value() << std::endl;
		std::cout << "value_or(\"merde\"): " << opt.value_or("merde") << std::endl;
		opt = ft::nullopt;
		std::cout << "Has value: " << opt.has_value() << std::endl;
		opt.reset();
		std::cout << "Has value: " << opt.has_value() << std::endl;
	}
	newtest();
	{ // Just random tests, not needed by subject
		ft::optional<std::string*>	opt = new std::string("Hello world");
		std::cout << "Has value: " << opt.has_value() << std::endl;
		if (opt)
			std::cout << "value(): " << opt.value() << std::endl;
		delete *opt;
		opt = ft::nullopt;
		std::cout << "Has value: " << opt.has_value() << std::endl;
		opt.reset();
		std::cout << "Has value: " << opt.has_value() << std::endl;
	}
	newtest();
	{
		NAMESP::map<int, char>	test;
		test.insert(NAMESP::make_pair(42, 'a'));
		NAMESP::map<int, char>::iterator it = test.begin();
		std::cout << (*it).second << std::endl;
		std::cout << it.operator->() << std::endl;
		std::cout << it.operator*().first << std::endl;
		it->second = 'b';
		std::cout << it->second << std::endl;
		// it->first = 'b';
	}
	newtest();
	{
		NAMESP::map<int, std::string>	test;
		test.insert(NAMESP::make_pair(30, "30"));
		test.insert(NAMESP::make_pair(20, "20"));
		test.insert(NAMESP::make_pair(70, "70"));
		test.insert(NAMESP::make_pair(10, "10"));
		test.insert(NAMESP::make_pair(50, "50"));
		test.insert(NAMESP::make_pair(40, "40"));
		test.insert(NAMESP::make_pair(60, "60"));
		
		printMap("map", test);
	}
	newtest();
	{
		NAMESP::map<int, std::string>	test;
		test.insert(NAMESP::make_pair(10, "10"));
		test.insert(NAMESP::make_pair(5, "5"));
		test.insert(NAMESP::make_pair(15, "15"));
		test.insert(NAMESP::make_pair(2, "2"));
		test.insert(NAMESP::make_pair(7, "7"));
		test.insert(NAMESP::make_pair(6, "6"));
		test.insert(NAMESP::make_pair(8, "8"));
		
		printMap("map - test", test);
		// test.debug_printByLevel();

		// test.debug_leftRotate(5);

		printMap("map - test", test);
		// test.debug_printByLevel();

		// test.debug_rightRotate(7);

		printMap("map - test", test);
		// test.debug_printByLevel();
	}
	newtest();
	{
		NAMESP::map<int, std::string>	test;
		test.insert(NAMESP::make_pair(10, "10"));
		test.insert(NAMESP::make_pair(5, "5"));
		test.insert(NAMESP::make_pair(15, "15"));
		test.insert(NAMESP::make_pair(2, "2"));
		test.insert(NAMESP::make_pair(7, "7"));
		test.insert(NAMESP::make_pair(6, "6"));
		test.insert(NAMESP::make_pair(8, "8"));
		test.insert(NAMESP::make_pair(1, "1"));
		test.insert(NAMESP::make_pair(0, "0"));
		
		printMap("map - test", test);
		// test.debug_printByLevel();
		// test.debug_printFamily(10);
		// test.debug_printFamily(15);
	}
	newtest();
	{
		NAMESP::map<int, std::string>	test;
		test.insert(NAMESP::make_pair(10, "10"));
		test.insert(NAMESP::make_pair(5, "5"));
		test.insert(NAMESP::make_pair(15, "15"));
		test.insert(NAMESP::make_pair(2, "2"));
		test.insert(NAMESP::make_pair(7, "7"));
		test.insert(NAMESP::make_pair(6, "6"));
		test.insert(NAMESP::make_pair(8, "8"));
		test.insert(NAMESP::make_pair(1, "1"));
		printMap("map - test", test);
		std::cout << test.insert(test.find(1), ft::make_pair(0, "0"))->first << std::endl;
		
		printMap("map - test", test);
		// test.debug_printByLevel();
		// test.debug_printFamily(10);
		// test.debug_printFamily(15);
	}
	newtest();
	{
		NAMESP::map<int, int>	test;
		test.insert(NAMESP::make_pair(1, 1));
		test.insert(NAMESP::make_pair(2, 2));
		test.insert(NAMESP::make_pair(3, 3));
		printMap("map - test", test);
	}
	return (0);
}
