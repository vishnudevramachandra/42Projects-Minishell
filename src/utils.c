/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:34:02 by swied             #+#    #+#             */
/*   Updated: 2025/09/11 13:18:42 by swied            ###   ########.fr       */
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
	int	fd;

	i = 3;
	while (i < 1023)
	{
		if (check_if_fd_open(i) == 0)
			close(i);
		i++;
	}
	fd = open("/dev/tty", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	fd = open("/dev/tty", O_WRONLY);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	fd = open("/dev/tty", O_WRONLY);
	dup2(fd, STDERR_FILENO);
	close(fd);
	return (-1);
}

int	get_exit_stauts(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
