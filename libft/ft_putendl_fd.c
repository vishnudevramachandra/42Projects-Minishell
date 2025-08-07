/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:20:43 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/18 14:34:15 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	len;
	char	nl;

	len = ft_strlen(s);
	write(fd, s, len);
	nl = '\n';
	write(fd, &nl, 1);
}

// int	main(void)
// {
// 	ft_putendl_fd("abc", 1);
// 	return (0);
// }