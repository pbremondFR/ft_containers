/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 10:10:28 by pbremond          #+#    #+#             */
/*   Updated: 2022/09/20 19:29:50 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #pragma once
#ifndef MAP_HPP
#define MAP_HPP

#include "utility.hpp"
#include "type_traits.hpp"
#include "optional.hpp"
#include "reverse_iterator.hpp"
#include "algorithm.hpp"

#include <cassert>
#include <functional> // std::less
#include <memory> // std::allocator

#define MAP_DEBUG_VERBOSE	false

#if MAP_DEBUG_VERBOSE == true
# include "ansi_color.h"
# include <queue>
#endif

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
			enum e_colour { RED, BLACK }	colour;

			__s_node() : parent(NULL), left(NULL), right(NULL), val(value_type()), colour(BLACK) {}

			__s_node(value_type const& value, __s_node *_parent) : parent(_parent), left(NULL),
			right(NULL), val(value), colour(RED) {}

			__s_node(__s_node const& src) : parent(src.parent), left(src.left), right(src.right),
			val(src.val), colour(src.colour) {}
			
			~__s_node() {}

			inline void		toggleColour() { colour = (colour == RED ? BLACK : RED); }

			inline __s_node	*brother()
			{
				if (parent == NULL)
					return (NULL);
				return (this == parent->left ? parent->right : parent->left);
			}
			inline __s_node	*uncle()
			{
				if (parent == NULL || parent->parent == NULL)
					return (NULL);
				return (parent == parent->parent->left ? parent->parent->right : parent->parent->left);
			}

			inline bool	isLeftChild() const { return (parent != NULL && this == parent->left); }

			void	rotateLeft(__s_node **treeRoot)
			{
				#if MAP_DEBUG_VERBOSE == true
					logstream << BBLU"DEBUG: "BRED"left rotate (" << this->val.first << ")"RESET << std::endl;
				#endif
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

			void	rotateRight(__s_node **treeRoot)
			{
				#if MAP_DEBUG_VERBOSE == true
					logstream << BBLU"DEBUG: "BGRN"right rotate (" << this->val.first << ")"RESET << std::endl;
				#endif
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

		template <class U>
		class __map_iterator
		{
			private:
				// NOTE: This is needed so that the map class can access the
				// node pointer of the iterator, which simplifies the code a whole bunch.
				friend class map;
				
				typedef __map_iterator<U>	self;
				
				__s_node	*_node;

				inline self& goto_begin()
				{
					for (; _node->left != NULL; _node = _node->left) ;
					return *this;
				}
				inline self& goto_end()
				{
					for (; _node->right != NULL; _node = _node->right) ;
					return *this;
				}
				
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

				inline reference	operator*()  const { return(_node->val);  }
				inline pointer		operator->() const { return(&_node->val); }

				__map_iterator&	operator++();
				__map_iterator	operator++(int);
				__map_iterator&	operator--();
				__map_iterator	operator--(int);

				inline bool	operator==(__map_iterator const& rhs) { return (this->_node == rhs._node); }
				inline bool	operator!=(__map_iterator const& rhs) { return (this->_node != rhs._node); }
		};

	private:
		typedef typename	Allocator::template rebind<__s_node>::other	_Alloc;
		Compare		_compare;
		_Alloc		_allocator;
		__s_node	*_endLeaf;
		__s_node	*_root;
		__s_node	*_dummy;
		std::size_t	_size;

		static std::ostream&	logstream; // Defined in map.tpp

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
				inline bool operator()(value_type const& lhs,value_type const& rhs) const
				{
					return (comp(lhs.first, rhs.first));
				}

			protected:
				Compare		comp;
				value_compare(Compare c) : comp(c) {}
		};
		
	public:
		explicit map(Compare const& comp = Compare(), Allocator const& alloc = Allocator());
		template<class InputIt>
		map(InputIt first, InputIt last,
			Compare const& comp = Compare(),
			Allocator const& alloc = Allocator(),
			typename enable_if< !is_fundamental<InputIt>::value, int >::type = 0);
		map(map const& src);
		~map()
		{
			this->clear();
			_allocator.deallocate(_endLeaf, 1);
			_allocator.deallocate(_dummy, 1);
		}

		map&	operator=(map const& src);
		
		allocator_type	get_allocator() const { return (_allocator); }
	
	public:
		T&			at(Key const& key);
		T const&	at(Key const& key) const;
		T&			operator[](Key const& key);

		bool		empty() const { return (_size == 0); }
		size_type	size() const { return (_size); }
		size_type	max_size() const { return (_allocator.max_size()); }

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

		ft::pair<iterator,iterator>				equal_range(Key const& key)
		{
			return (make_pair(lower_bound(key), upper_bound(key)));
		}
		ft::pair<const_iterator,const_iterator>	equal_range(Key const& key) const
		{
			return (make_pair(lower_bound(key), upper_bound(key)));
		}

		iterator		lower_bound(Key const& key);
		const_iterator	lower_bound(Key const& key) const;
		iterator		upper_bound(Key const& key);
		const_iterator	upper_bound(Key const& key) const;

		key_compare		key_comp() const { return (_compare); }
		value_compare	value_comp() const { return (value_compare(_compare)); }

		inline iterator			begin()		  { return (iterator(_root).goto_begin()); }
		inline const_iterator	begin() const { return (iterator(_root).goto_begin()); }
		inline iterator			end()		{ return (iterator(_endLeaf)); }
		inline const_iterator	end() const { return (iterator(_endLeaf)); }

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
		void	debug_printFamily(const __s_node *node) const;
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
		inline void	_repositionEndLeaf(__s_node *newNode)
		{
			newNode->right = _endLeaf;
			_endLeaf->parent = newNode;
		}
		// NOTE: Leafs are considered to be NULL nodes or the _endLeaf marker
		inline bool	_isLeaf(__s_node *node) const { return (node == NULL || node == _endLeaf || node == _dummy); }
		inline typename __s_node::e_colour	_getColour(__s_node *node) const
		{
			return (_isLeaf(node) ? __s_node::BLACK : node->colour);
		}
		__s_node	*_getBrotherOrDummy(__s_node *node)
		{
			_dummy->colour = __s_node::BLACK;
			_dummy->parent = NULL;
			_dummy->left = NULL;
			_dummy->right = NULL;
			if (node->parent == NULL)
				return (_dummy);
			__s_node	*bro = node->brother();
			if (bro == NULL) {
				_dummy->parent = node->parent;
				return (_dummy);
			}
			return (bro);
		}
		inline __s_node *_brother(__s_node *node) { return (_getBrotherOrDummy(node)); }
		
		// NOTE: Must NOT be called if node has more than one child!!!
		void	_removeNodeWithSingleChild(__s_node *toDelete, __s_node *child = NULL)
		{
			if (child == NULL)
				child = (_isLeaf(toDelete->left) ? toDelete->right : toDelete->left);
			__s_node	*parent = toDelete->parent;
			if (child != NULL)
				child->parent = parent;
			if (parent != NULL) {
				if (parent->left == toDelete)
					parent->left = child;
				else
					parent->right = child;
			}
			else
				_root = child;
			_allocator.destroy(toDelete);
			_allocator.deallocate(toDelete, 1);
		}

		void	_eraseTreeFix(__s_node *);
};

template <class Key, class T, class Compare, class Alloc>
bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs,
				const ft::map<Key,T,Compare,Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return (false);
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs,
				const ft::map<Key,T,Compare,Alloc>& rhs)
{
	return (!(lhs == rhs));
}

template <class Key, class T, class Compare, class Alloc>
bool operator< (const ft::map<Key,T,Compare,Alloc>& lhs,
				const ft::map<Key,T,Compare,Alloc>& rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class Key, class T, class Compare, class Alloc>
bool operator> (const ft::map<Key,T,Compare,Alloc>& lhs,
				const ft::map<Key,T,Compare,Alloc>& rhs)
{
	return (rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs,
				const ft::map<Key,T,Compare,Alloc>& rhs)
{
	return (!(rhs < lhs));
}

template <class Key, class T, class Compare, class Alloc>
bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs,
				const ft::map<Key,T,Compare,Alloc>& rhs)
{
	return (!(lhs < rhs));
}

}

namespace std
{
	template <class Key, class T, class Compare, class Alloc>
	void	swap(ft::map<Key, T, Compare, Alloc>& lhs,
				 ft::map<Key, T, Compare, Alloc>& rhs)
	{
		#if MAP_DEBUG_VERBOSE == true
			std::cout << _BLU"DEBUG: map: std::swap is specialized"RESET << std::endl;
		#endif
		lhs.swap(rhs);
	}
}

#include "map.tpp"

#endif
