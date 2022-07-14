/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 10:10:28 by pbremond          #+#    #+#             */
/*   Updated: 2022/07/14 19:23:29 by pbremond         ###   ########.fr       */
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
class __map_iterator
{
	private:
		
	public:
		typedef std::bidirectional_iterator_tag	iterator_type;
		typedef T								value_type;
		typedef	T*								pointer;
		typedef	T&								reference;
		typedef	ptrdiff_t						difference_type;
};


template <
    class Key,
    class T,
    class Compare = std::less<Key>, // TODO: ft::less ?
    class Allocator = std::allocator< ft::pair<const Key, T> >
		>
class map
{
	public:
		typedef				Key										key_type;
		typedef				T										mapped_type;
		typedef typename	ft::pair<const Key, T>					value_type;
		typedef typename	std::size_t								size_type;
		typedef typename	std::ptrdiff_t							difference_type;
		typedef				Compare									key_compare;
		typedef				Allocator								allocator_type;
		typedef				value_type&								reference;
		typedef				value_type const&						const_reference;
		typedef	typename	Allocator::pointer						pointer;
		typedef	typename	Allocator::const_pointer				const_pointer;
		typedef 			void									iterator;
		typedef 			void									const_iterator;
		typedef typename	ft::reverse_iterator<iterator>			reverse_iterator;
		typedef typename	ft::reverse_iterator<const_iterator>	const_reverse_iterator;

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
		~map();

		map&	operator=(map const& src);
		
		allocator_type	get_allocator() const { return (allocator_type()); }
	
	private:
		struct s_node
		{
			s_node	*parent;
			s_node	*left;
			s_node	*right;

			value_type	val;
			enum { RED, BLACK }	colour;

			s_node(value_type const& src, s_node *_parent) : val(src),
					parent(_parent), left(NULL), right(NULL), colour(RED) {}
		};

		s_node	*_root;
		friend __map_iterator<Key, T, Compare, Allocator>;
	
	public:
		T&			at(Key const& key);
		T const&	at(Key const& key) const;
		T&			operator[](Key const& key);

		bool		empty() const { return (_root == NULL); }
		size_type	size() const;
		size_type	max_size() const { return (std::numeric_limits<difference_type>::max()); } // NOTE: Is this allowed?

		void		clear();

		ft::pair<iterator, bool>	insert(value_type const& val);
		iterator					insert(iterator hint, value_type const& val);
		template<class InputIt>
		typename ft::enable_if <
			!ft::is_fundamental<InputIt>::value,
			void
		>::type						insert(InputIt first, InputIt last);

		void		erase(iterator pos);
		void		erase(iterator first, iterator last);
		size_type	erase(Key const& key);

		void		swap(map& src);

		size_type		count(Key const& key) const;
		iterator		find(Key const& key);
		const_iterator	find(Key const& key) const;

		std::pair<iterator,iterator>				equal_range(Key const& key);
		std::pair<const_iterator,const_iterator>	equal_range(Key const& key) const;

		iterator		lower_bound(Key const& key);
		const_iterator	lower_bound(Key const& key) const;
		iterator		upper_bound(Key const& key);
		const_iterator	upper_bound(Key const& key) const;

		key_compare		key_comp() const;
		value_compare	value_comp() const;
};

}

#include "map.tpp"
