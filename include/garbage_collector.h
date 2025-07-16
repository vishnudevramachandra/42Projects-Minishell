/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:50:34 by swied             #+#    #+#             */
/*   Updated: 2025/07/15 00:59:25 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

typedef struct s_garbage
{
	void *ptr;
	struct s_garbage *next;
} t_garbage;

t_garbage **get_garbage_list(void);
void 		add_to_garbage(void *ptr);
void 		free_all_garbage(void);

#endif