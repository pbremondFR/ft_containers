/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:46:05 by pbremond          #+#    #+#             */
/*   Updated: 2022/06/17 01:13:14 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include "../ft_iterator.hpp"

namespace ft
{

template < class T >
class __vector_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
{
	private:
		T	*_ptr;

	public:
		using typename ft::iterator<ft::random_access_iterator_tag, T>::pointer;
		using typename ft::iterator<ft::random_access_iterator_tag, T>::reference;
		using typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type;
		// typedef ptrdiff_t					difference_type;
		// typedef T							value_type;
		// typedef T*							pointer;
		// typedef T&							reference;
		// typedef random_access_iterator_tag	iterator_category;
		
		__vector_iterator(pointer ptr = NULL) : _ptr(ptr) {};

		reference			operator*() const	{ return (*_ptr); };
		pointer				operator->()		{ return (_ptr);  };

		__vector_iterator	&operator++()	{ ++_ptr; return (*this);							   };
		__vector_iterator	operator++(int)	{ __vector_iterator tmp = *this; ++_ptr; return (tmp); };
		__vector_iterator	&operator--()	{ --_ptr; return (*this);							   };
		__vector_iterator	operator--(int)	{ __vector_iterator tmp = *this; --_ptr; return (tmp); };

		__vector_iterator	operator+(difference_type delta) { return (__vector_iterator(_ptr + delta)); };
		__vector_iterator	operator-(difference_type delta) { return (__vector_iterator(_ptr - delta)); };

		bool				operator==(const __vector_iterator& rhs) { return (_ptr == rhs._ptr); };
		bool				operator!=(const __vector_iterator& rhs) { return (_ptr != rhs._ptr); };
};

template < class T >
class __vector_c_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
{
	private:
		T	*_ptr;

	public:
		using typename iterator<ft::random_access_iterator_tag, T>::pointer;
		using typename iterator<ft::random_access_iterator_tag, T>::reference;
		
		__vector_c_iterator(pointer ptr = NULL) : _ptr(ptr) {};
		__vector_c_iterator(__vector_iterator<T> src = NULL) : _ptr(src.operator->()) {};

		const reference		operator*() const { return (*_ptr); };
		pointer				operator->()	  { return (_ptr);  };
		__vector_c_iterator	&operator++()	{ ++_ptr; return (*this);								 };
		__vector_c_iterator	operator++(int)	{ __vector_c_iterator tmp = *this; ++_ptr; return (tmp); };
		bool				operator==(const __vector_c_iterator& rhs) { return (_ptr == rhs._ptr); };
		bool				operator!=(const __vector_c_iterator& rhs) { return (_ptr != rhs._ptr); };
};


template< class T, class Allocator = std::allocator<T> >
class vector
{
	public:
		typedef 			T							value_type;
		typedef 			Allocator					allocator_type;
		typedef typename	std::size_t					size_type;
		typedef typename	std::ptrdiff_t				difference_type;
		typedef 			value_type&					reference;
		typedef 			value_type const&			const_reference;
		typedef typename	Allocator::pointer			pointer;
		typedef typename	Allocator::const_pointer	const_pointer;
		typedef typename	ft::__vector_iterator<T>	iterator;
		typedef typename	ft::__vector_c_iterator<T>	const_iterator;

	public:
		explicit vector(const Allocator& alloc = Allocator());
		explicit vector(size_type count,
						const T& value = T(),
						const Allocator& alloc = Allocator());
		template<class InputIt>
		vector(InputIt first, InputIt last,
				const Allocator& alloc = Allocator());
		vector(const vector& other);
		vector &operator=(const vector& other);
		~vector();

		void	assign(size_type count, const T& value);
		template<class InputIt>
		void	assign(InputIt first, InputIt last);

		allocator_type	get_allocator() const;

	public:
		reference		at(size_type n);
		const_reference	at(size_type n) const;
		reference		operator[](size_type n)		  { return (_array[n]); };
		const_reference	operator[](size_type n) const { return (_array[n]); };
		reference		front()		  { return (_array[0]); };
		const_reference	front() const { return (_array[0]); };
		reference		back()		 { return (_array[_size - 1]); };
		const_reference	back() const { return (_array[_size - 1]); };
		T*				data()		 { return (_array); };
		const T*		data() const { return (_array); };

		bool		empty()		const { return (_size == 0);			};
		size_type	size()		const { return (_size);					};
		size_type	max_size()	const { return (_allocator.max_size());	};
		void		reserve(size_type new_cap);
		size_type	capacity()	const { return (_capacity);				};

		iterator		begin()		  { return (_itrBegin); };
		const_iterator	begin() const { return (_itrBegin); };
		iterator		end()	    { return (_itrEnd); };
		const_iterator	end() const { return (_itrEnd); };

		void		clear();
		iterator	insert(iterator pos, const T& value);
		void		insert(iterator pos, size_type count, const T& value);
		template<class InputIt>
		void		insert(iterator pos, InputIt first, InputIt last);
		iterator	erase(iterator pos);
		iterator	erase(iterator first, iterator last);
		void		push_back(const T& value);
		void		pop_back();
		void		resize(size_type count);
		void		swap(vector& other);

	private:
		static const bool	_verbose = false;

		allocator_type	_allocator;
		size_type		_init_size;

		T				*_array;
		size_type		_capacity;
		size_type		_size;
		// This might be fucking retarded. Yes, it allows not to construct
		// an iterator each time, but it's pretty spaghetti-y right now.
		iterator	_itrBegin;
		iterator	_itrEnd;
	
	private:
		void	_recalcIterators(bool begin, bool end);
		// helo
		
};

}

#include "ft_vector.tpp"
