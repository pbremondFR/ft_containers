/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 10:10:28 by pbremond          #+#    #+#             */
/*   Updated: 2022/09/07 18:48:16 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include "utility.hpp"
#include "type_traits.hpp"
// #include "optional.hpp"

#define MAP_DEBUG_VERBOSE	true

// TODO: Should maybe switch all of the logic behind the RBtree to a RBtree class,
// and derive it in there ? Same goes for its iterator...

// template <
// 	class Key,
// 	class T,
// 	class Compare = std::less<Key>, // TODO: ft::less ?
// 	class Allocator = std::allocator< ft::pair<const Key, T> >
// 		>
// class map : public __RBtree<ft::pair<const Key, T>, Compare, Allocator >

// Something like that... Except how would Compare() work ?
// Can't use ft::pair comparison operators because they compare both first and second values.
// Can't use default Compare() because it only uses the Key and disregards T.

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
	private:
		struct __s_node
		{
			typedef typename	ft::pair<const Key, T>	value_type;
			
			__s_node	*parent;
			__s_node	*left;
			__s_node	*right;
			Allocator	_allocator2;

			value_type	*val;
			enum { RED, BLACK }	colour;

			__s_node(value_type const& value, __s_node *_parent) : parent(_parent), left(NULL), right(NULL), colour(RED) {
				val = _allocator2.allocate(1);
				_allocator2.construct(val, value);
			}
			__s_node(__s_node const& src) : parent(src.parent), left(src.left), right(src.right), colour(src.colour) {
				val = _allocator2.allocate(1);
				_allocator2.construct(val, *src.val);
			}
			~__s_node() {
				_allocator2.destroy(val);
				_allocator2.deallocate(val, 1);
				val = NULL;
				if (MAP_DEBUG_VERBOSE)
					std::cerr << "\e[0;30;41m NODE DESTROYED \e[0m" << std::endl;
			}
		};

		__s_node	*_root;
		Compare		_compare;
		Allocator	_allocator;
		std::allocator<__s_node>	_node_allocator;

	private:
		template <class U>
		class __map_iterator
		{
			private:
				__s_node	*_node;

				inline void goto_start() throw() { for (; _node->left != NULL; _node = _node->left) ; }
				
			public:
				typedef std::bidirectional_iterator_tag	iterator_vategory;
				typedef ptrdiff_t						difference_type;
				typedef U								value_type;
				typedef U*								pointer;
				typedef U&								reference;
				
				__map_iterator(__s_node *node = NULL, bool goto_begin = false) : _node(node) {
					if (goto_begin == true && node != NULL)
						this->goto_start();
				}

				inline operator __map_iterator<const U>() const { return (this->_node); }

				inline reference	operator*()  const { return(*_node->val);  }
				inline pointer		operator->() const { return(_node->val); }

				__map_iterator&	operator++()
				{
					if (_node->right != NULL) {
						_node = _node->right;
						while (_node->left != NULL) {
							_node = _node->left;
						}
					}
					else {
						__s_node	*parent = _node->parent;
						while (parent != NULL && _node == parent->right) {
							_node = _node->parent;
							parent = parent->parent;
						}
						_node = parent;
					}
					return (*this);
				}

				bool	operator==(__map_iterator const& rhs) { return (this->_node == rhs._node); }
				bool	operator!=(__map_iterator const& rhs) { return (this->_node != rhs._node); }
		};
		
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
		typedef 			__map_iterator<value_type>				iterator;
		typedef 			__map_iterator<const value_type>		const_iterator;
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
				inline bool operator()(value_type const& lhs,value_type const& rhs) const {
					return (comp(lhs.first, rhs.first));
				}
		};
		
	public:
		explicit map(Compare const& comp = Compare(),
					 Allocator const& alloc = Allocator()) : _root(NULL), _compare(comp), _allocator(alloc) {}
		template<class InputIt>
		map(InputIt first, InputIt last,
			Compare const& comp = Compare(),
			Allocator const& alloc = Allocator(),
			typename enable_if< !is_fundamental<InputIt>::value, int >::type = 0);
		map(map const& src);
		~map() { this->clear(); }

		map&	operator=(map const& src);
		
		allocator_type	get_allocator() const { return (allocator_type()); }
	
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

		iterator		begin()		  { return (iterator(_root, true)); }
		const_iterator	begin() const { return (iterator(_root, true)); }
		iterator		end()		{ return (iterator(NULL)); }
		const_iterator	end() const { return (iterator(NULL)); }

	private:
		void	_postfix_clear(__s_node *root) {
			if (root == NULL)
				return ;
			_postfix_clear(root->left);
			_postfix_clear(root->right);
			if (MAP_DEBUG_VERBOSE)
				std::cerr << "DEBUG: " << root->val->first << '\n' << root->val->second << std::endl;
			_node_allocator.destroy(root);
			_node_allocator.deallocate(root, 1);
		}
};

}

#include "map.tpp"
