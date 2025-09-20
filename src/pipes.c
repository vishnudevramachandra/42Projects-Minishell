/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:19:52 by swied             #+#    #+#             */
/*   Updated: 2025/09/20 16:34:39 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

/* Execute a single command in a child process */
static void	execute_child_process(t_cmd_node *current, t_env_list *env_list)
{
	signals_for_child();
	if (redirect(current) != 0)
		exit(EXIT_FAILURE);
	if (execute_cmd_or_builtin(current, env_list) != 0)
		exit(EXIT_FAILURE);
}

/* Wait for all child processes and get last command exit status */
static int	wait_for_children(pid_t last_pid)
{
	pid_t	pid;
	int		status;
	int		last_status;

	last_status = 0;
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			last_status = status;
			last_pid = 0;
		}
		pid = wait(&status);
	}
	if (last_pid > 0)
		waitpid(last_pid, &last_status, 0);
	return (last_status);
}

/* Process single command in pipe */
static pid_t	process_pipe_cmd(t_cmd_list *cmd_list, t_env_list *env_list,
	t_cmd_node *current, int i)
{
	pid_t	pid;
	int		pipefd[2];

	if (i < (cmd_list->size - 1))
		pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		setup_pipes(cmd_list, pipefd, i);
		execute_child_process(current, env_list);
	}
	else
		close_pipes(cmd_list, current, pipefd, i);
	return (pid);
}

/* Execute pipes with reduced arguments */
int	execute_pipes(t_cmd_list *cmd_list, t_env_list *env_list)
{
	int			i;
	pid_t		last_pid;
	t_cmd_node	*current;

	current = cmd_list->head;
	cmd_list->prev_fd = -1;
	i = 0;
	last_pid = 0;
	while ((i < cmd_list->size) && (current))
	{
		last_pid = process_pipe_cmd(cmd_list, env_list, current, i);
		i++;
		current = current->next;
	}
	handle_signal_in_msh();
	return (get_exit_status(wait_for_children(last_pid)));
}
