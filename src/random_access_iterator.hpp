/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:40:08 by pbremond          #+#    #+#             */
/*   Updated: 2022/06/29 08:39:44 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"

namespace ft
{

template < class T >
class c_random_access_iterator;

template < class Tp >
class random_access_iterator
{
	private:
		typedef 	iterator_traits<Tp>		traits;

	protected:
		Tp	_ptr;

	public:
		typedef				random_access_iterator		this_type;
		typedef 			Tp							iterator_type;

		typedef typename	traits::difference_type		difference_type;
		typedef typename	traits::value_type			value_type;
		typedef typename	traits::pointer				pointer;
		typedef typename	traits::reference			reference;
		typedef typename	traits::iterator_category	iterator_category;
		
		random_access_iterator(pointer ptr = NULL) : _ptr(ptr) {};
		template <class Iter>
		random_access_iterator(random_access_iterator<Iter> const& src) : _ptr(src.operator->()) {};
		// template <class Iter>
		// this_type&	operator=(random_access_iterator<Iter> const& src) { _ptr = src.operator->(); return (*this); }

		reference	operator* () const					{ return (*_ptr); };
		pointer		operator->() const					{ return (_ptr);  };
		reference	operator[](difference_type n) const { return (*(_ptr + n)); };

		this_type&	operator++()	{ ++_ptr; return (*this);					   };
		this_type	operator++(int)	{ this_type tmp = *this; ++_ptr; return (tmp); };
		this_type&	operator--()	{ --_ptr; return (*this);					   };
		this_type	operator--(int)	{ this_type tmp = *this; --_ptr; return (tmp); };

		this_type&	operator+=(difference_type n)	{ _ptr += n; return (*this); };
		this_type&	operator-=(difference_type n)	{ _ptr -= n; return (*this); };

		this_type	operator+(difference_type rhs) const	 { return (this_type(_ptr + rhs)); };
		this_type	operator-(difference_type rhs) const	 { return (this_type(_ptr - rhs)); };
		difference_type		operator-(this_type delta) const { return (difference_type(_ptr - delta._ptr)); };
};

template <class Iter1, class Iter2>
typename random_access_iterator<Iter1>::difference_type
	operator- ( random_access_iterator<Iter1> const& lhs,
				random_access_iterator<Iter2> const& rhs)
{
	return (lhs.operator->() - rhs.operator->());
}

template < class T >
random_access_iterator<T>	operator+(typename random_access_iterator<T>::difference_type n,
	random_access_iterator<T> const& rhs)
{
	return (rhs + n);
}

template < class Iter1, class Iter2 >
bool	operator==(random_access_iterator<Iter1> const& lhs, random_access_iterator<Iter2> const& rhs)
{
	return (lhs.operator->() == rhs.operator->());
}

template < class Iter1, class Iter2 >
bool	operator!=(random_access_iterator<Iter1> const& lhs, random_access_iterator<Iter2> const& rhs)
{
	return (lhs.operator->() != rhs.operator->());
}

template < class Iter1, class Iter2 >
bool	operator<=(random_access_iterator<Iter1> const& lhs, random_access_iterator<Iter2> const& rhs)
{
	return (lhs.operator->() <= rhs.operator->());
}

template < class Iter1, class Iter2 >
bool	operator>=(random_access_iterator<Iter1> const& lhs, random_access_iterator<Iter2> const& rhs)
{
	return (lhs.operator->() >= rhs.operator->());
}

template < class Iter1, class Iter2 >
bool	operator<(random_access_iterator<Iter1> const& lhs, random_access_iterator<Iter2> const& rhs)
{
	return (lhs.operator->() < rhs.operator->());
}

template < class Iter1, class Iter2 >
bool	operator>(random_access_iterator<Iter1> const& lhs, random_access_iterator<Iter2> const& rhs)
{
	return (lhs.operator->() > rhs.operator->());
}

}
