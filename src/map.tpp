/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.tpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 16:58:33 by pbremond          #+#    #+#             */
/*   Updated: 2022/07/14 18:59:47 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "map.hpp"

template <class Key, class T, class Compare, class Allocator>
ft::pair<typename ft::map<Key, T, Compare, Allocator>::iterator, bool>
ft::map<Key, T, Compare, Allocator>::insert(value_type const& val)
{
	s_node	*tree = _root;
	s_node	*prev = NULL;
	bool	go_left = false;

	while (tree != NULL)
	{
		prev = tree;
		if (Compare(val, tree->val) == true) {
			tree = tree->left;
			go_left = true;
		}
		else if (Compare(tree->val, val) == true) {
			tree = tree->right;
			go_left = false;
		}
		else
			return (ft::pair(iterator, false))
	}
	if (prev == NULL) {
		_root = new s_node(val, NULL);
		return (ft::pair(iterator(_root), true));
	}
	else if (go_left) {
		prev->left = new s_node(val, prev);
		return (ft::pair(iterator(prev->left), true));
	}
	else {
		prev->right = new s_node(val, prev);
		return (ft::pair(iterator(prev->right), true));
	}
}
