/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:14:34 by pbremond          #+#    #+#             */
/*   Updated: 2022/06/28 03:38:23 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "vector.hpp"

#define DEBUG_VERBOSE	false

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
	_itrEnd = _array + _capacity;
	for (size_type i = 0; i < count; ++i)
		_array[i] = value;
}

template < class T, class Allocator >
template<class InputIt>
ft::vector<T, Allocator>::vector(InputIt first,
								 InputIt last,
								 const Allocator& alloc,
								 typename enable_if< !is_fundamental<InputIt>::value, int >::type)
: _allocator(alloc)
{
	_init_size = std::distance(first, last);
	_capacity = _init_size;
	_size = _init_size;
	_array = _allocator.allocate(_init_size);
	_itrBegin = _array;
	_itrEnd = _array + _capacity;

	size_type	i = 0;
	for (InputIt itr = first; itr != last; ++itr)
		_array[i++] = *itr;
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
	this->assign(src.begin(), src.end());
}

template < class T, class Allocator >
ft::vector<T, Allocator>	&ft::vector<T, Allocator>::operator=(const ft::vector<T, Allocator>& rhs)
{
	_allocator.deallocate(_array, _init_size);
	_array = _allocator.allocate(rhs._capacity);
	_recalcIterators(true, false);
	_capacity = rhs._capacity;
	_init_size = rhs._capacity;
	_size = rhs._size;
	this->assign(rhs.begin(), rhs.end());
	return (*this);
}

template < class T, class Allocator >
ft::vector<T, Allocator>::~vector()
{
	_allocator.deallocate(_array, _init_size);
}

template < class T, class Allocator >
void	ft::vector<T, Allocator>::assign(size_type count, const T& value)
{
	if (count > _capacity)
		this->reserve(count);
	for (size_type i = 0; i < count; ++i)
		_array[i] = value;
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
	difference_type	newSize = std::distance<InputIt>(first, last);
	size_type		i = 0;

	if (static_cast<size_type>(newSize) > _capacity)
		this->reserve(newSize);
	for (InputIt itr = first; itr != last; ++itr)
		_array[i++] = *itr;
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
		throw (std::length_error("std::length_error"));	
	T	*newArray = _allocator.allocate(newCapacity);
	std::memcpy(newArray, _array, _size * sizeof(T));
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
	std::memmove((pos + 1).operator->(), pos.operator->(),
		static_cast<size_type>(_itrEnd - pos) * sizeof(T));
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
		size_type	pos_index = pos.operator->() - _itrBegin.operator->();
		this->reserve(_size + count);
		pos = _itrBegin + pos_index;
	}
	std::memmove((pos + count).operator->(), pos.operator->(),
		static_cast<size_type>(_itrEnd - pos) * sizeof(T));
	for (size_type i = 0; i < count; ++i)
		*pos++ = value;
	_size += count;
	_recalcIterators(false, true);
}

template < class T, class Allocator >
template < class InputIt >
typename std::enable_if
<
	!ft::is_fundamental<InputIt>::value,
	void
>::type
ft::vector<T, Allocator>::insert(iterator pos, InputIt first, InputIt last)
{
	difference_type	count = std::distance(first, last);

	if (_size + count > _capacity)
	{
		size_type	pos_index = pos.operator->() - _itrBegin.operator->();
		this->reserve(_size + count);
		pos = _itrBegin.operator->() + pos_index;
	}
	std::memmove((pos + count).operator->(), pos.operator->(),
		static_cast<size_type>(_itrEnd - pos) * sizeof(T));
	for (; first != last; ++first)
		*pos++ = *first;
	_size += count;
	_recalcIterators(false, true);
}

template < class T, class Allocator >
typename ft::vector<T, Allocator>::iterator	ft::vector<T, Allocator>::erase(iterator pos)
{
	_allocator.destroy(pos.operator->());
	std::memmove(pos.operator->(), (pos + 1).operator->(),
		static_cast<size_type>((_itrEnd).operator->() - (pos + 1).operator->()) * sizeof(T));
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
	_size -= std::distance(first, last);
	for (iterator it = first; it != last; ++it)
		_allocator.destroy(it.operator->());
	std::memmove(first.operator->(), last.operator->(),
		static_cast<size_type>((_itrEnd).operator->() - last.operator->()) * sizeof(T));
	_recalcIterators(false, true);
	return (first);
}

template < class T, class Allocator >
void	ft::vector<T, Allocator>::push_back(const T& value)
{
	if (_size + 1 > _capacity)
		this->_doubleCapacity();
	_array[_size] = value;
	++_size;
	_recalcIterators(false, true);
}

template < class T, class Allocator >
void	ft::vector<T, Allocator>::pop_back()
{
	_array[_size--].~T();
}

template < class T, class Allocator >
void	ft::vector<T, Allocator>::resize(size_type count, T value)
{
	if (_size < count)
	{
		if (_capacity < count)
			this->reserve(count); // TESTME: compare alloc size to std::vector
		for (size_type i = _size; i < count; ++i)
			_array[i] = value;
		_size = count;
		_recalcIterators(false, true);
	}
	else if (_size > count)
	{
		this->erase(_itrBegin + count, _itrEnd);
	}
}

template < class T, class Allocator >
void	ft::vector<T, Allocator>::swap(vector& other)
{
	vector	tmp;

	if (_verbose)
		std::cout << "DEBUG: INSIDE MEMBER SWAP FUNC" << std::endl;
	tmp._shallowCopyNoDealloc(other);
	other._shallowCopyNoDealloc(*this);
	this->_shallowCopyNoDealloc(tmp);
	tmp._array = NULL;
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
		if (DEBUG_VERBOSE)
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
