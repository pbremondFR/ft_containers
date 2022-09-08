/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.tpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 16:58:33 by pbremond          #+#    #+#             */
/*   Updated: 2022/09/08 18:35:32 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "map.hpp"

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
	bool	go_left = false; // Avoids extra Compare() call

	if (_root == NULL) { // No tree exists
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
void	ft::map<Key, T, Compare, Allocator>::clear(void)
{
	this->_postfix_clear(_root);
	_root = NULL;
}
