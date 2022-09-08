/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optional.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:26:23 by pbremond          #+#    #+#             */
/*   Updated: 2022/09/08 20:42:44 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>

#if __cplusplus == 199711L
# define noexcept	throw()
#endif

namespace ft
{

// Not as functional or as good as the real C++17's std::optional. And I don't care.

class bad_optional_access : public std::exception
{
	public:
		virtual const char* what() const noexcept { return ("bad optional access"); }
};

struct nullopt_t
{
	explicit nullopt_t(int) {}
};

const nullopt_t __nullopt(0);
#define nullopt	__nullopt

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

		optional&	operator=(nullopt_t) noexcept {
			if (_hasData) {
				_data.~T(); // I don't even know how that doesn't fuck up with primitives, but I'm glad thing it doesn't
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
		inline operator bool() const noexcept { return (_hasData); }
		inline bool	has_value() const noexcept { return (_hasData); }

		inline T const* operator->() const noexcept { return (&_data); }
		inline T*		operator->() noexcept		{ return (&_data); }
		inline T const& operator*() const noexcept	{ return (_data); }
		inline T& 		operator*() noexcept		{ return (_data); }

		inline T&		value() {
			if (_hasData)
				return (_data);
			else
				throw (bad_optional_access());
		}
		inline T const&	value() const {
			if (_hasData)
				return (_data);
			else
				throw (bad_optional_access());
		}

		inline T	value_or(T const& default_value) const { return (_hasData ? _data : default_value); }

		inline void	reset() noexcept { *this = ft::nullopt; }
		inline void	swap(optional& src) noexcept {
			optional tmp(src);
			src = *this;
			*this = tmp;
		}
};

}
