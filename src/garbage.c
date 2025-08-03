/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:55:50 by swied             #+#    #+#             */
/*   Updated: 2025/08/03 12:02:33 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

t_garbage **get_garbage_list(void)
{
    static t_garbage *g_garbage = NULL;
    return &g_garbage;
}

void add_to_garbage(void *ptr)
{
	t_garbage *new_node;

	new_node = malloc(sizeof(t_garbage));
	if (!new_node)
	{
		printf("Malloc failed\n");
		return;
	}
	new_node->ptr = ptr;
	new_node->next = *get_garbage_list();
	*get_garbage_list() = new_node;
	return;
}

void free_all_garbage(void)
{
	t_garbage *current;
	t_garbage *tmp;

	current = *get_garbage_list();
	while (current)
	{
		free(current->ptr);
		tmp = current;
		current = current->next;
		free(tmp);
	}
	*get_garbage_list() = NULL;
}

void	*gc_malloc(size_t size)
{
	void	*ret;	
	ret = malloc(size);
	if (!ret)
		return (NULL);
	add_to_garbage(ret);
	return (ret);
}
