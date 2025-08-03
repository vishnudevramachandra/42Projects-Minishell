/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 01:40:52 by swied             #+#    #+#             */
/*   Updated: 2025/08/03 15:08:34 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		printf("getcwd failed\n");
		return (1);
	}
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	return (free(cwd), 0);
}
