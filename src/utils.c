/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:34:02 by swied             #+#    #+#             */
/*   Updated: 2025/09/25 11:50:57 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"
#include <sys/stat.h>
#include <sys/types.h>

int	check_if_fd_open(int fd)
{
	struct stat	st;

	return (fstat(fd, &st));
}

int	reset_stds(void)
{
	int	i;

	i = 3;
	while (i < 1023)
	{
		if (check_if_fd_open(i) == 0)
			close(i);
		i++;
	}
	return (0);
}

int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
