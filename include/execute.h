/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 23:04:38 by swied             #+#    #+#             */
/*   Updated: 2025/09/21 16:31:12 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
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
# include <stddef.h>
# include <readline/readline.h>
# include "libft/libft.h"
# include "garbage_collector.h"
# include "minishell.h"
# include "lexer.h"

//execute_utils.c
int				ft_strcmp(const char *s1, const char *s2);

//builtins
int				builtin_pwd(void);
int				builtin_echo(char **args);
int				builtin_cd(char **args, t_env_list *env_list);
int				builtin_env(t_env_list *env_list);
int				builtin_exit(char **args);
int				builtin_unset(t_env_list *env_list, t_cmd_node *cmd_node);

//env.c
int				update_env_var(char ***env, char *key, char *value);
int				add_env_var(t_env_list *env_list, char *var, char *val);
int				print_env(t_env_list *env_list);
int				set_env_var(t_env_list *env_list, char *var, char *val);

//env_utils.c
t_env_node		*create_env_node(char *var, char *val);
char			*get_env_value(t_env_list *env_list, char *var);

//echo.c
int				is_n_flag(char *arg);

//env_list.c
t_env_list		*fill_env_list(char **envp);
void			shell_lvl_up(t_env_list *env_list);

//list_to_dblarray.c
char			**list_to_dblarray(t_env_list *env_list);
int				create_env(char *var, char *value, char **array, int i);
char			**free_env_array(char **array, int i);

//get_path.c
char			*get_total_path(char **envp);
char			*get_correct_path_second(char **path_array, char *suffix);
char			*get_correct_path(char *cmd, char **envp);

//builtin.c
int				execute_builtin(t_cmd_node *cmd_node, t_env_list *env_list);

//execute.c
int				execute_cmd(t_cmd_node *cmd_node, t_env_list *env_list);
int				execute_cmd_or_builtin(t_cmd_node *cmd_node,
					t_env_list *env_list);
int				execute_loop(t_cmd_list *cmd_list, t_env_list *env_list);
int				collect_heredocs(t_cmd_list *cmd_list);
void			signals_for_execution(void);

//redirect.c
int				redirect(t_cmd_node *cmd_node);
int				open_redirects(t_cmd_node *cmd_node);
void			check_fd(t_cmd_node *cmd_node);
int				get_last_hd_fd(t_cmd_node *cmd_node);

//pipes.c
int				execute_pipes(t_cmd_list *cmd_list, t_env_list *env_list);
void			close_pipes(t_cmd_list *cmd_list, t_cmd_node *current,
					int *pipefd, int i);
void			setup_pipes(t_cmd_list *cmd_list, int *pipefd, int i);
void			signals_for_child(void);

//heredoc_signals.c
void			heredoc_signal_handler(int sig);
void			setup_heredoc_signals(void);
void			restore_default_signals(void);
void			handle_signal_interruption(void);
void			setup_parent_signal_handler(void);
int				get_heredoc_interrupted(void);
void			reset_heredoc_interrupted(void);

//heredoc_memory.c
t_hd_line		*create_hd_line(char *content);
void			add_line_to_heredoc(t_hd_node *hd_node, char *line);
t_hd_node		*init_heredoc_node(char *delimiter);
void			add_heredoc_to_list(t_cmd_node *cmd_node, t_hd_node *hd_node);
void			init_hd_list(t_cmd_node *cmd_node);

//heredoc_parsing.c
int				is_delimiter_match(char *line, char *delimiter);
int				is_delimiter(char *line, char *delimiter);
int				cmd_list_has_heredocs(t_cmd_list *cmd_list);
int				process_heredocs_in_single_cmd(t_cmd_node *cmd_node,
					t_env_list *env_list);

//heredoc_output.c
int				collect_heredoc_input(char *delimiter, int write_fd,
					t_env_list *env_list);
int				read_heredoc_content(t_hd_node *hd_node, int read_fd);
int				write_heredoc_to_pipe(t_hd_node *hd_node, int write_fd);
int				create_heredoc_fd(t_hd_node *hd_node);

//heredoc_core.c
int				handle_cmd_list_heredocs(t_cmd_list *cmd_list,
					t_env_list *env_list);
int				process_heredocs_in_cmd_list(t_cmd_list *cmd_list,
					t_env_list *env_list);
int				execute_heredoc_collection(char *delimiter, t_hd_node *hd_node,
					t_env_list *env_list);
int				create_heredoc(char *delimiter, t_cmd_node *cmd_node,
					t_file_node *file_node, t_env_list *env_list);

//heredoc_expansion.c

char			*expand_heredoc(char *line, t_env_list *env_list);
char			*check_for_dollar(char *str, t_env_list *env_list);
char			*find_env_value(char *var_name, t_env_list *env_list);

//garbage.c
int				gc_free(void *ptr);
int				free_node(t_garbage_list *gc_list, void *ptr);
void			*gc_malloc(size_t size);
void			add_gc_node(t_garbage_node *node);
t_garbage_node	*create_gc_node(void *ptr);
void			free_all_garbage(void);
void			add_to_garbage(void *ptr);
t_garbage_list	*get_garbage_list(void);
int				add_to_gc(void *ptr);

//unset.c
void			unset_env_var(t_env_list *env_list, char *var);

//export.c
int				builtin_export(t_env_list *env_list, t_cmd_node *cmd_node);
void			print_export(t_env_list *env_list, char **env_array, int i);
void			fill_export_array(t_env_list *env_list, char **env_array);
char			**create_export_list(t_env_list *env_list);
void			free_export_array(char **array, int i);

//export_add.c
int				handle_export_without_value(t_env_list *env_list, char *var);
int				search_for_equal_sign(char *arg);
int				handle_export_without_equal(t_env_list *env_list, char *arg);
int				process_export_arg(t_env_list *env_list, char *arg);
int				add_export(t_env_list *env_list, t_cmd_node *cmd_node);

//export_utils.c
int				count_exported_vars(t_env_list *env_list);
void			bubblesort_array(char **env_array);
t_env_node		*find_env_var(t_env_list *env_list, char *var);

//shell.c
void			sig_handler(int signum, siginfo_t *info, void *context);
void			handle_signal_in_msh(void);
void			interactive_shell(int argc, char **argv, char **envp);
void			non_interactive_shell(int argc, char **argv, char **envp);

//utils.c
int				check_if_fd_open(int fd);
int				reset_stds(void);
int				get_exit_status(int status);

#endif