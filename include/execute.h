/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 23:04:38 by swied             #+#    #+#             */
/*   Updated: 2025/07/14 23:42:09 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	EXECUTE_H
# define EXECUTE_H
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "libft/libft.h"

typedef struct s_data {
	char	*cmd;
	char	*env;

}	t_data;

#endif