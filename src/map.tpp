/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.tpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 16:58:33 by pbremond          #+#    #+#             */
/*   Updated: 2022/09/07 13:30:02 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "map.hpp"

template <class Key, class T, class Compare, class Allocator>
ft::pair<typename ft::map<Key, T, Compare, Allocator>::iterator, bool>
ft::map<Key, T, Compare, Allocator>::insert(value_type const& val) // NOTE: value_type is a key/value pair!!!
{
	__s_node	*tree = _root;
	__s_node	*prev = NULL;
	bool	go_left = false; // Avoids extra comparison

	if (_root == NULL) { // No tree exists
		_root = new __s_node(val, NULL);
		return (ft::make_pair(iterator(_root), true));
	}
	while (tree != NULL)
	{
		prev = tree;
		if (key_compare(val.first(), tree->val.first()) == true) {
			tree = tree->left;
			go_left = true;
		}
		else if (key_compare(tree->val.first(), val.first()) == true) {
			tree = tree->right;
			go_left = false;
		}
		else // If two keys are equal, unable to insert
			return (ft::make_pair(iterator(tree), false));
	}
	if (go_left) {
		prev->left = new __s_node(val, prev);
		return (ft::make_pair(iterator(prev->left), true));
	}
	else {
		prev->right = new __s_node(val, prev);
		return (ft::make_pair(iterator(prev->right), true));
	}
}

// template <class Key, class T, class Compare, class Allocator>
// ft::pair<typename ft::map<Key, T, Compare, Allocator>::iterator, bool>
// ft::map<Key, T, Compare, Allocator>::insert(value_type const& val) // NOTE: value_type is a key/value pair!!!
// {
// 	optional<__s_node>	tree = _root;
// 	optional<__s_node>	prev;
// 	bool				go_left = false; // Avoids extra comparison

// 	if (!_root) { // No tree exists
// 		_root = __s_node(val, NULL);
// 		return (ft::make_pair(iterator(_root), true));
// 	}
// 	while (tree.has_value())
// 	{
// 		prev = tree;
// 		if (key_compare(val.first(), tree->val.first()) == true) {
// 			tree = tree->left;
// 			go_left = true;
// 		}
// 		else if (key_compare(tree->val.first(), val.first()) == true) {
// 			tree = tree->right;
// 			go_left = false;
// 		}
// 		else // If two keys are equal, unable to insert
// 			return (ft::make_pair(iterator(tree->val), false));
// 	}
// 	if (go_left) {
// 		prev->left = __s_node(val, prev);
// 		return (ft::make_pair(iterator(prev->left), true));
// 	}
// 	else {
// 		prev->right = __s_node(val, prev);
// 		return (ft::make_pair(iterator(prev->right), true));
// 	}
// }
