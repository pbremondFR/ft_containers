/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.tpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 16:58:33 by pbremond          #+#    #+#             */
/*   Updated: 2022/09/08 21:36:33 by pbremond         ###   ########.fr       */
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
		return (ft::make_pair(iterator(_root), true));
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
		return (ft::make_pair(iterator(prev->left), true));
	}
	else {
		prev->right = _allocator.allocate(1);
		_allocator.construct(prev->right, __s_node(val, prev));
		return (ft::make_pair(iterator(prev->right), true));
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
			node = node->left;
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
			node = node->left;
		else
			return (const_iterator(node));
	}
	return (this->end());
}

template <class Key, class T, class Compare, class Allocator>
void	ft::map<Key, T, Compare, Allocator>::clear(void)
{
	this->_postfix_clear(_root);
	_root = NULL;
}

template <class Key, class T, class Compare, class Allocator>
void	ft::map<Key, T, Compare, Allocator>::_postfix_clear(__s_node *root)
{
	if (root == NULL)
		return ;
	_postfix_clear(root->left);
	_postfix_clear(root->right);
	if (MAP_DEBUG_VERBOSE) {
		std::cerr << "DEBUG: _postfix_clear(): " << root->val.first << '\t' << root->val.second << std::endl;
		if (root->optbrother().has_value()) {
			std::cerr << "brother has value !\t" << root->optbrother().value()->val.first << std::endl;
		}
		else
			std::cerr << "brother has NO value !\n";
	}
	_allocator.destroy(root);
	_allocator.deallocate(root, 1);
}
