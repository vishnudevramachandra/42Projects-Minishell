/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:55:50 by swied             #+#    #+#             */
/*   Updated: 2025/08/06 19:31:42 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

/* gets static garbage list so its the same list every time its called */
t_garbage_list *get_garbage_list(void)
{
    static t_garbage_list g_garbage = {NULL, NULL, 0};
    return &g_garbage;
}

/* goes through the list and frees every pointer via tmp + sets head and tail to NULL */
void free_all_garbage(void)
{
	t_garbage_node *current;
	t_garbage_node *tmp;
	t_garbage_list	*gc_list;

	gc_list = get_garbage_list();
	current = gc_list->head;
	while (current)
	{
		free(current->ptr);
		tmp = current;
		current = current->next;
		free(tmp);
	}
	gc_list->head = NULL;
	gc_list->tail = NULL;
	gc_list->size = 0;
}

/* creates new_node which ptr gets set to input + new_node->next gets set to NULL */
t_garbage_node	*create_gc_node(void *ptr)
{
	t_garbage_node	*new_node;

	new_node = malloc(sizeof(t_garbage_node));
	if (!new_node)
		return (ft_putstr_fd("minishell: malloc failed\n", 2), NULL);
	new_node->ptr = ptr;
	new_node->next = NULL;
	return (new_node);
}

/* If there is no node before it gets the head and tail | else the node gets the next one in the list */
void	add_gc_node(t_garbage_node *node)
{
	t_garbage_list *list;

	list = get_garbage_list();
	if (!list->head)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		list->tail->next = node;
		list->tail = node;
	}
	list->size++;
}

/* creates a ptr with the size of input and adds it to the gc_list */
void	*gc_malloc(size_t size)
{
	void			*ptr;	
	t_garbage_node	*new_node;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new_node = create_gc_node(ptr);
	add_gc_node(new_node);
	return (ptr);
}
