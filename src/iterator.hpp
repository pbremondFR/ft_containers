/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:27:37 by pbremond          #+#    #+#             */
/*   Updated: 2022/06/22 22:48:51 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// #include <memory>
#include <stddef.h>

namespace ft
{

// struct input_iterator_tag {};
// struct output_iterator_tag {};
// struct forward_iterator_tag			: public input_iterator_tag {};
// struct bidirectional_iterator_tag	: public forward_iterator_tag {};
// struct random_access_iterator_tag	: public bidirectional_iterator_tag {};

// template<class Iterator>
// struct iterator_traits
// {
// 	typedef typename Iterator::difference_type		difference_type;
// 	typedef typename Iterator::value_type			value_type;
// 	typedef typename Iterator::pointer				pointer;
// 	typedef typename Iterator::reference			reference;
// 	typedef typename Iterator::iterator_category	iterator_category;
// };

// template<class T>
// struct iterator_traits<T*>
// {
// 	typedef ptrdiff_t					difference_type;
// 	typedef T							value_type;
// 	typedef T*							pointer;
// 	typedef T&							reference;
// 	typedef random_access_iterator_tag 	iterator_category;
// };

// template<class T>
// struct iterator_traits<const T*>
// {
// 	typedef ptrdiff_t					difference_type;
// 	typedef T							value_type;
// 	typedef T const*					pointer;
// 	typedef T const&					reference;
// 	typedef random_access_iterator_tag	iterator_category;
// };

template < class _Category, class T, class _Distance = ptrdiff_t,
	class _Pointer = T*, class _Reference = T& >
struct iterator
{
	typedef T			value_type;
	typedef _Distance	difference_type;
	typedef _Pointer	pointer;
	typedef _Reference	reference;
	typedef _Category	iterator_category;

	// iterator(pointer ptr) : _ptr(ptr) {};

	// reference	operator*() const	{ return (*_ptr); };
	// pointer		operator->()		{ return (_ptr);  };
	// iterator	&operator++()		{ return (*(++_ptr));						  };
	// iterator	operator++(int)		{ iterator tmp = *this; ++_ptr; return (tmp); };
	// bool		operator==(const iterator& rhs) { return (_ptr == rhs._ptr); };
	// bool		operator!=(const iterator& rhs) { return (_ptr != rhs._ptr); };

	// private:
	// 	pointer*	_ptr;
};

}
