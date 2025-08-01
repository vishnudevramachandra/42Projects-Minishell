/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:42:10 by swied             #+#    #+#             */
/*   Updated: 2025/04/04 18:03:19 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>

int	connect_lines(char *buff, char **new_line)
{
	char	*temp;
	size_t	i;

	i = 0;
	if (!*new_line)
	{
		*new_line = malloc(1);
		if (!*new_line)
			return (-1);
		(*new_line)[0] = '\0';
	}
	temp = ft_strjoin_gnl(*new_line, buff);
	free(*new_line);
	if (temp == NULL)
		return (-1);
	*new_line = temp;
	while ((*new_line)[i] != '\0')
	{
		if ((*new_line)[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*new_line;
	int			read_bytes;
	int			flag;

	new_line = NULL;
	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buff[0] == '\0')
		{
			read_bytes = read(fd, buff, BUFFER_SIZE);
			if (read_bytes == -1)
				return (free_line(new_line));
			if (read_bytes == 0)
				return (new_line);
		}
		flag = connect_lines(buff, &new_line);
		delete_buff(buff);
		if (flag == 1)
			return (new_line);
		if (flag == -1)
			return (NULL);
	}
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("textfile1.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	close(fd);
// 	return (0);
// }
