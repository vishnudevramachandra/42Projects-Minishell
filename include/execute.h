/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 23:04:38 by swied             #+#    #+#             */
/*   Updated: 2025/07/16 18:49:57 by swied            ###   ########.fr       */
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
# include "garbage_collector.h"
# include "minishell.h"

typedef struct s_cmd {
	char			**args; // args for execve (argv[0] = "ls" | argv[1] = "-la" | argv[2] = "NULL")
	int				pipe_in; // If input comes from pipe -> pipe_in = 1
	int				pipe_out; // If output goes into pipe -> pipe_out = 1
	struct s_cmd	*next; // Not fix yet if list of cmd like this makes sense
}	t_cmd;

typedef struct s_pipe
{
	int	fd[2]; // in and out of pipe
}	t_pipe;

//execute_utils.c
int	ft_strcmp(const char *s1, const char *s2);

//builtins
int	builtin_pwd(void);
int	builtin_echo(char **args);
int	builtin_cd(char **args, char ***env);

//env.c
int	update_env_var(char ***env, char *key, char *value);
int	add_env_var(char ***env, char *new_entry, int i);

#endif