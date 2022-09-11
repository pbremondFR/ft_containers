/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.tpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 16:58:33 by pbremond          #+#    #+#             */
/*   Updated: 2022/09/11 16:59:44 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "map.hpp"

// ============================================================================================== //
// ------------------------------------------ ITERATOR ------------------------------------------ //
// ============================================================================================== //

template <class Key, class T, class Compare, class Allocator>
template <class U>
typename ft::map<Key, T, Compare, Allocator>::template __map_iterator<U>&
	ft::map<Key, T, Compare, Allocator>::__map_iterator<U>::operator++()
{
	if (_node->right != NULL) // NOTE: No need to edit this behaviour for end leaf, because end()++ is undefined
	{ // If there is a right child
		_node = _node->right;
		while (_node->left != NULL)
			_node = _node->left;
	}
	else
	{ // No right child, go back up until you go over a left child
		__s_node	*parent = _node->parent;
		while (parent != NULL && _node == parent->right) {
			_node = _node->parent;
			parent = parent->parent;
		}
		_node = parent;
	}
	return (*this);
}

template <class Key, class T, class Compare, class Allocator>
template <class U>
typename ft::map<Key, T, Compare, Allocator>::template __map_iterator<U>
	ft::map<Key, T, Compare, Allocator>::__map_iterator<U>::operator++(int)
{
	__map_iterator<U>	tmp(*this);
	this->operator++();
	return (tmp);
}

template <class Key, class T, class Compare, class Allocator>
template <class U>
typename ft::map<Key, T, Compare, Allocator>::template __map_iterator<U>&
	ft::map<Key, T, Compare, Allocator>::__map_iterator<U>::operator--()
{
	if (_node->left != NULL)
	{
		_node = _node->left;
		while (_node->right != NULL)
			_node = _node->right;
	}
	else
	{
		__s_node	*parent = _node->parent;
		while (parent != NULL && _node == parent->left) {
			_node = _node->parent;
			parent = parent->parent;
		}
		_node = parent;
	}
	return (*this);
}

template <class Key, class T, class Compare, class Allocator>
template <class U>
typename ft::map<Key, T, Compare, Allocator>::template __map_iterator<U>
	ft::map<Key, T, Compare, Allocator>::__map_iterator<U>::operator--(int)
{
	__map_iterator<U>	tmp(*this);
	this->operator--();
	return (tmp);
}

// ============================================================================================== //
// --------------------------------------- PUBLIC METHODS --------------------------------------- //
// ============================================================================================== //

template <class Key, class T, class Compare, class Allocator>
ft::map<Key, T, Compare, Allocator>::map(Compare const& comp, Allocator const& alloc)
	: _root(NULL), _compare(comp), _allocator(alloc)
{
	_endLeaf = _allocator.allocate(1); // No need to construct object, just initialize pointers and color
	_endLeaf->colour = __s_node::BLACK;
	_endLeaf->parent = NULL;
	_endLeaf->left = NULL;
	_endLeaf->right = NULL;
	_root = _endLeaf; // Maybe this is the solution to avoid ugly size checking with begin() ?
					  // Since I'd need to return end() with size 0...
}

template <class Key, class T, class Compare, class Allocator>
template <class InputIt>
ft::map<Key, T, Compare, Allocator>::map(InputIt first, InputIt last,
										 Compare const& comp,
										 Allocator const& alloc,
										 typename enable_if< !is_fundamental<InputIt>::value, int >::type)
	: _root(NULL), _compare(comp), _allocator(alloc)
{
	this->insert(first, last);
}

template <class Key, class T, class Compare, class Allocator>
ft::map<Key, T, Compare, Allocator>::map(map const& src) : _root(NULL), _compare(src._compare),
	_allocator(src._allocator)
{
	for (map::const_iterator it = src.begin(); it != src.end(); ++it)
	{
		this->insert(*it);
	}
}

template <class Key, class T, class Compare, class Allocator>
ft::map<Key, T, Compare, Allocator>&
	ft::map<Key, T, Compare, Allocator>::operator=(map const& src)
{
	this->clear();
	this->_allocator = src._allocator;
	this->_compare = src._compare;
	this->insert(src.begin(), src.end());
	return (*this);
}

template <class Key, class T, class Compare, class Allocator>
ft::pair<typename ft::map<Key, T, Compare, Allocator>::iterator, bool>
	ft::map<Key, T, Compare, Allocator>::insert(value_type const& val) // NOTE: value_type is a key/value pair!!!
{
	__s_node	*tree = _root;
	__s_node	*prev = NULL;
	bool		go_left = false; // Avoids extra _compare() call

	if (_root == _endLeaf) {
		_root = _allocator.allocate(1);
		_allocator.construct(_root, __s_node(val, NULL));
		_repositionEndLeaf(_root);
		return (_correctInsertion(_root, iterator(_root)));
	}
	while (tree != NULL && tree != _endLeaf)
	{
		prev = tree;
		if (this->_compare(val.first, tree->val.first) == true) {
			tree = tree->left;
			go_left = true;
		}
		else if (this->_compare(tree->val.first, val.first) == true) {
			tree = tree->right;
			go_left = false;
		}
		else // If two keys are equal, unable to insert
			return (ft::make_pair(iterator(tree), false));
	}
	if (go_left) {
		prev->left = _allocator.allocate(1);
		_allocator.construct(prev->left, __s_node(val, prev));
		return (_correctInsertion(prev->left, iterator(prev->left)));
	}
	else {
		prev->right = _allocator.allocate(1);
		_allocator.construct(prev->right, __s_node(val, prev));
		if (tree == _endLeaf) // Repositions end leaf correctly
			_repositionEndLeaf(prev->right);
		return (_correctInsertion(prev->right, iterator(prev->right)));
	}
}

template <class Key, class T, class Compare, class Allocator>
typename ft::map<Key, T, Compare, Allocator>::iterator
	ft::map<Key, T, Compare, Allocator>::insert(iterator hint, value_type const& val)
{
	if (_compare(val.first, hint->first) == true && hint._node->left == NULL)
	{
		hint._node->left = _allocator.allocate(1);
		_allocator.construct(hint._node->left, __s_node(val, hint._node));
		return (_correctInsertion(hint._node->left, hint._node->left).first);
	}
	else if (_compare(hint->first, val.first) == true && hint._node->right == NULL)
	{
		hint._node->right = _allocator.allocate(1);
		_allocator.construct(hint._node->right, __s_node(val, hint._node));
		if (hint._node == _endLeaf)
			_repositionEndLeaf(hint._node);
		return (_correctInsertion(hint._node->right, hint._node->right).first);
	}
	else
		return (this->insert(val).first);
}

template <class Key, class T, class Compare, class Allocator>
template <class InputIt>
typename ft::enable_if
<
	!ft::is_fundamental<InputIt>::value,
	void
>::type
	ft::map<Key, T, Compare, Allocator>::insert(InputIt first, InputIt last)
{
	for (; first != last; ++first)
	{
		this->insert(*first);
	}
}

template <class Key, class T, class Compare, class Allocator>
void	ft::map<Key, T, Compare, Allocator>::swap(map& other)
{
	__s_node *tmpRoot = other._root;
	other._root = this->_root;
	this->_root = tmpRoot;

	_Alloc tmpAlloc = other._allocator;
	other._allocator = this->_allocator;
	this->_allocator = tmpAlloc;

	Compare tmpComp = other._compare;
	other._compare = this->_compare;
	this->_compare = tmpComp;

	__s_node *tmpEndLeaf = other._endLeaf;
	other._endLeaf = this->_endLeaf;
	this->_endLeaf = tmpEndLeaf;
}

template <class Key, class T, class Compare, class Allocator>
T&	ft::map<Key, T, Compare, Allocator>::at(Key const& key)
{
	iterator	target = this->find(key);
	if (target != this->end())
		return (target->second);
	else
		throw (std::out_of_range("map::at: key not found"));
}

template <class Key, class T, class Compare, class Allocator>
T const&	ft::map<Key, T, Compare, Allocator>::at(Key const& key) const
{
	const_iterator	target = this->find(key);
	if (target != this->end())
		return (target->second);
	else
		throw (std::out_of_range("map::at: key not found"));
}

template <class Key, class T, class Compare, class Allocator>
T&	ft::map<Key, T, Compare, Allocator>::operator[](Key const& key)
{
	iterator	target = this->find(key);
	if (target != this->end())
		return (target->second);
	else
		return (this->insert(ft::make_pair(key, T())).first->second);
}

template <class Key, class T, class Compare, class Allocator>
typename ft::map<Key, T, Compare, Allocator>::size_type
	ft::map<Key, T, Compare, Allocator>::count(Key const& key) const
{
	return (this->find(key) == this->end() ? 0 : 1);
}

template <class Key, class T, class Compare, class Allocator>
typename ft::map<Key, T, Compare, Allocator>::iterator
	ft::map<Key, T, Compare, Allocator>::find(Key const& key)
{
	__s_node	*node = _root;

	while (node != NULL)
	{
		if (_compare(key, node->val.first) == true)
			node = node->left;
		else if (_compare(node->val.first, key) == true)
			node = node->right;
		else
			return (iterator(node));
	}
	return (this->end());
}

template <class Key, class T, class Compare, class Allocator>
typename ft::map<Key, T, Compare, Allocator>::const_iterator
	ft::map<Key, T, Compare, Allocator>::find(Key const& key) const
{
	__s_node	*node = _root;

	while (node != NULL)
	{
		if (_compare(key, node->val.first) == true)
			node = node->left;
		else if (_compare(node->val.first, key) == true)
			node = node->right;
		else
			return (const_iterator(node));
	}
	return (this->end());
}

template <class Key, class T, class Compare, class Allocator>
void	ft::map<Key, T, Compare, Allocator>::clear(void)
{
	this->_postfix_dealloc(_root);
	_root = _endLeaf;
}

template <class Key, class T, class Compare, class Allocator>
typename ft::map<Key, T, Compare, Allocator>::iterator
	ft::map<Key, T, Compare, Allocator>::lower_bound(Key const& key)
{
	for (iterator it = this->begin(); it != this->end(); ++it) {
		if (_compare(it->first, key) == false)
			return (it);
	}
	return (this->end());
}

template <class Key, class T, class Compare, class Allocator>
typename ft::map<Key, T, Compare, Allocator>::const_iterator
	ft::map<Key, T, Compare, Allocator>::lower_bound(Key const& key) const
{
	for (const_iterator it = this->begin(); it != this->end(); ++it) {
		if (_compare(it->first, key) == false)
			return (it);
	}
	return (this->end());
}

template <class Key, class T, class Compare, class Allocator>
typename ft::map<Key, T, Compare, Allocator>::iterator
	ft::map<Key, T, Compare, Allocator>::upper_bound(Key const& key)
{
	for (iterator it = this->begin(); it != this->end(); ++it) {
		if (_compare(key, it->first) == true)
			return (it);
	}
	return (this->end());
}

template <class Key, class T, class Compare, class Allocator>
typename ft::map<Key, T, Compare, Allocator>::const_iterator
	ft::map<Key, T, Compare, Allocator>::upper_bound(Key const& key) const
{
	for (const_iterator it = this->begin(); it != this->end(); ++it) {
		if (_compare(key, it->first) == true)
			return (it);
	}
	return (this->end());
}

// ============================================================================================== //
// ------------------------------------- PRIVATE FUNCTIONS -------------------------------------- //
// ============================================================================================== //

template <class Key, class T, class Compare, class Allocator>
void	ft::map<Key, T, Compare, Allocator>::_postfix_dealloc(__s_node *root)
{
	if (root == NULL || root == _endLeaf)
		return ;
	_postfix_dealloc(root->left);
	_postfix_dealloc(root->right);
	#if MAP_DEBUG_VERBOSE == true
		std::cerr << BBLU"DEBUG: _postfix_dealloc(): "RESET
			<< root->val.first << '\t' << root->val.second << std::endl;
	#endif
	_allocator.destroy(root);
	_allocator.deallocate(root, 1);
}

template <class Key, class T, class Compare, class Allocator>
int	ft::map<Key, T, Compare, Allocator>::_checkInsertValidity(__s_node *node) const
{
	if (node->parent == NULL)
		return (CORRECT_ROOT);
	else if (node->parent->colour == __s_node::BLACK)
		return (CORRECT_NOTHING);
	else if (node->uncle() != NULL && node->uncle()->colour == __s_node::RED)
		return (CORRECT_COLOR);
	else // Uncle is black when it is NULL
		return (CORRECT_ROTATE);
}

// &retval is the value to be returned, which may not be an iterator to the same node at *node,
// due to function recursiveness.
template <class Key, class T, class Compare, class Allocator>
ft::pair<typename ft::map<Key, T, Compare, Allocator>::iterator, bool>
	ft::map<Key, T, Compare, Allocator>::_correctInsertion(__s_node *node, iterator const& retval)
{
	#if MAP_DEBUG_VERBOSE == true
		std::cout << std::endl;
		debug_printByLevel(node->val.first);
	#endif
	switch (_checkInsertValidity(node))
	{
		case CORRECT_ROOT:
			#if MAP_DEBUG_VERBOSE == true
				std::cout << _BLU"DEBUG: insert case 1 for node " << node->val.first
					<< " (recolor root)"RESET << std::endl;
			#endif
			node->colour = __s_node::BLACK;
			return (ft::pair<iterator, bool>(retval, true));

		case CORRECT_NOTHING:
			#if MAP_DEBUG_VERBOSE == true
				std::cout << _BLU"DEBUG: insert case 2 for node " << node->val.first
					<< " (do nothing)"RESET << std::endl;
			#endif
			return (ft::pair<iterator, bool>(retval, true));

		case CORRECT_COLOR:
			#if MAP_DEBUG_VERBOSE == true
				std::cout << _BLU"DEBUG: insert case 3 for node " << node->val.first
					<< " (recolor parent, uncle and grandparent)"RESET << std::endl;
			#endif

			node->parent->colour = __s_node::BLACK;
			node->uncle()->colour = __s_node::BLACK;
			node->parent->parent->colour = __s_node::RED;
			return (_correctInsertion(node->parent->parent, retval));

		case CORRECT_ROTATE:
			#if MAP_DEBUG_VERBOSE == true
				std::cout << _BLU"DEBUG: insert case 4 for node " << node->val.first
					<< " (rotations and stuff)"RESET << std::endl;
			#endif

			_correctInsertion_rotate(node);
			return (ft::pair<iterator, bool>(retval, true));
	}
	throw (std::logic_error("map: insert: _correctInsertion: unexpected fatal logic error"));
}

template <class Key, class T, class Compare, class Allocator>
void	ft::map<Key, T, Compare, Allocator>::_correctInsertion_rotate(__s_node *node)
{
	__s_node	*grandparent = node->parent->parent;

	if (grandparent->left && grandparent->left->right
		&& node == grandparent->left->right) {
		node->parent->rotateLeft(&_root);
		node = node->left;
	}
	else if (grandparent->right && grandparent->right->left
		&& node == grandparent->right->left) {
		node->parent->rotateRight(&_root);
		node = node->right;
	}
	grandparent = node->parent->parent;
	if (node == node->parent->left)
		grandparent->rotateRight(&_root);
	else
		grandparent->rotateLeft(&_root);
	node->parent->colour = __s_node::BLACK;
	grandparent->colour = __s_node::RED;
}

// ============================================================================================== //
// -------------------------------------- DEBUG FUNCTIONS --------------------------------------- //
// ============================================================================================== //

#if MAP_DEBUG_VERBOSE == true

	template <class Key, class T, class Compare, class Allocator>
	void	ft::map<Key, T, Compare, Allocator>::debug_leftRotate(Key const& key)
	{
		iterator	target = this->find(key);
		if (target == this->end())
			throw (std::logic_error("DEBUG: debug_leftRotate: invalid key"));
		std::cerr << BBLU"DEBUG:"BRED" left rotate ("<<key<<')'<<RESET << std::endl;
		target._node->rotateLeft(&_root);
	}

	template <class Key, class T, class Compare, class Allocator>
	void	ft::map<Key, T, Compare, Allocator>::debug_rightRotate(Key const& key)
	{
		iterator	target = this->find(key);
		if (target == this->end())
			throw (std::logic_error("DEBUG: debug_rightRotate: invalid key"));
		std::cerr << BBLU"DEBUG:"BGRN" right rotate ("<<key<<')'<<RESET << std::endl;
		target._node->rotateRight(&_root);
	}

	template <class Key, class T, class Compare, class Allocator>
	void	ft::map<Key, T, Compare, Allocator>::debug_printByLevel() const
	{
		std::queue<__s_node *>	queue;
		queue.push(_root);
		std::cerr << BLUB"  "RESET BBLU"DEBUG: Print by level"RESET << std::endl;
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
	template <class Key, class T, class Compare, class Allocator>
	void	ft::map<Key, T, Compare, Allocator>::debug_printByLevel(Key const& key) const
	{
		std::queue<__s_node *>	queue;
		queue.push(_root);
		std::cerr << BLUB"  "RESET BBLU"DEBUG: Print by level"RESET << std::endl;
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
	template <class Key, class T, class Compare, class Allocator>
	void	ft::map<Key, T, Compare, Allocator>::debug_printFamily(Key const& key) const
	{
		const_iterator	target = this->find(key);
		if (target == this->end())
			throw (std::logic_error("DEBUG: debug_printFamily: invalid key"));
		std::cerr << BBLU"DEBUG: Family of node " << key << ": \n"RESET
			<< _YEL"Parent: "RESET
				<< (target._node->parent ? target._node->parent->val.first : 99999) << '\n'
			<< _RED"Left: "RESET
				<< (target._node->left ? target._node->left->val.first : 99999) << '\n'
			<< _GRN"Right: "RESET
				<< (target._node->right ? target._node->right->val.first : 99999) << std::endl;
	}

#endif
