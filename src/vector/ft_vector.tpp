/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.tpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:14:34 by pbremond          #+#    #+#             */
/*   Updated: 2022/06/17 01:13:43 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.hpp"
#include <memory>
#include <iterator>
#include <iostream>

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
								const Allocator& alloc)
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

// TODO: Make sure that assign updates iterators if needed
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

// TODO: Make sure that assign() updates iterators
template < class T, class Allocator >
ft::vector<T, Allocator>	&ft::vector<T, Allocator>::operator=(const ft::vector<T, Allocator>& rhs)
{
	_allocator.deallocate(_array, _init_size);
	_array = _allocator.allocate(rhs._capacity);
	_capacity = rhs._capacity;
	_init_size = rhs._capacity;
	_size = rhs.size();
	this->assign(rhs.begin(), rhs.end());
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
void	ft::vector<T, Allocator>::assign(InputIt first, InputIt last)
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

template < class T, class Allocator >
typename ft::vector<T, Allocator>::allocator_type	ft::vector<T, Allocator>::get_allocator() const
{
	return (_allocator);
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
typename ft::vector<T, Allocator>::iterator	ft::vector<T, Allocator>::insert(iterator pos, const T& value)
{
	if (_size + 1 > _capacity)
	{
		std::cout << "prout" << std::endl;
		size_type	pos_index = pos.operator->() - _itrBegin.operator->();
		this->reserve(_capacity * 2);
		pos = _itrBegin.operator->() + pos_index;
	}
	std::memmove((pos + 1).operator->(), pos.operator->(),
		static_cast<size_type>((_itrEnd).operator->() - pos.operator->()));
	*pos = value;
	++_size;
	if (pos == _itrBegin)
		_recalcIterators(true, true);
	else
		_recalcIterators(false, true);
	return (pos);
}

template < class T, class Allocator >
void	ft::vector<T, Allocator>::push_back(const T& value)
{
	if (_size + 1 > _capacity)
		this->reserve(_capacity * 2);
	_array[_size] = value;
	++_size;
	_recalcIterators(false, true);
}

/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */

template < class T, class Allocator >
void	ft::vector<T, Allocator>::_recalcIterators(bool begin, bool end)
{
	if (begin)
		_itrBegin = _array;
	if (end)
		_itrEnd = _array + _size;
}
