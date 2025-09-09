/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 23:04:38 by swied             #+#    #+#             */
/*   Updated: 2025/09/09 16:41:20 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	EXECUTE_H
# define EXECUTE_H
# define _GNU_SOURCE
# define _POSIX_C_SOURCE 200809L
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include "libft/libft.h"
# include "garbage_collector.h"
# include "minishell.h"

//execute_utils.c
int		ft_strcmp(const char *s1, const char *s2);

//builtins
int		builtin_pwd(void);
int		builtin_echo(char **args);
int		builtin_cd(char **args, t_env_list *env_list);
int		builtin_env(t_env_list *env_list);
int		builtin_exit(void);
int		builtin_export(t_env_list *env_list, t_cmd_node *cmd_node);
int		builtin_unset(t_env_list *env_list, t_cmd_node *cmd_node);

//env.c
int		update_env_var(char ***env, char *key, char *value);
int		add_env_var(t_env_list *env_list, char *var, char *val);
int		print_env(t_env_list *env_list);
char	*get_env_value(t_env_list *env_list, char *var);
int		set_env_var(t_env_list *env_list, char *var, char *val);

//export.c
void	    print_export(t_env_list *env_list, char **env_array, int i);
char	    **create_export_list(t_env_list *env_list);
void	    bubblesort_array(char **env_array);
void	    free_export_array(char **array, int i);

//echo.c
int	        is_n_flag(char *arg);

//env_list.c
t_env_list	*fill_env_list(char **envp);

//list_to_dblarray.c
char		**list_to_dblarray(t_env_list *env_list);
int			create_env(char *var, char *value, char **array, int i);
char		**free_env_array(char **array, int i);

//get_path.c
char		*get_total_path(char **envp);
char		*get_correct_path_second(char **path_array, char *suffix);
char		*get_correct_path(char *cmd, char **envp);

//builtin.c
int			execute_builtin(t_cmd_node *cmd_node, t_env_list *env_list);

//execute.c
int			execute_cmd(t_cmd_node *cmd_node, t_env_list *env_list);
int			execute_cmd_or_builtin(t_cmd_node *cmd_node, t_env_list *env_list);
int			execute_loop(t_cmd_list *cmd_list, t_env_list *env_list);
int	        collect_heredocs(t_cmd_list *cmd_list);
void	    signals_for_execution(void);

//redirect.c
int 		redirect(t_cmd_node *cmd_node);
int			open_redirects(t_cmd_node *cmd_node);
void		check_fd(t_cmd_node *cmd_node);
int	        handle_heredoc(t_cmd_node *cmd_node);
int	        get_last_hd_fd(t_cmd_node *cmd_node);

//pipes.c
int			execute_pipes(t_cmd_list *cmd_list, t_env_list *env_list);
void		close_pipes(t_cmd_list *cmd_list, t_cmd_node *current, int *pipefd, int i);
void		setup_pipes(t_cmd_list *cmd_list, int *pipefd, int i);
void	    signals_for_child(void);

//heredoc_utils.c
t_hd_line	*create_hd_line(char *content);
t_hd_node	*create_hd_node(char *lim);
void		add_line_to_heredoc(t_hd_node *hd_node, char *line);
int			is_delimiter(char *line, char *delimiter);
int			create_heredoc_fd(t_hd_node *hd_node);
int			write_heredoc_to_pipe(t_hd_node *hd_node, int write_fd);
int			check_exit_status(pid_t child_pid, t_mini *mini);
int         create_heredoc(char *lim, t_cmd_node *cmd_node, t_file_node *file_node);

int	        process_heredocs_in_cmd_list(t_cmd_list *cmd_list);
int	        process_heredocs_in_single_cmd(t_cmd_node *cmd_node);
int	        cmd_list_has_heredocs(t_cmd_list *cmd_list);
int	        handle_cmd_list_heredocs(t_cmd_list *cmd_list);

//garbage.c
int				gc_free(void *ptr);
int				free_node(t_garbage_list *gc_list, void *ptr);
void			*gc_malloc(size_t size);
void			add_gc_node(t_garbage_node *node);
t_garbage_node	*create_gc_node(void *ptr);
void 			free_all_garbage(void);
void 			add_to_garbage(void *ptr);
t_garbage_list 	*get_garbage_list(void);
int				add_to_gc(void *ptr);

//unset.c
void			unset_env_var(t_env_list *env_list, char *var);

//export_add.c
int				handle_export_without_value(t_env_list *env_list, char *var);
int				search_for_equal_sign(char *arg);
int				handle_export_without_equal(t_env_list *env_list, char *arg);
int 			process_export_arg(t_env_list *env_list, char *arg);
int				add_export(t_env_list *env_list, t_cmd_node *cmd_node);

//shell.c
void			sig_handler(int signum, siginfo_t *info, void *context);
void			handle_signal_in_msh(void);

//utils.c

int				check_if_fd_open(int fd);
int				reset_stds(void);

#endif