/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 23:04:36 by swied             #+#    #+#             */
/*   Updated: 2025/07/24 19:28:04 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int	execute_cmd_or_builtin(t_cmd_node *cmd_node, char **envp)
{
	if (cmd_node->cmd_type == 1)
		execute_builtin(cmd_node, envp);
	else
		execute_cmd(cmd_node, envp);
	//clean_up();
	return (0);
}

int	execute_cmd_loop(t_cmd_node *cmd_node, char **envp)
{
	execute_cmd_or_builtin(cmd_node, envp);
	return (0);
}

int	execute_loop(t_cmd_list *cmd_list, char **envp)
{
	execute_pipes(cmd_list, envp);
	return (0);
}

int	execute_cmd(t_cmd_node *cmd_node, char **envp)
{
	char	*path;

	if (!cmd_node || !cmd_node->cmd)
		return (0);
	path = get_correct_path(cmd_node->cmd[0], envp);
	if (!path)
		return (printf("Cmd not found\n"), 1);
	execve(path, cmd_node->cmd, envp);
	printf("Execve faild\n");
	exit(EXIT_FAILURE);
}

void	cmd_init1(t_cmd_node *cmd_node)
{
	cmd_node->cmd = malloc(sizeof(char *) * 4);
	cmd_node->cmd[0] = "ls";
	cmd_node->cmd[1] = "-l";
	cmd_node->cmd[2] = NULL;
	cmd_node->cmd_type = 0;
	// Datei-Redirect vorbereiten
	cmd_node->file = malloc(sizeof(t_file_list));
	cmd_node->file->size = 0;
	cmd_node->file->fd_infile = -1;
	cmd_node->file->fd_outfile = -1;
	// Datei-Node anlegen
	// t_file_node *outfile_node1 = malloc(sizeof(t_file_node));
	// t_file_node *outfile_node2 = malloc(sizeof(t_file_node));
	// t_file_node *infile_node1 = malloc(sizeof(t_file_node));
	// t_file_node *infile_node2 = malloc(sizeof(t_file_node));
	// infile_node1->filename = "infile1.txt";
	// infile_node1->redir_type = REDIR_IN;
	// infile_node1->next = infile_node2;
	// infile_node2->filename = "infile2.txt";
	// infile_node2->redir_type = REDIR_IN;
	// infile_node2->next = outfile_node1;

	// outfile_node1->filename = "test.txt";
	// outfile_node1->redir_type = REDIR_APPEND;
	// outfile_node1->next = outfile_node2;
	// outfile_node2->filename = "test2.txt";
	// outfile_node2->redir_type = REDIR_APPEND;
	// outfile_node2->next = NULL;

	// cmd_node->file->head = infile_node1;
	// cmd_node->file->tail = outfile_node2;
}
void	cmd_init2(t_cmd_node *cmd_node)
{
	cmd_node->cmd = malloc(sizeof(char *) * 4);
	cmd_node->cmd[0] = "wc";
	cmd_node->cmd[1] = NULL;
	cmd_node->cmd_type = 0;
	// Datei-Redirect vorbereiten
	cmd_node->file = malloc(sizeof(t_file_list));
	cmd_node->file->size = 0;
	cmd_node->file->fd_infile = -1;
	cmd_node->file->fd_outfile = -1;
}

void	cmd_init3(t_cmd_node *cmd_node)
{
	cmd_node->cmd = malloc(sizeof(char *) * 4);
	cmd_node->cmd[0] = "cat";
	cmd_node->cmd[1] = NULL;
	cmd_node->cmd_type = 0;
	cmd_node->file = malloc(sizeof(t_file_list));
	cmd_node->file->size = 0;
	cmd_node->file->fd_infile = -1;
	cmd_node->file->fd_outfile = -1;
}


int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_cmd_list	*cmd_list = malloc(sizeof(t_cmd_list));
	t_cmd_node	*cmd_node1 = malloc(sizeof(t_cmd_node));
	t_cmd_node	*cmd_node2 = malloc(sizeof(t_cmd_node));
	t_cmd_node	*cmd_node3 = malloc(sizeof(t_cmd_node));
	t_cmd_node	*cmd_node4 = malloc(sizeof(t_cmd_node));

	cmd_init1(cmd_node1);
	cmd_init2(cmd_node2);
	cmd_init3(cmd_node3);
	cmd_init2(cmd_node4);

	cmd_list->head = cmd_node1;
	cmd_list->head->next = cmd_node2;
	cmd_node2->next = cmd_node3;
	cmd_node3->next = cmd_node4;
	cmd_list->tail = cmd_node4;
	cmd_list->size = 4;

	// Redirects ausführen
	if (redirect(cmd_list) != 0)
		return (1);
	// Befehl ausführen
	execute_loop(cmd_list, envp);
	(void)envp;

	return (0);
}
