/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:50:34 by swied             #+#    #+#             */
/*   Updated: 2025/08/05 17:26:01 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

typedef struct s_garbage_node
{
	void *ptr;
	struct s_garbage_node *next;
}	t_garbage_node;

typedef struct s_garbage_list
{
	t_garbage_node	*head;
	t_garbage_node	*tail;
	size_t			size;
}	t_garbage_list;

#endif