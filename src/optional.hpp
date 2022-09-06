/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optional.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:26:23 by pbremond          #+#    #+#             */
/*   Updated: 2022/09/06 18:57:41 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>

namespace ft
{

// Not as functional or as good as the real C++17's std::optional. And I don't care.

class bad_optional_access : public std::exception
{
	public:
		bad_optional_access() throw() {}
		virtual const char* what() const throw() { return ("bad optional access"); }
};

struct nullopt_t
{
	explicit nullopt_t(int) {}
};

const nullopt_t nullopt(0);

template <class T>
class optional
{
	private:
		bool	_hasData;
		T		_data;

	public:
		optional() : _hasData(false) {}
		optional(nullopt_t) : _hasData(false) {}
		optional(T const& src) : _hasData(true), _data(src) {}
		optional(optional const& src) : _hasData(src._hasData), _data(src._data) {}

		optional&	operator=(nullopt_t) throw() {
			if (_hasData) {
				_data.~T(); // I don't even know how that doesn't fuck up with primitives, but it's a good thing it doesn't
				_hasData = false;
			}
			return (*this);
		}
		optional&	operator=(T const& src) {
			_data = src;
			_hasData = true;
		}
		optional&	operator=(optional const& src) {
			if (!src.has_value())
				return (*this = ft::nullopt);
			else {
				_data = src.value();
				_hasData = true;
				return (*this);
			}
		}
	
	public:
		operator bool() const throw() { return (_hasData); }
		bool	has_value() const throw() { return (_hasData); }

		T const* operator->() const throw() { return (&_data); }
		T*		 operator->() throw()		{ return (&_data); }
		T const& operator*() const throw()	{ return (_data); }
		T& 		 operator*() throw()		{ return (_data); }

		T&			value() {
			if (_hasData)
				return (_data);
			else
				throw (bad_optional_access());
		}
		T const&	value() const {
			if (_hasData)
				return (_data);
			else
				throw (bad_optional_access());
		}

		T	value_or(T const& default_value) const { return (_hasData ? _data : default_value); }

		void	reset() throw() { *this = ft::nullopt; }
		void	swap(optional& src) throw() {
			optional tmp(src);
			src = *this;
			*this = tmp;
		}
};

}
