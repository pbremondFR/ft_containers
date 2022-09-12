/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 09:03:22 by pbremond          #+#    #+#             */
/*   Updated: 2022/09/12 17:26:22 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{

// NOTE: Copy constructor and copy assignment operator are implicit in C++98 standard.
// See https://en.cppreference.com/w/cpp/utility/pair
template < class T1, class T2 >
struct pair
{
	typedef	T1	first_type;
	typedef	T2	second_type;
	
	T1	first;
	T2	second;

	pair() : first(T1()), second(T2()) {}
	pair(T1 const& a, T2 const& b) : first(a), second(b) {}
	template<class U1, class U2>
	pair(pair<U1, U2> const& src) : first(src.first), second(src.second) {}
};

template < class T1, class T2 >
ft::pair<T1, T2>	make_pair(T1 a, T2 b)
{
	return (pair<T1, T2>(a, b));
}

template < class T1, class T2 >
bool operator==(ft::pair<T1,T2> const& lhs, ft::pair<T1,T2> const& rhs)
{
	return (lhs.first == rhs.first && lhs.second == rhs.second);
}

template < class T1, class T2 >
bool operator!=(ft::pair<T1,T2> const& lhs, ft::pair<T1,T2> const& rhs)
{
	return (!(lhs == rhs));
}

template < class T1, class T2 >
bool operator< (ft::pair<T1,T2> const& lhs, ft::pair<T1,T2> const& rhs)
{
	return (lhs.first < rhs.first
		|| (!(rhs.first < lhs.first) && lhs.second < rhs.second));
}

template < class T1, class T2 >
bool operator> (ft::pair<T1,T2> const& lhs, ft::pair<T1,T2> const& rhs)
{
	return (rhs < lhs);
}

template < class T1, class T2 >
bool operator<=(ft::pair<T1,T2> const& lhs, ft::pair<T1,T2> const& rhs)
{
	return (!(rhs < lhs));
}

template < class T1, class T2 >
bool operator>=(ft::pair<T1,T2> const& lhs, ft::pair<T1,T2> const& rhs)
{
	return (!(lhs < rhs));
}

}
