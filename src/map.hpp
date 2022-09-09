/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 10:10:28 by pbremond          #+#    #+#             */
/*   Updated: 2022/09/09 15:13:14 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include "utility.hpp"
#include "type_traits.hpp"
#include "optional.hpp"

#include "ansi_color.h"
#include <queue>

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

			value_type	val;
			enum { RED, BLACK }	colour;

			__s_node(value_type const& value, __s_node *_parent) : parent(_parent), left(NULL),
			right(NULL), val(value), colour(RED) {}

			__s_node(__s_node const& src) : parent(src.parent), left(src.left), right(src.right),
			val(src.val), colour(src.colour) {}
			
			~__s_node()
			{
				// if (MAP_DEBUG_VERBOSE)
				// 	std::cerr << "\e[0;30;41m NODE DESTROYED \e[0m" << std::endl;
			}

			inline void		toggleColour() { colour = (colour == RED ? BLACK : RED); }
			inline __s_node	*brother() // OK
			{
				if (parent == NULL)
					return (NULL);
				return (this == parent->left ? parent->right : parent->left);
			}
			inline __s_node	*uncle() // OK, or I commit sudoku
			{
				if (parent == NULL || parent->parent == NULL)
					return (NULL);
				return (parent == parent->parent->left ? parent->parent->right : parent->parent->left);
			}
			inline optional<__s_node*>	optbrother() // OK
			{
				if (parent == NULL || parent->left == NULL || parent->right == NULL)
					return (nullopt);
				return (this == parent->left ? parent->right : parent->left);
			}
			inline optional<__s_node*>	optuncle() // OK
			{
				if (parent == NULL || parent->parent == NULL
					|| parent->parent->left == NULL || parent->parent->right == NULL)
					return (nullopt);
				return (parent == parent->parent->left ? parent->parent->right : parent->parent->left);
			}

			void	rotateLeft(__s_node **treeRoot) // TESTME
			{ // Oh fuck it looks like it works
				__s_node	*son = this->right;
				if (son == NULL)
					throw (std::logic_error("map: attempted to left-rotate with no right child"));
				this->right = son->left;
				if (this->right != NULL)
					this->right->parent = this;
				if (this->parent == NULL)
					*treeRoot = son;
				else if (this->parent->left == this)
					this->parent->left = son;
				else
					this->parent->right = son;
				son->parent = this->parent;
				son->left = this;
				this->parent = son;
			}

			void	rotateRight(__s_node **treeRoot) // TESTME
			{ // Oh fuck it looks like it works
				__s_node	*son = this->left;
				if (son == NULL)
					throw (std::logic_error("map: attempted to right-rotate with no left child"));
				this->left = son->right;
				if (this->left != NULL)
					this->left->parent = this;
				if (this->parent == NULL)
					*treeRoot = son;
				else if (this->parent->right == this)
					this->parent->right = son;
				else
					this->parent->left = son;
				son->parent = this->parent;
				son->right = this;
				this->parent = son;
			}
		};

		typedef typename	Allocator::template rebind<__s_node>::other	_Alloc;
		__s_node	*_root;
		Compare		_compare;
		_Alloc		_allocator;

	private:
		template <class U>
		class __map_iterator
		{
			private:
				friend class map; // KO maybe, are you SURE ? Only needed for debug for now
				__s_node	*_node;

				inline void goto_start() throw() { for (; _node->left != NULL; _node = _node->left) ; } // OK
				
			public:
				typedef std::bidirectional_iterator_tag	iterator_vategory;
				typedef ptrdiff_t						difference_type;
				typedef U								value_type;
				typedef U*								pointer;
				typedef U&								reference;
				
				__map_iterator(__s_node *node = NULL, bool goto_begin = false) : _node(node)
				{
					if (goto_begin == true && node != NULL)
						this->goto_start();
				}

				inline operator __map_iterator<const U>() const { return (this->_node); }

				inline reference	operator*()  const { return(_node->val);  } // OK
				inline pointer		operator->() const { return(&_node->val); } // OK

				__map_iterator&	operator++(); // OK
				__map_iterator	operator++(int); // TESTME
				__map_iterator&	operator--(); // TESTME
				__map_iterator	operator--(int); // TESTME

				inline bool	operator==(__map_iterator const& rhs) { return (this->_node == rhs._node); } // OK
				inline bool	operator!=(__map_iterator const& rhs) { return (this->_node != rhs._node); } // OK
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
				inline bool operator()(value_type const& lhs,value_type const& rhs) const
				{
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
		T&			at(Key const& key); // TESTME
		T const&	at(Key const& key) const; // TESTME
		T&			operator[](Key const& key); // TESTME

		bool		empty() const { return (_root == NULL); } // OK
		size_type	size() const;
		size_type	max_size() const { return (std::numeric_limits<difference_type>::max()); } // NOTE: Is this allowed?

		void		clear(); // OK

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

		size_type		count(Key const& key) const; // OK
		iterator		find(Key const& key); // OK
		const_iterator	find(Key const& key) const; // OK

		std::pair<iterator,iterator>				equal_range(Key const& key);
		std::pair<const_iterator,const_iterator>	equal_range(Key const& key) const;

		iterator		lower_bound(Key const& key);
		const_iterator	lower_bound(Key const& key) const;
		iterator		upper_bound(Key const& key);
		const_iterator	upper_bound(Key const& key) const;

		key_compare		key_comp() const { return (_compare); } // OK
		value_compare	value_comp() const;

		inline iterator			begin()		  { return (iterator(_root, true)); } // OK
		inline const_iterator	begin() const { return (iterator(_root, true)); } // OK
		inline iterator			end()		{ return (iterator(NULL)); } // OK
		inline const_iterator	end() const { return (iterator(NULL)); } // OK

		void	debug_leftRotate(Key const& key)
		{
			iterator	target = this->find(key);
			if (target == this->end())
				throw (std::logic_error("DEBUG: debug_leftRotate: invalid key"));
			std::cout << BBLU"DEBUG:"BRED" left rotate ("<<key<<')'<<RESET << std::endl;
			target._node->rotateLeft(&_root);
		}

		void	debug_rightRotate(Key const& key)
		{
			iterator	target = this->find(key);
			if (target == this->end())
				throw (std::logic_error("DEBUG: debug_rightRotate: invalid key"));
			std::cout << BBLU"DEBUG:"BGRN" right rotate ("<<key<<')'<<RESET << std::endl;
			target._node->rotateRight(&_root);
		}
		void	debug_printByLevel()
		{
			std::queue<__s_node *>	queue;
			queue.push(_root);
			std::cout << BLUB"  "RESET BBLU"DEBUG: Print by level"RESET << std::endl;
			while (!queue.empty())
			{
				std::cout << BLUB" "RESET" "
					<< (queue.front()->colour == __s_node::RED ? REDB : BLKB)
					<< queue.front()->val.first << " | " << queue.front()->val.second
					<< RESET << std::endl;
				if (queue.front()->left)
					queue.push(queue.front()->left);
				if (queue.front()->right)
					queue.push(queue.front()->right);
				queue.pop();
			}
		}
		void	debug_printByLevel(Key const& key)
		{
			std::queue<__s_node *>	queue;
			queue.push(_root);
			std::cout << BLUB"  "RESET BBLU"DEBUG: Print by level"RESET << std::endl;
			while (!queue.empty())
			{
				std::cout << BLUB" "RESET" "
					<< (queue.front()->colour == __s_node::RED ? REDB : BLKB)
					<< queue.front()->val.first << " | " << queue.front()->val.second
					<< RESET << (queue.front()->val.first == key ? BGRN"*"RESET : "")
					<< std::endl;
				if (queue.front()->left)
					queue.push(queue.front()->left);
				if (queue.front()->right)
					queue.push(queue.front()->right);
				queue.pop();
			}
		}
		void	debug_printFamily(Key const& key)
		{
			iterator	target = this->find(key);
			if (target == this->end())
				throw (std::logic_error("DEBUG: debug_printFamily: invalid key"));
			std::cout << BBLU"DEBUG: Family of node " << key << ": \n"RESET
				// << _YEL"Parent: "RESET << target._node->parent << '\n'
				<< _YEL"Parent: "RESET
					<< (target._node->parent ? target._node->parent->val.first : 99999) << '\n'
				<< _RED"Left: "RESET
					<< (target._node->left ? target._node->left->val.first : 99999) << '\n'
				<< _GRN"Right: "RESET
					<< (target._node->right ? target._node->right->val.first : 99999) << std::endl;
				// << _GRN"Right: "RESET << target._node->right << std::endl;
		}

	private:
		void	_postfix_dealloc(__s_node *root);
		int		_checkInsertValidity(__s_node *node) const;
		ft::pair<iterator, bool>	_correctInsertion(__s_node *node, iterator const& retval);
};

}

#include "map.tpp"
