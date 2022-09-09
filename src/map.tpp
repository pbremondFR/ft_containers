/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.tpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 16:58:33 by pbremond          #+#    #+#             */
/*   Updated: 2022/09/09 15:41:43 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "map.hpp"

template <class Key, class T, class Compare, class Allocator>
template <class U>
typename ft::map<Key, T, Compare, Allocator>::template __map_iterator<U>&
ft::map<Key, T, Compare, Allocator>::__map_iterator<U>::operator++()
{
	if (_node->right != NULL)
	{
		_node = _node->right;
		while (_node->left != NULL)
			_node = _node->left;
	}
	else
	{
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

// template <class Key, class T, class Compare, class Allocator>
// template <class InputIt>
// ft::map<Key, T, Compare, Allocator>::map(InputIt first, InputIt last,
// 										Compare const& comp,
// 										Allocator const& alloc,
// 										typename enable_if< !is_fundamental<InputIt>::value, int >::type)
// {
// 	// TODO
// }

// template <class Key, class T, class Compare, class Allocator>
// ft::map<Key, T, Compare, Allocator>::map(map const& src)
// {
// 	// TODO
// }

template <class Key, class T, class Compare, class Allocator>
ft::pair<typename ft::map<Key, T, Compare, Allocator>::iterator, bool>
ft::map<Key, T, Compare, Allocator>::insert(value_type const& val) // NOTE: value_type is a key/value pair!!!
{
	__s_node	*tree = _root;
	__s_node	*prev = NULL;
	bool	go_left = false; // Avoids extra _compare() call

	if (_root == NULL) {
		_root = _allocator.allocate(1);
		_allocator.construct(_root, __s_node(val, NULL));
		// _root->colour = __s_node::BLACK; // NOTE: Should this be done there or in the correction later ?
		// return (ft::make_pair(iterator(_root), true));
		return (_correctInsertion(_root, iterator(_root)));
	}
	while (tree != NULL)
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
		// return (ft::make_pair(iterator(prev->left), true));
		return (_correctInsertion(prev->left, iterator(prev->left)));
	}
	else {
		prev->right = _allocator.allocate(1);
		_allocator.construct(prev->right, __s_node(val, prev));
		// return (ft::make_pair(iterator(prev->right), true));
		return (_correctInsertion(prev->right, iterator(prev->right)));
	}
}

template <class Key, class T, class Compare, class Allocator>
T&	ft::map<Key, T, Compare, Allocator>::at(Key const& key)
{
	iterator	target = this->find(key);
	if (target != this->end())
		return (target.second);
	else
		throw (std::out_of_range("map::at: key not found"));
}

template <class Key, class T, class Compare, class Allocator>
T const&	ft::map<Key, T, Compare, Allocator>::at(Key const& key) const
{
	const_iterator	target = this->find(key);
	if (target != this->end())
		return (target.second);
	else
		throw (std::out_of_range("map::at: key not found"));
}

template <class Key, class T, class Compare, class Allocator>
T&	ft::map<Key, T, Compare, Allocator>::operator[](Key const& key)
{
	iterator	target = this->find(key);
	if (target != this->end())
		return (target.second);
	else
		return (this->insert(key, T()).first->second);
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
	_root = NULL;
}

template <class Key, class T, class Compare, class Allocator>
void	ft::map<Key, T, Compare, Allocator>::_postfix_dealloc(__s_node *root)
{
	if (root == NULL)
		return ;
	_postfix_dealloc(root->left);
	_postfix_dealloc(root->right);
	if (MAP_DEBUG_VERBOSE) {
		std::cerr << BBLU"DEBUG: _postfix_dealloc(): "RESET
			<< root->val.first << '\t' << root->val.second << std::endl;
		// if (root->optbrother().has_value()) {
		// 	std::cerr << "brother has value !\t" << root->optbrother().value()->val.first << std::endl;
		// }
		// else
		// 	std::cerr << "brother has NO value !\n";
	} // BUG: These brother debug options produce invalid reads. That's OK, they won't be there for long.
	_allocator.destroy(root);
	_allocator.deallocate(root, 1);
}

template <class Key, class T, class Compare, class Allocator>
ft::pair<typename ft::map<Key, T, Compare, Allocator>::iterator, bool>
ft::map<Key, T, Compare, Allocator>::_correctInsertion(__s_node *node, iterator const& retval)
{
	std::cout << std::endl;
	debug_printByLevel(node->val.first);
	switch (_checkInsertValidity(node))
	{
		case 1:
			std::cout << _BLU"DEBUG: insert case 1 for node " << node->val.first
				<< " (recolor root)" << RESET << std::endl;

			node->colour = __s_node::BLACK;
			return (ft::pair<iterator, bool>(retval, true));
		case 2:
			std::cout << _BLU"DEBUG: insert case 2 for node " << node->val.first
				<< " (do nothing)" << RESET << std::endl;

			return (ft::pair<iterator, bool>(retval, true));
		case 3:
			std::cout << _BLU"DEBUG: insert case 3 for node " << node->val.first
				<< " (recolor parent, uncle and grandparent)" << RESET << std::endl;

			node->parent->colour = __s_node::BLACK;
			node->uncle()->colour = __s_node::BLACK;
			node->parent->parent->colour = __s_node::RED;
			return (_correctInsertion(node->parent->parent, retval));
		case 4:
			std::cout << _BLU"DEBUG: insert case 4 for node " << node->val.first
				<< " (rotations and stuff)" << RESET << std::endl;

			__s_node	*grandparent = node->parent->parent;
			if (grandparent->left->right && node == grandparent->left->right) {
				node->parent->rotateLeft(&_root);
				node = node->left;
			}
			else if (grandparent->left->right && node == grandparent->right->left) {
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
			return (ft::pair<iterator, bool>(retval, true));
	}
	throw (std::logic_error("what the fuck"));
}

template <class Key, class T, class Compare, class Allocator>
int	ft::map<Key, T, Compare, Allocator>::_checkInsertValidity(__s_node *node) const
{
	if (node->parent == NULL)
		return (1);
	else if (node->parent->colour == __s_node::BLACK)
		return (2);
	else if (node->uncle() != NULL && node->uncle()->colour == __s_node::RED)
		return (3);
	else // Uncle is black when it is NULL
		return (4);
}
