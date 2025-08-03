/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 23:04:38 by swied             #+#    #+#             */
/*   Updated: 2025/08/03 11:00:01 by swied            ###   ########.fr       */
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
# include <fcntl.h>
# include "libft/libft.h"
# include "garbage_collector.h"
# include "minishell.h"

//execute_utils.c
int		ft_strcmp(const char *s1, const char *s2);

//builtins
int		builtin_pwd(void);
int		builtin_echo(char **args);
int		builtin_cd(char **args, char ***env);
int		builtin_env(char **envp);
int		builtin_exit(int status);

//env.c
int		update_env_var(char ***env, char *key, char *value);
int		add_env_var(char ***env, char *new_entry, int i);

//get_path.c
char	*get_total_path(char **envp);
char	*get_correct_path_second(char **path_array, char *suffix);
char	*get_correct_path(char *cmd, char **envp);

//builtin.c
int		execute_builtin(t_cmd_node *cmd_node, char **envp);

//execute.c
int		execute_cmd(t_cmd_node *cmd_node, char **envp);
int		execute_cmd_or_builtin(t_cmd_node *cmd_node, char **envp);
int		execute_loop(t_cmd_list *cmd_list, char **envp);
int		execute_cmd_loop(t_cmd_node *cmd_node, char **envp);

//redirect.c
int 	redirect(t_cmd_node *cmd_node);
int		open_redirects(t_cmd_node *cmd_node);
void	check_fd(t_cmd_node *cmd_node);

//pipes.c
int		execute_pipes(t_cmd_list *cmd_list, char **envp);
void	close_pipes(t_cmd_list *cmd_list, t_cmd_node *current, int *pipefd, int i);
void	setup_pipes(t_cmd_list *cmd_list, int *pipefd, int i);

//heredoc_utils.c
t_hd_line	*create_hd_line(char *content);
t_hd_node	*create_hd_node(char *lim);
void		add_line_to_heredoc(t_hd_node *hd_node, char *line);
int			is_delimiter(char *line, char *delimiter);
int			create_heredoc_fd(t_hd_node *hd_node);
int			write_heredoc_to_pipe(t_hd_node *hd_node, int write_fd);
int			check_exit_status(pid_t child_pid, t_mini *mini);

#endif