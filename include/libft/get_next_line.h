/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:35:59 by swied             #+#    #+#             */
/*   Updated: 2025/07/31 18:50:12 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

typedef struct s_list
{
	char	test;
}	t_list;

char	*get_next_line(int fd);
int		connect_lines(char *buff, char **new_line);
// size_t	ft_strlcpy(char *dest, const char *src, unsigned int size);
size_t	ft_strlen_gnl(const char *s);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
void	delete_buff(char *buff);
char	*free_line(char *new_line);

#endif