/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:15:00 by swied             #+#    #+#             */
/*   Updated: 2025/09/25 15:34:12 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

/* Main function to handle all heredocs in cmd_list before execution */
int	handle_cmd_list_heredocs(t_cmd_list *cmd_list, t_env_list *env_list)
{
	if (!cmd_list_has_heredocs(cmd_list))
		return (0);
	return (process_heredocs_in_cmd_list(cmd_list, env_list));
}

/* Processes all heredocs in the entire cmd_list */
int	process_heredocs_in_cmd_list(t_cmd_list *cmd_list, t_env_list *env_list)
{
	t_cmd_node	*current;

	if (!cmd_list || !cmd_list->head)
		return (0);
	current = cmd_list->head;
	while (current)
	{
		if (process_heredocs_in_single_cmd(current, env_list) == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}

/* Execute heredoc collection in child process */
int	execute_heredoc_collection(char *delimiter, t_hd_node *hd_node,
	t_env_list *env_list)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (close(pipe_fd[0]), close(pipe_fd[1]), -1);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		collect_heredoc_input(delimiter, pipe_fd[1], env_list);
	}
	close(pipe_fd[1]);
	if (read_heredoc_content(hd_node, pipe_fd[0]) == -1)
		return (close(pipe_fd[0]), waitpid(pid, &status, 0),
			handle_signal_in_msh(), -1);
	close(pipe_fd[0]);
	waitpid(pid, &status, 0);
	handle_signal_in_msh();
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (-1);
	return (0);
}

/* Create and process a single heredoc */
int	create_heredoc(char *delimiter, t_cmd_node *cmd_node,
	t_file_node *file_node,	t_env_list *env_list)
{
	t_hd_node	*hd_node;

	hd_node = init_heredoc_node(delimiter);
	if (!hd_node)
		return (-1);
	hd_node->file_node = file_node;
	add_heredoc_to_list(cmd_node, hd_node);
	if (execute_heredoc_collection(delimiter, hd_node, env_list) == -1)
		return (-1);
	return (0);
}
