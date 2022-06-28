/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 05:19:12 by pbremond          #+#    #+#             */
/*   Updated: 2022/06/28 06:35:18 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"

namespace ft
{

template < class Iterator >
class reverse_iterator
	: public iterator
	<
		typename iterator_traits<Iterator>::iterator_category,
		typename iterator_traits<Iterator>::value_type,
		typename iterator_traits<Iterator>::difference_type,
		typename iterator_traits<Iterator>::pointer,
		typename iterator_traits<Iterator>::reference
	>
{
	private:
		typedef	iterator
		<
			typename iterator_traits<Iterator>::iterator_category,
			typename iterator_traits<Iterator>::value_type,
			typename iterator_traits<Iterator>::difference_type,
			typename iterator_traits<Iterator>::pointer,
			typename iterator_traits<Iterator>::reference
		>					base_t;
		typedef	reverse_iterator	this_type;
	protected:
		Iterator	_itCurrent;

	public:
		typedef			Iterator	iterator_type;
		using typename	base_t::iterator_category;
		using typename	base_t::value_type;
		using typename	base_t::difference_type;
		using typename	base_t::pointer;
		using typename	base_t::reference;

		reverse_iterator(pointer ptr = NULL) : _itCurrent(ptr) {}
		explicit reverse_iterator(iterator_type src) : _itCurrent(src) {}
		template <class Iter>
		reverse_iterator(reverse_iterator<Iter> const& src) : _itCurrent(src.base()) {}

		iterator_type	base() const { return (_itCurrent); }
		
		reference	operator* () const { return (*(_itCurrent - 1)); }
		pointer		operator->() const { return (&(operator*()));    }
		reference	operator[](difference_type n) const { return (*(_itCurrent - 1 - n)); }
		
		this_type&	operator++()	{ --_itCurrent; return (*this);						 };
		this_type	operator++(int)	{ this_type tmp = *this; --_itCurrent; return (tmp); };
		this_type&	operator--()	{ ++_itCurrent; return (*this);						 };
		this_type	operator--(int)	{ this_type tmp = *this; ++_itCurrent; return (tmp); };

		this_type	operator+(difference_type n) const { return (this_type(_itCurrent - n)); }
		this_type	operator-(difference_type n) const { return (this_type(_itCurrent + n)); }

		this_type&	operator+=(difference_type n) { _itCurrent -= n; return (*this); }
		this_type&	operator-=(difference_type n) { _itCurrent += n; return (*this); }
};

/* ************************************************************************** */
/*                           OUT-OF-CLASS OPERATORS                           */
/* ************************************************************************** */

template <class Iterator>
reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
	reverse_iterator<Iterator> const& rev_it)
{
	return (rev_it + n);
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type
	operator- ( reverse_iterator<Iterator> const& lhs,
				reverse_iterator<Iterator> const& rhs)
{
	return (rhs.base() - lhs.base());
}

/* ************************************************************************** */
/*                            RELATIONAL OPERATORS                            */
/* ************************************************************************** */

template <class Iterator>
bool operator==(const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() == rhs.base());
}

template <class Iterator>
bool operator!=(const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() != rhs.base());
}

template <class Iterator>
bool operator< (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() < rhs.base());
}

template <class Iterator>
bool operator> (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() > rhs.base());
}

template <class Iterator>
bool operator<=(const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() <= rhs.base());
}

template <class Iterator>
bool operator>=(const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() >= rhs.base());
}

}
