/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:46:05 by pbremond          #+#    #+#             */
/*   Updated: 2022/06/27 20:04:27 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include "iterator.hpp"
#include "type_traits.hpp"
#include "random_access_iterator.hpp"

namespace ft
{

// template < class T >
// class __vector_iterator : public ft::iterator<std::random_access_iterator_tag, T>
// {
// 	protected:
// 		T	*_ptr;

// 	public:
// 		typedef typename	ft::iterator<std::random_access_iterator_tag, T>	base;
// 		using typename	base::difference_type;
// 		using typename	base::value_type;
// 		using typename	base::pointer;
// 		using typename	base::reference;
// 		using typename	base::iterator_category;
		
// 		__vector_iterator(pointer ptr = NULL) : _ptr(ptr) {};

// 		reference	operator* ()				  { return (*_ptr); };
// 		pointer		operator->()				  { return (_ptr);  };
// 		reference	operator[](difference_type n) { return (*(_ptr + n)); };

// 		__vector_iterator&	operator++()	{ ++_ptr; return (*this);							   };
// 		__vector_iterator	operator++(int)	{ __vector_iterator tmp = *this; ++_ptr; return (tmp); };
// 		__vector_iterator&	operator--()	{ --_ptr; return (*this);							   };
// 		__vector_iterator	operator--(int)	{ __vector_iterator tmp = *this; --_ptr; return (tmp); };

// 		__vector_iterator&	operator+=(difference_type n)	{ _ptr += n; return (*this); };
// 		__vector_iterator&	operator-=(difference_type n)	{ _ptr -= n; return (*this); };

// 		__vector_iterator	operator+(difference_type rhs) const	 { return (__vector_iterator(_ptr + rhs)); };
// 		__vector_iterator	operator-(difference_type rhs) const	 { return (__vector_iterator(_ptr - rhs)); };
// 		difference_type		operator-(__vector_iterator delta) const { return (difference_type(_ptr - delta._ptr)); };

// 		inline bool		operator==(const __vector_iterator& rhs) const { return (_ptr == rhs._ptr); };
// 		inline bool		operator!=(const __vector_iterator& rhs) const { return (_ptr != rhs._ptr); };
// 		inline bool		operator> (const __vector_iterator& rhs) const { return (_ptr > rhs._ptr);  };
// 		inline bool		operator< (const __vector_iterator& rhs) const { return (_ptr < rhs._ptr);  };
// 		inline bool		operator>=(const __vector_iterator& rhs) const { return (_ptr >= rhs._ptr); };
// 		inline bool		operator<=(const __vector_iterator& rhs) const { return (_ptr <= rhs._ptr); };
// };

// template < class T >
// __vector_iterator<T>	operator+(typename __vector_iterator<T>::difference_type lhs, __vector_iterator<T> const& rhs)
// {
// 	return (rhs + lhs);
// }

// template < class T >
// class __vector_c_iterator : public __vector_iterator<T>
// {
// 	public:
// 		typedef typename	ft::__vector_iterator<T>		base;
// 		// typedef				const typename base::pointer	pointer;
// 		// typedef 			const typename base::reference	reference;
// 		using typename		base::iterator_category;
// 		using typename		base::difference_type;
// 		using typename		base::value_type;
// 		using typename		base::pointer;
// 		using typename		base::reference;

// 		__vector_c_iterator(pointer ptr = NULL) : __vector_iterator<T>(ptr) {};
// 		__vector_c_iterator(__vector_iterator<T> src) : __vector_iterator<T>(src) {};
		
// 		const reference	operator*() const	{ std::cout << "MERDE\n"; return (base::operator*()); };
// 		// const pointer	operator->() const  { return (base::_ptr);  };
// };

// template < class T >
// class __vector_c_iterator : public ft::iterator<std::random_access_iterator_tag, T>
// {
// 	protected:
// 		T	*_ptr;

// 	public:
// 		typedef typename	ft::iterator<std::random_access_iterator_tag, T>	base;
// 		using typename	base::difference_type;
// 		using typename	base::value_type;
// 		using typename	base::pointer;
// 		using typename	base::reference;
// 		using typename	base::iterator_category;
		
// 		__vector_c_iterator(pointer ptr = NULL) : _ptr(ptr) {};
// 		__vector_c_iterator(__vector_iterator<T>& src) : _ptr(src.operator->()) {};
// 		__vector_c_iterator(__vector_iterator<T> src) : _ptr(src.operator->()) {};

// 		const reference	operator* () const			  { return (*_ptr); };
// 		const pointer	operator->() const			  { return (_ptr);  };
// 		const reference	operator[](difference_type n) { return (*(_ptr + n)); };

// 		__vector_c_iterator&	operator++()	{ ++_ptr; return (*this);							   };
// 		__vector_c_iterator	operator++(int)	{ __vector_c_iterator tmp = *this; ++_ptr; return (tmp); };
// 		__vector_c_iterator&	operator--()	{ --_ptr; return (*this);							   };
// 		__vector_c_iterator	operator--(int)	{ __vector_c_iterator tmp = *this; --_ptr; return (tmp); };

// 		__vector_c_iterator&	operator+=(difference_type n)	{ _ptr += n; return (*this); };
// 		__vector_c_iterator&	operator-=(difference_type n)	{ _ptr -= n; return (*this); };

// 		__vector_c_iterator	operator+(difference_type rhs) const	 { return (__vector_c_iterator(_ptr + rhs)); };
// 		__vector_c_iterator	operator-(difference_type rhs) const	 { return (__vector_c_iterator(_ptr - rhs)); };
// 		difference_type		operator-(__vector_c_iterator delta) const { return (difference_type(_ptr - delta._ptr)); };

// 		inline bool		operator==(const __vector_c_iterator& rhs) const { return (_ptr == rhs._ptr); };
// 		inline bool		operator!=(const __vector_c_iterator& rhs) const { return (_ptr != rhs._ptr); };
// 		inline bool		operator> (const __vector_c_iterator& rhs) const { return (_ptr > rhs._ptr);  };
// 		inline bool		operator< (const __vector_c_iterator& rhs) const { return (_ptr < rhs._ptr);  };
// 		inline bool		operator>=(const __vector_c_iterator& rhs) const { return (_ptr >= rhs._ptr); };
// 		inline bool		operator<=(const __vector_c_iterator& rhs) const { return (_ptr <= rhs._ptr); };
// };

template< class T, class Allocator = std::allocator<T> >
class vector
{
	public:
		typedef 			T											value_type;
		typedef 			Allocator									allocator_type;
		typedef typename	std::size_t									size_type;
		typedef typename	std::ptrdiff_t								difference_type;
		typedef 			value_type&									reference;
		typedef 			value_type const&							const_reference;
		typedef typename	Allocator::pointer							pointer;
		typedef typename	Allocator::const_pointer					const_pointer;
		typedef typename	ft::random_access_iterator<T>			iterator;
		typedef typename	ft::c_random_access_iterator<T>	const_iterator;

	public:
		explicit vector(const Allocator& alloc = Allocator());
		explicit vector(size_type count,
						const T& value = T(),
						const Allocator& alloc = Allocator());
		template<class InputIt>
		vector( InputIt first,
				InputIt last,
				const Allocator& alloc = Allocator(),
				typename enable_if< !is_fundamental<InputIt>::value, int >::type = 0);
		vector(const vector& other);
		vector &operator=(const vector& other);
		~vector();

		void	assign(size_type count, const T& value);
		template<class InputIt>
		typename ft::enable_if <
			!ft::is_fundamental<InputIt>::value,
			void
		>::type	assign(InputIt first, InputIt last);

		allocator_type	get_allocator() const { return (_allocator); };

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

		inline const_iterator	begin() const { return (const_iterator(_array)); };
		inline iterator			begin()		  { return (_itrBegin); };
		inline const_iterator	end() const { return (const_iterator(_array + _size)); };
		inline iterator			end()	    { return (_itrEnd); };

		void		clear();
		iterator	insert(iterator pos, const T& value);
		void		insert(iterator pos, size_type count, const T& value);
		template<class InputIt>
		typename std::enable_if <
			!ft::is_fundamental<InputIt>::value,
			void
		>::type		insert(iterator pos, InputIt first, InputIt last);
		iterator	erase(iterator pos);
		iterator	erase(iterator first, iterator last);
		void		push_back(const T& value);
		void		pop_back();
		void		resize(size_type count, T value = T());
		void		swap(vector& other);

	private:
		static const bool	_verbose = false;

		allocator_type	_allocator;
		size_type		_init_size;

		T			*_array;
		size_type	_capacity;
		size_type	_size;

		iterator	_itrBegin;
		iterator	_itrEnd;
	
	private:
		void	_doubleCapacity();
		void	_recalcIterators(bool begin, bool end);
		void	_shallowCopyNoDealloc(vector& other);
		
};

}

#include "vector.tpp"
