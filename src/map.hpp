/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 10:10:28 by pbremond          #+#    #+#             */
/*   Updated: 2022/09/11 21:11:40 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>
#include "utility.hpp"
#include "type_traits.hpp"
#include "optional.hpp"
#include "reverse_iterator.hpp"

#include "ansi_color.h"
#include <queue>

#define MAP_DEBUG_VERBOSE	false

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

			__s_node() : parent(NULL), left(NULL), right(NULL), val(value_type()), colour(BLACK) {}

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

			void	rotateLeft(__s_node **treeRoot) // OK
			{
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

			void	rotateRight(__s_node **treeRoot) // OK
			{
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
		Compare		_compare;
		_Alloc		_allocator;
		__s_node	*_endLeaf;
		__s_node	*_root;

	private:
		template <class U>
		class __map_iterator
		{
			private:
				friend class map; // KO maybe, are you SURE ?
				typedef __map_iterator<U>	self;
				
				__s_node	*_node;

				inline self& goto_begin()
				{
					for (; _node->left != NULL; _node = _node->left) ;
					return *this;
				} // OK
				inline self& goto_end()
				{
					for (; _node->right != NULL; _node = _node->right) ;
					return *this;
				} // OK
				
			public:
				typedef std::bidirectional_iterator_tag	iterator_category;
				typedef ptrdiff_t						difference_type;
				typedef U								value_type;
				typedef U*								pointer;
				typedef U&								reference;
				
				__map_iterator(__s_node *node = NULL, bool goto_begin = false) : _node(node)
				{
					if (goto_begin == true && node != NULL)
						this->goto_begin();
				}

				inline operator __map_iterator<const U>() const { return (this->_node); }

				inline reference	operator*()  const { return(_node->val);  } // OK
				inline pointer		operator->() const { return(&_node->val); } // OK

				__map_iterator&	operator++(); // OK
				__map_iterator	operator++(int); // OK
				__map_iterator&	operator--(); // OK
				__map_iterator	operator--(int); // OK

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
		typedef typename	std::reverse_iterator<iterator>			reverse_iterator;
		typedef typename	std::reverse_iterator<const_iterator>	const_reverse_iterator;

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{ // TODO: ft::binary_function ?
			friend class map;

			public:
				using typename std::binary_function<value_type, value_type, bool>::result_type;
				using typename std::binary_function<value_type, value_type, bool>::first_argument_type;
				using typename std::binary_function<value_type, value_type, bool>::second_argument_type;
				inline bool operator()(value_type const& lhs,value_type const& rhs) const
				{
					return (comp(lhs.first, rhs.first));
				}

			protected:
				Compare		comp;
				value_compare(Compare c) : comp(c) {}
		};
		
	public:
		explicit map(Compare const& comp = Compare(), Allocator const& alloc = Allocator()); // OK
		template<class InputIt>
		map(InputIt first, InputIt last,
			Compare const& comp = Compare(),
			Allocator const& alloc = Allocator(),
			typename enable_if< !is_fundamental<InputIt>::value, int >::type = 0); // OK
		map(map const& src); // OK
		~map() { this->clear(); _allocator.deallocate(_endLeaf, 1); } // OK

		map&	operator=(map const& src); // OK
		
		allocator_type	get_allocator() const { return (_allocator); } // OK
	
	public:
		T&			at(Key const& key); // OK
		T const&	at(Key const& key) const; // OK
		T&			operator[](Key const& key); // OK

		bool		empty() const { return (_root == _endLeaf); } // OK
		size_type	size() const { return ft::distance(this->begin(), this->end()); } // FIXME: Inefficient as hell
		size_type	max_size() const { return (_allocator.max_size()); } // OK

		void		clear(); // OK

		ft::pair<iterator, bool>	insert(value_type const& val); // OK
		iterator					insert(iterator hint, value_type const& val); // OK
		template<class InputIt>
		typename ft::enable_if <
			!ft::is_fundamental<InputIt>::value,
			void
		>::type						insert(InputIt first, InputIt last); // OK

		void		erase(iterator pos); // TODO
		void		erase(iterator first, iterator last); // TODO
		size_type	erase(Key const& key); // TODO

		void		swap(map& src); // OK

		size_type		count(Key const& key) const; // OK
		iterator		find(Key const& key); // OK
		const_iterator	find(Key const& key) const; // OK

		ft::pair<iterator,iterator>				equal_range(Key const& key) // OK
		{
			return (make_pair(lower_bound(key), upper_bound(key)));
		}
		ft::pair<const_iterator,const_iterator>	equal_range(Key const& key) const // OK
		{
			return (make_pair(lower_bound(key), upper_bound(key)));
		}

		iterator		lower_bound(Key const& key); // OK
		const_iterator	lower_bound(Key const& key) const; // OK
		iterator		upper_bound(Key const& key); // OK
		const_iterator	upper_bound(Key const& key) const; // OK

		key_compare		key_comp() const { return (_compare); } // OK
		value_compare	value_comp() const { return (value_compare(_compare)); } // OK

		inline iterator			begin()		  { return (iterator(_root).goto_begin()); } // OK
		inline const_iterator	begin() const { return (iterator(_root).goto_begin()); } // OK
		inline iterator			end()		{ return (iterator(_endLeaf)); } // OK
		inline const_iterator	end() const { return (iterator(_endLeaf)); } // OK

		inline reverse_iterator			rbegin()	   { return reverse_iterator(end()); }
		inline const_reverse_iterator	rbegin() const { return reverse_iterator(end()); }
		inline reverse_iterator			rend()		 { return reverse_iterator(begin()); }
		inline const_reverse_iterator	rend() const { return reverse_iterator(begin()); }

	#if MAP_DEBUG_VERBOSE == true
		void	debug_leftRotate(Key const& key);	
		void	debug_rightRotate(Key const& key);
		void	debug_printByLevel() const;
		void	debug_printByLevel(Key const& key) const;
		void	debug_printFamily(Key const& key) const;
	#endif

	private:
		void	_postfix_dealloc(__s_node *root);
		int		_checkInsertValidity(__s_node *node) const;
		ft::pair<iterator, bool>	_correctInsertion(__s_node *node, iterator const& retval);
		void	_correctInsertion_rotate(__s_node *node);
		enum _e_correctAction {
			CORRECT_ROOT,
			CORRECT_NOTHING,
			CORRECT_COLOR,
			CORRECT_ROTATE
		};
		void	_repositionEndLeaf(__s_node *newNode)
		{
			newNode->right = _endLeaf;
			_endLeaf->parent = newNode;
		}
};

}

#include "map.tpp"
