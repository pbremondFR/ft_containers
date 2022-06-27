/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 22:45:28 by pbremond          #+#    #+#             */
/*   Updated: 2022/06/27 23:40:08 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{

template < class InputIt1, class InputIt2 >
bool	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
{
	for (; first1 != last1; ++first1, ++first2)
		if (*first1 != *first2)
			return (false);
	return (true);
}

// Why the FUCK was this not implemented until C++14. Fuck you C++98, I'm implementing it.
template < class InputIt1, class InputIt2 >
bool	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
{
	for (; first1 != last1 && first2 != last2; ++first1, ++first2)
		if (*first1 != *first2)
			return (false);
	return (true);
}

template < class InputIt1, class InputIt2, class BinaryPredicate >
bool	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
{
	for (; first1 != last1; ++first1, ++first2)
		if (!p(first1, first2))
			return (false);
	return (true);
}

template < class InputIt1, class InputIt2, class BinaryPredicate >
bool	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2,
	BinaryPredicate p)
{
	for (; first1 != last1 && first2 != last2; ++first1, ++first2)
		if (!p(first1, first2))
			return (false);
	return (true);
}

template < class InputIt1, class InputIt2 >
bool	lexicographical_compare(InputIt1 first1, InputIt1 last1,
								InputIt2 first2, InputIt2 last2)
{
	while (first1 != last1 && first2 != last2)
	{
		if (*first1 < *first2)
			return (true);
		if (*first1 > *first2)
			return (false);
		++first1;
		++first2;
	}
	return (first1 == last1 && first2 != last2);
}

template < class InputIt1, class InputIt2, class Compare >
bool	lexicographical_compare(InputIt1 first1, InputIt1 last1,
								InputIt2 first2, InputIt2 last2,
								Compare comp)
{
	while (first1 != last1 && first2 != last2 && *first1 == *first2)
	{
		if (comp(*first1, *first2))
			return (true);
		if (comp(*first2, *first1))
			return (false);
		++first1;
		++first2;
	}
	return (first1 == last1 && first2 != last2);
}

}
