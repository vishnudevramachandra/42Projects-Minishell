/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vishnudevramachandra <vishnudevramachan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:19:52 by swied             #+#    #+#             */
/*   Updated: 2025/09/24 15:20:28 by vishnudevra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

/* Execute a single command in a child process */
static void	execute_child_process(t_cmd_node *current, t_env_list *env_list)
{
	if (redirect(current) != 0)
	{
		free_all_garbage();
		exit(EXIT_FAILURE);
	}
	if (execute_cmd_or_builtin(current, env_list) != 0)
	{
		free_all_garbage();
		exit(EXIT_FAILURE);
	}
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
	tcsetpgrp(STDOUT_FILENO, getpid());
	return (last_status);
}

static pid_t	tcsetpgrp_in_child(int i, pid_t pgid)
{
	if (i < 1)
	{
		pgid = getpid();
		if (tcsetpgrp(STDOUT_FILENO, pgid) != 0)
			perror("tcsetpgrp() error");
	}
	return (pgid);
}

/* Process single command in pipe */
static pid_t	process_pipe_cmd(t_cmd_list *cmd_list, t_env_list *env_list,
					t_cmd_node *current, int i)
{
	pid_t			pid;
	int				pipefd[2];
	static pid_t	pgid;

	if (i < (cmd_list->size - 1))
		pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		pgid = tcsetpgrp_in_child(i, pgid);
		setpgid(pid, pgid);
		setup_pipes(cmd_list, pipefd, i);
		execute_child_process(current, env_list);
	}
	else
	{
		if (i < 1)
			pgid = pid;
		setpgid(pid, pgid);
		close_pipes(cmd_list, current, pipefd, i);
	}
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
	return (get_exit_status(wait_for_children(last_pid)));
}
