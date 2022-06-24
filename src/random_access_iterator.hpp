/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:40:08 by pbremond          #+#    #+#             */
/*   Updated: 2022/06/24 18:25:00 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"

namespace ft
{

template < class T >
class c_random_access_iterator;

template < class T >
class random_access_iterator : ft::iterator_traits<T*>
{
	protected:
		T*	_ptr;

	public:
		typedef typename	ft::iterator_traits<T*>	base;
		typedef				random_access_iterator		this_type;
		// typedef ptrdiff_t							difference_type;
		// typedef T									value_type;
		// typedef T*									pointer;
		// typedef T&									reference;
		// typedef std::random_access_iterator_tag     iterator_category;
		using typename		base::difference_type;
		using typename		base::value_type;
		using typename		base::pointer;
		using typename		base::reference;
		using typename		base::iterator_category;
		
		random_access_iterator(pointer ptr = NULL) : _ptr(ptr) {};
		random_access_iterator(random_access_iterator<T> const& src) : _ptr(src.operator->()) {};
		// random_access_iterator(random_access_iterator<T>& src) : _ptr(src.operator->()) {};
		// random_access_iterator(random_access_iterator<const T> src) : _ptr(src.operator->()) {};

		reference	operator* () 					{ return (*_ptr); };
		pointer		operator->() 					{ return (_ptr);  };
		reference	operator[](difference_type n)  { return (*(_ptr + n)); };
		const reference	operator* () const					{ return (*_ptr); };
		const pointer	operator->() const					{ return (_ptr);  };
		const reference	operator[](difference_type n) const { return (*(_ptr + n)); };

		operator c_random_access_iterator<T>() { return (c_random_access_iterator<T>(_ptr)); };

		this_type&	operator++()	{ ++_ptr; return (*this);					   };
		this_type	operator++(int)	{ this_type tmp = *this; ++_ptr; return (tmp); };
		this_type&	operator--()	{ --_ptr; return (*this);					   };
		this_type	operator--(int)	{ this_type tmp = *this; --_ptr; return (tmp); };

		this_type&	operator+=(difference_type n)	{ _ptr += n; return (*this); };
		this_type&	operator-=(difference_type n)	{ _ptr -= n; return (*this); };

		this_type	operator+(difference_type rhs) const	 { return (this_type(_ptr + rhs)); };
		this_type	operator-(difference_type rhs) const	 { return (this_type(_ptr - rhs)); };
		difference_type		operator-(this_type delta) const { return (difference_type(_ptr - delta._ptr)); };

		inline bool		operator==(const this_type& rhs) const { return (_ptr == rhs._ptr); };
		inline bool		operator!=(const this_type& rhs) const { return (_ptr != rhs._ptr); };
		inline bool		operator> (const this_type& rhs) const { return (_ptr > rhs._ptr);  };
		inline bool		operator< (const this_type& rhs) const { return (_ptr < rhs._ptr);  };
		inline bool		operator>=(const this_type& rhs) const { return (_ptr >= rhs._ptr); };
		inline bool		operator<=(const this_type& rhs) const { return (_ptr <= rhs._ptr); };
};

template < class T >
random_access_iterator<T>	operator+(typename random_access_iterator<T>::difference_type lhs,
	random_access_iterator<T> const& rhs)
{
	return (rhs + lhs);
}

// template < class T>
// class c_random_access_iterator : ft::random_access_iterator<const T>
// {

// };

// template < class T >
// c_random_access_iterator<T>	operator+(typename c_random_access_iterator<T>::difference_type lhs,
// 	c_random_access_iterator<T> const& rhs)
// {
// 	return (rhs + lhs);
// }

template < class T >
class c_random_access_iterator : ft::iterator_traits<const T*>
{
	protected:
		const T*	_ptr;

	public:
		typedef typename	ft::iterator_traits<const T*>	base;
		typedef				c_random_access_iterator		this_type;
		// typedef ptrdiff_t							difference_type;
		// typedef T									value_type;
		// typedef T*									pointer;
		// typedef T&									reference;
		// typedef std::random_access_iterator_tag     iterator_category;
		using typename		base::difference_type;
		using typename		base::value_type;
		using typename		base::pointer;
		using typename		base::reference;
		using typename		base::iterator_category;
		
		c_random_access_iterator(pointer ptr = NULL) : _ptr(ptr) {};
		// random_access_iterator(const random_access_iterator<T>& src) : _ptr(src.operator->()) {};
		c_random_access_iterator(c_random_access_iterator<const T> const& src) : _ptr(src.operator->()) {};
		c_random_access_iterator(random_access_iterator<T> const& src) : _ptr(src.operator->()) {};

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

		inline bool		operator==(const this_type& rhs) const { return (_ptr == rhs._ptr); };
		inline bool		operator!=(const this_type& rhs) const { return (_ptr != rhs._ptr); };
		inline bool		operator> (const this_type& rhs) const { return (_ptr > rhs._ptr);  };
		inline bool		operator< (const this_type& rhs) const { return (_ptr < rhs._ptr);  };
		inline bool		operator>=(const this_type& rhs) const { return (_ptr >= rhs._ptr); };
		inline bool		operator<=(const this_type& rhs) const { return (_ptr <= rhs._ptr); };
};

template < class T >
c_random_access_iterator<T>	operator+(typename c_random_access_iterator<T>::difference_type lhs,
	c_random_access_iterator<T> const& rhs)
{
	return (rhs + lhs);
}

template < class T >
bool	operator!=(random_access_iterator<T> const& lhs, c_random_access_iterator<T> const& rhs)
{
	return (lhs.operator->() != rhs.operator->());
}

template < class T >
bool	operator!=(c_random_access_iterator<T> const& lhs, random_access_iterator<T> const& rhs)
{
	return (lhs.operator->() != rhs.operator->());
}

template < class T >
bool	operator==(random_access_iterator<T> const& lhs, c_random_access_iterator<T> const& rhs)
{
	return (lhs.operator->() == rhs.operator->());
}

template < class T >
bool	operator==(c_random_access_iterator<T> const& lhs, random_access_iterator<T> const& rhs)
{
	return (lhs.operator->() == rhs.operator->());
}

template < class T >
bool	operator<=(random_access_iterator<T> const& lhs, c_random_access_iterator<T> const& rhs)
{
	return (lhs.operator->() <= rhs.operator->());
}

template < class T >
bool	operator<=(c_random_access_iterator<T> const& lhs, random_access_iterator<T> const& rhs)
{
	return (lhs.operator->() <= rhs.operator->());
}

template < class T >
bool	operator>=(random_access_iterator<T> const& lhs, c_random_access_iterator<T> const& rhs)
{
	return (lhs.operator->() >= rhs.operator->());
}

template < class T >
bool	operator>=(c_random_access_iterator<T> const& lhs, random_access_iterator<T> const& rhs)
{
	return (lhs.operator->() >= rhs.operator->());
}

template < class T >
bool	operator>(random_access_iterator<T> const& lhs, c_random_access_iterator<T> const& rhs)
{
	return (lhs.operator->() > rhs.operator->());
}

template < class T >
bool	operator>(c_random_access_iterator<T> const& lhs, random_access_iterator<T> const& rhs)
{
	return (lhs.operator->() > rhs.operator->());
}

template < class T >
bool	operator<(random_access_iterator<T> const& lhs, c_random_access_iterator<T> const& rhs)
{
	return (lhs.operator->() < rhs.operator->());
}

template < class T >
bool	operator<(c_random_access_iterator<T> const& lhs, random_access_iterator<T> const& rhs)
{
	return (lhs.operator->() < rhs.operator->());
}

}
