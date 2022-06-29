/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 10:40:16 by pbremond          #+#    #+#             */
/*   Updated: 2022/06/29 11:16:30 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "vector.hpp"

namespace ft
{

template < class T, class Container = ft::vector<T> >
class stack
{
	public:
		typedef				Container					container_type;
		typedef typename	Container::value_type		value_type;
		typedef typename	Container::size_type		size_type;
		typedef typename	Container::reference		reference;
		typedef typename	Container::const_reference	const_reference;
	
	protected:
		container_type	c;
	
	public:
		explicit stack(Container const& cnt = Container()) : c(cnt) {}
		stack(stack const& src) : c(src.c) {}
		~stack() {}
	
	public:
		reference		top()		{ return (c.back()); }
		const_reference	top() const { return (c.back()); }

		bool		empty() const { return (c.empty()); }
		size_type	size()  const { return (c.size());  }

		void	push(value_type const& value) { c.push_back(value); }
		void	pop()						  { c.pop_back(); }
	
	private:
		template<class U, class Cont>
		friend bool	operator==(ft::stack<U, Cont> const&, ft::stack<U, Cont> const&);
		template<class U, class Cont>
		friend bool	operator< (ft::stack<U, Cont> const&, ft::stack<U, Cont> const&);
};

template < class T, class Container >
bool	operator==(ft::stack<T,Container> const& lhs, ft::stack<T,Container> const& rhs)
{
	return (lhs.c == rhs.c);
}

template < class T, class Container >
bool	operator!=(ft::stack<T,Container> const& lhs, ft::stack<T,Container> const& rhs)
{
	return (!(lhs == rhs));
}

template < class T, class Container >
bool	operator< (ft::stack<T,Container> const& lhs, ft::stack<T,Container> const& rhs)
{
	return (lhs.c < rhs.c);
}

template < class T, class Container >
bool	operator> (ft::stack<T,Container> const& lhs, ft::stack<T,Container> const& rhs)
{
	return (rhs < lhs);
}

template < class T, class Container >
bool	operator<=(ft::stack<T,Container> const& lhs, ft::stack<T,Container> const& rhs)
{
	return (!(rhs < lhs));
}

template < class T, class Container >
bool	operator>=(ft::stack<T,Container> const& lhs, ft::stack<T,Container> const& rhs)
{
	return (!(lhs < rhs));
}

}
