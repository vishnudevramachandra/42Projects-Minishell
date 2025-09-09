/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 10:58:06 by swied             #+#    #+#             */
/*   Updated: 2025/09/09 15:21:00 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

/* not done yet */
int	builtin_exit(void)
{
	free_all_garbage();
	ft_putendl_fd("exit", 1);
	exit(0);
}
