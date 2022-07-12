/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 10:10:28 by pbremond          #+#    #+#             */
/*   Updated: 2022/07/12 13:39:52 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include "utility.hpp"
#include "type_traits.hpp"

namespace ft
{

template <
    class Key,
    class T,
    class Compare = std::less<Key>, // TODO: ft::less ?
    class Allocator = std::allocator< ft::pair<const Key, T> >
		>
class map
{
	public:
		typedef				Key							key_type;
		typedef				T							mapped_type;
		typedef typename	ft::pair<const Key, T>		value_type;
		typedef typename	std::size_t					size_type;
		typedef typename	std::ptrdiff_t				difference_type;
		typedef				Compare						key_compare;
		typedef				Allocator					allocator_type;
		typedef				value_type&					reference;
		typedef				value_type const&			const_reference;
		typedef	typename	Allocator::pointer			pointer;
		typedef	typename	Allocator::const_pointer	const_pointer;

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{ // TODO: ft::binary_function ?
			friend class map;

			public:
				using typename std::binary_function<value_type, value_type, bool>::result_type;
				using typename std::binary_function<value_type, value_type, bool>::first_argument_type;
				using typename std::binary_function<value_type, value_type, bool>::second_argument_type;

			protected:
				Compare		comp;
				value_compare(Compare c) : comp(c) {}
				bool operator()(value_type const& lhs,value_type const& rhs) const
				{
					return (comp(lhs.first, rhs.first));
				}
		};
		
	
	public:
		explicit map(Compare const& comp = Compare(),
					 Allocator const& alloc = Allocator());

		template<class InputIt>
		map(InputIt first, InputIt last,
			Compare const& comp = Compare(),
			Allocator const& alloc = Allocator(),
			typename enable_if< !is_fundamental<InputIt>::value, int >::type = 0);

		map(map const& src);
		
		allocator_type	get_allocator() const { return (allocator_type()); }
	
	private:
		struct s_node
		{
			s_node	*parent;
			s_node	*left;
			s_node	*right;

			value_type	val;

			s_node() : parent(NULL), left(NULL), right(NULL) {}
		};

		s_node	*root;
		
};

}
