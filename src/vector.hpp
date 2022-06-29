/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:46:05 by pbremond          #+#    #+#             */
/*   Updated: 2022/06/29 08:42:48 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include <iostream>
#include "iterator.hpp"
#include "type_traits.hpp"
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "algorithm.hpp"

namespace ft
{

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
		typedef typename	ft::random_access_iterator<pointer>			iterator;
		typedef typename	ft::random_access_iterator<const_pointer>	const_iterator;
		typedef typename	ft::reverse_iterator<iterator>				reverse_iterator;
		typedef typename	ft::reverse_iterator<const_iterator>		const_reverse_iterator;

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

		inline const_iterator	begin() const { return (const_iterator(_itrBegin)); };
		inline iterator			begin()		  { return (_itrBegin); };
		inline const_iterator	end() const { return (const_iterator(_itrEnd)); };
		inline iterator			end()	    { return (_itrEnd); };

		inline const_reverse_iterator	rbegin() const { return (const_reverse_iterator(_array + _size)); };
		inline reverse_iterator			rbegin()	   { return (_array + _size); };
		inline const_reverse_iterator	rend() const { return (const_reverse_iterator(_array)); };
		inline reverse_iterator			rend()	     { return (_array); };

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

template < class T, class Allocator >
bool	operator==(ft::vector<T, Allocator> const& lhs, ft::vector<T, Allocator> const& rhs)
{
	if (lhs.size() != rhs.size())
		return (false);
	else
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template < class T, class Allocator >
bool	operator!=(ft::vector<T, Allocator> const& lhs, ft::vector<T, Allocator> const& rhs)
{
	return (!(lhs == rhs));
}

template < class T, class Allocator >
bool	operator<(ft::vector<T, Allocator> const& lhs, ft::vector<T, Allocator> const& rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template < class T, class Allocator >
bool	operator>(ft::vector<T, Allocator> const& lhs, ft::vector<T, Allocator> const& rhs)
{
	return (rhs < lhs);
}

template < class T, class Allocator >
bool	operator<=(ft::vector<T, Allocator> const& lhs, ft::vector<T, Allocator> const& rhs)
{
	return (!(rhs < lhs));
}

template < class T, class Allocator >
bool	operator>=(ft::vector<T, Allocator> const& lhs, ft::vector<T, Allocator> const& rhs)
{
	return (!(lhs < rhs));
}

}

#include "vector.tpp"
