/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 21:03:13 by swied             #+#    #+#             */
/*   Updated: 2025/08/05 21:03:25 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int	free_node(t_garbage_list *gc_list, void *ptr)
{
	t_garbage_node	*current;
	t_garbage_node	*prev;

	if (!gc_list)
		return (0);
	prev = gc_list->head;
	current = prev->next;
	while(current)
	{
		if (current->ptr == ptr)
		{
			prev->next = current->next;
			if (current == gc_list->tail)
				gc_list->tail = prev;
			free(current->ptr);
			free(current);
			gc_list->size--;
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

int	free_head_node(t_garbage_list *gc_list)
{
	t_garbage_node	*current;

	current = gc_list->head;
	gc_list->head = gc_list->head->next;
	if (!gc_list->head)
		gc_list->tail = NULL;
	free(current->ptr);
	free(current);
	gc_list->size--;
	return (1);
}

int	gc_free(void *ptr)
{
	t_garbage_list	*gc_list;

	gc_list = get_garbage_list();
	if (!ptr || !gc_list->head)
		return (0);
	if (gc_list->head->ptr == ptr)
	{
		if (!free_head_node(gc_list))
			return (0);
	}
	else
	{
		ft_putstr_fd("else\n", 1);
		if (!free_node(gc_list, ptr))
			return (0);
	}
	return (1);
}

int	add_to_gc(void *ptr)
{
	t_garbage_node	*new_node;

	if (!ptr)
		return (0);
	new_node = create_gc_node(ptr);
	add_gc_node(new_node);
	return (1);
}