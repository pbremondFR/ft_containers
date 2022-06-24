/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 06:44:44 by pbremond          #+#    #+#             */
/*   Updated: 2022/06/24 22:55:55 by pbremond         ###   ########.fr       */
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

template < class T, T v >
struct integral_constant {
	static const	T	value = v;

	typedef	T						value_type;
	typedef	integral_constant<T,v>	type;

	operator T() const { return (v); }
};

typedef integral_constant<bool, true>	true_type;
typedef integral_constant<bool, false>	false_type;

template < class T, class U >
struct is_same : false_type
{
};
 
template < class T >
struct is_same<T, T> : true_type
{
};

// is_integral declaration and specialisation
template <class T>	struct is_integral						: public false_type {};
template <>			struct is_integral<bool>				: public true_type {};
template <>			struct is_integral<char>				: public true_type {};
template <>			struct is_integral<unsigned char>		: public true_type {};
template <>			struct is_integral<wchar_t>				: public true_type {};
template <>			struct is_integral<char16_t>			: public true_type {};
template <>			struct is_integral<char32_t>			: public true_type {};
template <>			struct is_integral<short>				: public true_type {};
template <>			struct is_integral<unsigned short>		: public true_type {};
template <>			struct is_integral<int>					: public true_type {};
template <>			struct is_integral<unsigned int>		: public true_type {};
template <>			struct is_integral<long>				: public true_type {};
template <>			struct is_integral<unsigned long>		: public true_type {};
template <>			struct is_integral<long long>			: public true_type {};
template <>			struct is_integral<unsigned long long>	: public true_type {};
template <>			struct is_integral<__int128_t>			: public true_type {};
template <>			struct is_integral<__uint128_t>			: public true_type {};

// is_floating_point declaration and specialisation
template <class T>	struct is_floating_point				: public false_type {};
template <>			struct is_floating_point<float>			: public true_type {};
template <>			struct is_floating_point<double>		: public true_type {};
template <>			struct is_floating_point<long double>	: public true_type {};

template < class T >
struct is_fundamental
	: ft::integral_constant
	<
		bool,
		ft::is_integral<T>::value
		|| ft::is_floating_point<T>::value
	>
{};

// TODO
template < class T, class U >
struct is_convertible : false_type
{};

}
