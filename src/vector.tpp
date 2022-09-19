/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:14:34 by pbremond          #+#    #+#             */
/*   Updated: 2022/09/19 21:37:18 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cassert>

// NOTE: Absolutely MORONIC use of std::memmove was in there. You're not in C anymore.
// Classes exist, and their instances cannot just be wildly flailed around.

#include "vector.hpp"

#define VEC_DEBUG_VERBOSE	false

template < class T, class Allocator >
ft::vector<T, Allocator>::vector(const Allocator& alloc): _allocator(alloc)
{
	_array = _allocator.allocate(0);
	_init_size = 0;
	_size = 0;
	_capacity = 0;
	_itrBegin = _array;
	_itrEnd = _array;
}

template < class T, class Allocator >
ft::vector<T, Allocator>::vector(size_type count,
								 const T& value,
								 const Allocator& alloc)
: _allocator(alloc)
{
	_init_size = count;
	_capacity = count;
	_size = count;
	_array = _allocator.allocate(_init_size);
	_itrBegin = _array;
	_itrEnd = _array + _size;
	for (size_type i = 0; i < count; ++i)
		_allocator.construct(_array + i, value);
}

template < class T, class Allocator >
template<class InputIt>
ft::vector<T, Allocator>::vector(InputIt first,
								 InputIt last,
								 const Allocator& alloc,
								 typename enable_if< !is_fundamental<InputIt>::value, int >::type)
: _allocator(alloc)
{
	_init_size = 0;
	_capacity = _init_size;
	_size = _init_size;
	_array = _allocator.allocate(_init_size);
	_itrBegin = _array;
	_itrEnd = _array + _size;

	this->assign(first, last);
}

template < class T, class Allocator >
ft::vector<T, Allocator>::vector(const ft::vector<T, Allocator>& src)
: _allocator(src._allocator)
{
	_init_size = src._capacity;
	_capacity = src._capacity;
	_array = _allocator.allocate(_init_size);
	_size = src._size;
	_itrBegin = _array;
	_itrEnd = _array;
	this->assign(src.begin(), src.end());
}

template < class T, class Allocator >
ft::vector<T, Allocator>	&ft::vector<T, Allocator>::operator=(const ft::vector<T, Allocator>& rhs)
{
	if (&rhs == this)
		return (*this);
	// for (size_type i = 0; i < _capacity; ++i)
	// 	_allocator.destroy(_array + i);
	_allocator.deallocate(_array, _init_size);
	_array = _allocator.allocate(rhs._capacity);
	_recalcIterators(true, true);
	_capacity = rhs._capacity;
	_init_size = rhs._capacity;
	_size = rhs._size;
	this->assign(rhs.begin(), rhs.end());
	return (*this);
}

template < class T, class Allocator >
ft::vector<T, Allocator>::~vector()
{
	for (size_type i = 0; i < _size; ++i)
		_allocator.destroy(_array + i);
	_allocator.deallocate(_array, _init_size);
}

template < class T, class Allocator >
void	ft::vector<T, Allocator>::assign(size_type count, const T& value)
{
	if (count > _capacity)
		this->reserve(count);
	for (size_type i = 0; i < count; ++i)
		_allocator.construct(_array + i, value);
	_size = count;
	_recalcIterators(false, true);
}

template < class T, class Allocator >
template < class InputIt >
typename ft::enable_if
<
	!ft::is_fundamental<InputIt>::value,
	void
>::type
ft::vector<T, Allocator>::assign(InputIt first, InputIt last)
{
	difference_type	newSize = std::distance<InputIt>(first, last); // FIXME

	if (static_cast<size_type>(newSize) > _capacity)
		this->reserve(newSize);
	size_type i = 0;
	for (InputIt itr = first; itr != last; ++itr, ++i)
		_allocator.construct(_array + i, *itr);
	_size = newSize;
	_recalcIterators(false, true);
}

/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */

template < class T, class Allocator >
typename ft::vector<T, Allocator>::reference	ft::vector<T, Allocator>::at(size_type n)
{
	if (n >= _size)
		throw (std::out_of_range("std::out_of_range"));
	return (_array[n]);
}

template < class T, class Allocator >
typename ft::vector<T, Allocator>::const_reference	ft::vector<T, Allocator>::at(size_type n) const
{
	if (n >= _size)
		throw (std::out_of_range("std::out_of_range"));
	return (_array[n]);
}

template < class T, class Allocator >
void	ft::vector<T, Allocator>::reserve(size_type newCapacity)
{
	if (newCapacity <= _capacity)
		return ;
	if (newCapacity > _allocator.max_size())
		throw (std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size"));	
	T	*newArray = _allocator.allocate(newCapacity);
	for (size_type i = 0; i < _size; ++i) {
		_allocator.construct(newArray + i, _array[i]);
	}
	for (size_type i = 0; i < _size; ++i)
		_allocator.destroy(_array + i);
	_allocator.deallocate(_array, _init_size);
	_init_size = newCapacity;
	_capacity = newCapacity;
	_array = newArray;
	_recalcIterators(true, true);
}

/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */

template < class T, class Allocator >
void	ft::vector<T, Allocator>::clear()
{
	for (size_type i = 0; i < _size; ++i)
		_allocator.destroy(_array + i);
	_size = 0;
	_recalcIterators(false, true);
}

template < class T, class Allocator >
typename ft::vector<T, Allocator>::iterator	ft::vector<T, Allocator>::insert(iterator pos,
	const T& value)
{
	if (_size + 1 > _capacity)
	{
		size_type	pos_index = pos - _itrBegin;
		this->_doubleCapacity();
		pos = _itrBegin + pos_index;
	}
	pointer src = pos.operator->();
	pointer dest = src + 1;
	for (size_type i = _itrEnd - pos; i > 0;) {
		--i;
		_allocator.construct(dest + i, src[i]);
		// dest[i] = src[i];
	}
	
	*pos = value;
	++_size;
	_recalcIterators(false, true);
	return (pos);
}

template < class T, class Allocator >
void	ft::vector<T, Allocator>::insert(iterator pos, size_type count, const T& value)
{
	if (_size + count > _capacity)
	{
		size_type	pos_index = pos - _itrBegin;
		this->reserve(_size + count);
		pos = _itrBegin + pos_index;
	}
	pointer src = pos.operator->();
	pointer dest = src + count;
	for (difference_type i = _itrEnd - pos; i > 0;) {
		--i;
		// _allocator.destroy(_array + i);
		_allocator.construct(dest + i, src[i]);
		// dest[i] = src[i];
	}
	for (size_type i = 0; i < count; ++i, ++pos) {
		*pos = value;
	}
	_size += count;
	_recalcIterators(false, true);
}

template < class T, class Allocator >
template < class InputIt >
typename ft::enable_if
<
	!ft::is_fundamental<InputIt>::value,
	void
>::type
ft::vector<T, Allocator>::insert(iterator pos, InputIt first, InputIt last)
{
	_do_insert(pos, first, last, typename ft::iterator_traits<InputIt>::iterator_category());
}

template < class T, class Allocator >
template < class InputIt >
void	ft::vector<T, Allocator>::_do_insert(iterator pos, InputIt first, InputIt last,
	std::input_iterator_tag)
{
	#if VEC_DEBUG_VERBOSE == true
		std::cerr << _BLU"vector: insert: In input iterator specialization"RESET << std::endl;
	#endif

	for (; first != last; ++first, ++pos)
		this->insert(pos, *first);
	_recalcIterators(false, true);
}

template < class T, class Allocator >
template < class ForwardIt >
void	ft::vector<T, Allocator>::_do_insert(iterator pos, ForwardIt first, ForwardIt last,
	std::forward_iterator_tag)
{
	#if VEC_DEBUG_VERBOSE == true
		std::cerr << _BLU"vector: insert: In forward iterator specialization"RESET << std::endl;
	#endif

	difference_type	count = std::distance(first, last);
	if (_size + count > _capacity)
	{
		size_type	pos_index = pos.operator->() - _itrBegin.operator->();
		// typename ForwardIt::pointer	first_ptr = first.operator->();
		// typename ForwardIt::pointer	last_ptr = last.operator->();
		// size_type first_index = (first_ptr >= _array && first_ptr <= _array + _capacity ?
		// 	first_ptr - _array : std::numeric_limits<size_type>::max());
		// size_type last_index = (first_index != std::numeric_limits<size_type>::max() ?
		// 	last_ptr - _array : std::numeric_limits<size_type>::max());
		// size_type first_index
		// 	= (first.operator->() >= _array && first.operator->() <= _array + _capacity ?
		// 		first.operator->() : std::numeric_limits<size_type>::max());
		this->reserve(_size + count);
		pos = _itrBegin.operator->() + pos_index;
		// if (first_index != std::numeric_limits<size_type>::max()) {
		// 	first = _array + first_index;
		// 	last = _array + last_index;
		// }
	}
	pointer src = pos.operator->();
	pointer dest = src + count;
	for (difference_type i = _itrEnd - pos; i > 0;) {
		--i;
		// dest[i] = src[i];
		// _allocator.destroy(_array + i);
		_allocator.construct(dest + i, src[i]);
	}
	for (; first != last; ++first, ++pos)
		*pos = *first;
	_size += count;
	_recalcIterators(false, true);
}

template < class T, class Allocator >
typename ft::vector<T, Allocator>::iterator	ft::vector<T, Allocator>::erase(iterator pos)
{
	_allocator.destroy(pos.operator->());
	pointer src = (pos + 1).operator->();
	pointer dest = pos.operator->();
	for (difference_type i = 0; i < _itrEnd - src; ++i) {
		// dest[i] = src[i];
		// _allocator.destroy(dest + i);
		_allocator.construct(dest + i, src[i]);
	}
	--_size;
	_recalcIterators(false, true);
	if (pos > _itrEnd)
		return (_itrEnd);
	else
		return (pos);
}

template < class T, class Allocator >
typename ft::vector<T, Allocator>::iterator	ft::vector<T, Allocator>::erase(iterator first, iterator last)
{
	_size -= ft::distance(first, last);
	for (iterator it = first; it != last; ++it)
		_allocator.destroy(it.operator->());
	pointer src = last.operator->();
	pointer dest = first.operator->();
	for (difference_type i = 0; i < _itrEnd - last; ++i) {
		// _allocator.destroy(dest + i);
		_allocator.construct(dest + i, src[i]);
		// dest[i] = src[i];
	}
	_recalcIterators(false, true);
	return (first);
}

template < class T, class Allocator >
void	ft::vector<T, Allocator>::push_back(const T& value)
{
	if (_size + 1 > _capacity)
		this->_doubleCapacity();
	_allocator.construct(_array + _size, value);
	++_size;
	_recalcIterators(false, true);
}

template < class T, class Allocator >
void	ft::vector<T, Allocator>::pop_back()
{
	_allocator.destroy((_array + _size--) - 1);
	_recalcIterators(false, true);
}

template < class T, class Allocator >
void	ft::vector<T, Allocator>::resize(size_type count, T value)
{
	if (_size < count)
	{
		if (_capacity < count)
			this->reserve(count);
		for (size_type i = _size; i < count; ++i)
			_allocator.construct(_array + i, value);
		_size = count;
		_recalcIterators(false, true);
	}
	else if (count < _size)
	{
		this->erase(this->begin() + count, this->end());
	}
}

template < class T, class Allocator >
void	ft::vector<T, Allocator>::swap(vector& other)
{
	// vector			tmp;
	// vector::pointer	tmp_ptr = tmp._array;

	if (_verbose)
		std::cout << "DEBUG: INSIDE MEMBER SWAP FUNC" << std::endl;
	std::swap(this->_allocator, other._allocator);
	std::swap(this->_init_size, other._init_size);
	std::swap(this->_array, other._array);
	std::swap(this->_capacity, other._capacity);
	std::swap(this->_size, other._size);
	std::swap(this->_itrBegin, other._itrBegin);
	std::swap(this->_itrEnd, other._itrEnd);
	// tmp._shallowCopyNoDealloc(other);
	// other._shallowCopyNoDealloc(*this);
	// this->_shallowCopyNoDealloc(tmp);
	// tmp._init_size = 0;
	// tmp._array = tmp_ptr;
}

// namespace ft
// {
// 	// using std::swap;
// 	template< class T, class Alloc >
// 	void	swap(ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs)
// 	{
// 		std::cout << "DEBUG: SWAP IS SPECIALIZED (IN FT)" << std::endl;
// 		lhs.swap(rhs);
// 	}
// }

// NOTE: Apparently this is the wrong way to do it, orthodox way is commented out above.
// However, only with that solution can I specialize std::swap for both these cases:
// - `using std::swap; swap(a, b);`
// - `std::swap(a, b);`
namespace std
{
	// using std::swap;
	template< class T, class Alloc >
	void	swap(ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs)
	{
		if (VEC_DEBUG_VERBOSE)
			std::cout << "DEBUG: SWAP IS SPECIALIZED (IN STD)" << std::endl;
		lhs.swap(rhs);
	}
}

/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */

template < class T, class Allocator >
void	ft::vector<T, Allocator>::_doubleCapacity()
{
	if (_capacity == 0)
		this->reserve(1);
	else
		this->reserve(_capacity * 2);
}

template < class T, class Allocator >
void	ft::vector<T, Allocator>::_recalcIterators(bool begin, bool end)
{
	if (begin)
		_itrBegin = _array;
	if (end)
		_itrEnd = _array + _size;
}

template < class T, class Allocator >
void	ft::vector<T, Allocator>::_shallowCopyNoDealloc(vector& other)
{
	_allocator = other._allocator;
	_init_size = other._init_size;

	_array = other._array;
	_capacity = other._capacity;
	_size = other._size;
	
	_itrBegin = other._itrBegin;
	_itrEnd = other._itrEnd;
}
