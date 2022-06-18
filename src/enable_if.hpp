/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 06:44:44 by pbremond          #+#    #+#             */
/*   Updated: 2022/06/17 13:46:26 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{

template < bool B, class T = void >
struct enable_if
{
};
 
template < class T >
struct enable_if<true, T>
{
	typedef	T	type;
};

template <class T, T v>
struct integral_constant {
  static const	T	value = v;

  typedef	T						value_type;
  typedef	integral_constant<T,v> type;

  operator T() const { return (v); }
};

template < class T, class U >
struct is_same : ft::integral_constant<bool, false>
{
};
 
template<class T>
struct is_same<T, T> : ft::integral_constant<bool, true>
{
};

}
