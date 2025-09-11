/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:19:52 by swied             #+#    #+#             */
/*   Updated: 2025/09/11 13:19:14 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

/* creates pipefd and pid | pipes pipefd | forks pid | In child process setup the pipes, redirects and execute the cmd | In main process close the pipes and at end wait for every child process */
int	execute_pipes(t_cmd_list *cmd_list, t_env_list *env_list)
{
	pid_t		pid;
	int			i;
	int			status;
	int			pipefd[2];
	t_cmd_node	*current;

	current = cmd_list->head;
	cmd_list->prev_fd = -1;
	i = 0;
	while ((i < cmd_list->size) && (current))
	{
		if (i < (cmd_list->size - 1))
			pipe(pipefd);
		pid = fork();
		if (pid == 0)
		{
			signals_for_child();
			setup_pipes(cmd_list, pipefd, i);
			if (redirect(current) != 0)
				exit(EXIT_FAILURE);
			if (execute_cmd_or_builtin(current, env_list) != 0)
				exit(EXIT_FAILURE);
		}
		else
			close_pipes(cmd_list, current, pipefd, i);
		i++;
		current = current->next;
	}
	while (wait(&status) > 0);
	handle_signal_in_msh();
	return (get_exit_stauts(status));
}

/* If there is a prev_fd before -> close it and dup2 into standard */ 
void	setup_pipes(t_cmd_list *cmd_list, int *pipefd, int i)
{
	if (cmd_list->prev_fd != -1)
	{
		dup2(cmd_list->prev_fd, STDIN_FILENO);
		close(cmd_list->prev_fd);
	}
	if (i < cmd_list->size - 1)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
}

/* If prev_fd is there close it | Also close after last cmd */
void	close_pipes(t_cmd_list *cmd_list, t_cmd_node *current,
	int *pipefd, int i)
{
	if (cmd_list->prev_fd != -1)
		close(cmd_list->prev_fd);
	if (i < cmd_list->size - 1)
	{
		close(pipefd[1]);
		cmd_list->prev_fd = pipefd[0];
	}
	if (current && current->file_list)
	{
		if (current->file_list->fd_infile != -1)
			close(current->file_list->fd_infile);
		if (current->file_list->fd_outfile != -1)
			close(current->file_list->fd_outfile);
	}
}

void	signals_for_child(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = SIG_DFL;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_DFL;
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
