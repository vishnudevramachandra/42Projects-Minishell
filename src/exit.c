/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 10:58:06 by swied             #+#    #+#             */
/*   Updated: 2025/09/20 05:32:45 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

static int	is_numstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

/* not done yet */
int	builtin_exit(char **args)
{
	int	exit_code;

	exit_code = 0;
	ft_putendl_fd("exit", 1);
	if (args && args[1])
	{
		if (!is_numstr((args[1])))
		{
			free_all_garbage();
			rl_clear_history();
			exit(2);
		}
		exit_code = ft_atoi(args[1]);
		if (args[2])
		{
			ft_putendl_fd("exit: too many arguments", 2);
			return (1);
		}
	}
	free_all_garbage();
	rl_clear_history();
	exit(exit_code);
}
