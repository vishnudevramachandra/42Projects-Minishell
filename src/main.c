/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:42:42 by swied             #+#    #+#             */
/*   Updated: 2025/07/25 19:20:50 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	cmd_init1(t_cmd_node *cmd_node)
{
	cmd_node->cmd = malloc(sizeof(char *) * 4);
	cmd_node->cmd[0] = "grep";
	cmd_node->cmd[1] = "txt";
	cmd_node->cmd[2] = NULL;
	cmd_node->cmd_type = 0;
	// Datei-Redirect vorbereiten
	cmd_node->file = malloc(sizeof(t_file_list));
	cmd_node->file->size = 0;
	cmd_node->file->fd_infile = -1;
	cmd_node->file->fd_outfile = -1;
	// Datei-Node anlegen
	t_file_node *infile_node1 = malloc(sizeof(t_file_node));
	t_file_node *infile_node2 = malloc(sizeof(t_file_node));
	infile_node1->filename = "infile1.txt";
	infile_node1->redir_type = REDIR_IN;
	infile_node1->next = infile_node2;
	infile_node2->filename = "infile2.txt";
	infile_node2->redir_type = REDIR_IN;
	infile_node2->next = NULL;

	cmd_node->file->head = infile_node1;
	cmd_node->file->tail = infile_node1;
}

void	cmd_init2(t_cmd_node *cmd_node)
{
	cmd_node->cmd = malloc(sizeof(char *) * 4);
	cmd_node->cmd[0] = "grep";
	cmd_node->cmd[1] = "txt";
	cmd_node->cmd[2] = NULL;
	cmd_node->cmd_type = 0;
	// Datei-Redirect vorbereiten
	cmd_node->file = malloc(sizeof(t_file_list));
	cmd_node->file->size = 0;
	cmd_node->file->fd_infile = -1;
}

void	cmd_init3(t_cmd_node *cmd_node)
{
	cmd_node->cmd = malloc(sizeof(char *) * 4);
	cmd_node->cmd[0] = "wc";
	cmd_node->cmd[1] = NULL;
	cmd_node->cmd_type = 0;
	cmd_node->file = malloc(sizeof(t_file_list));
	cmd_node->file->size = 0;
	cmd_node->file->fd_infile = -1;
	cmd_node->file->fd_outfile = -1;

	t_file_node *outfile_node1 = malloc(sizeof(t_file_node));
	outfile_node1->filename = "test.txt";
	outfile_node1->redir_type = REDIR_OUT;
	outfile_node1->next = NULL;
	cmd_node->file->fd_outfile = -1;

	cmd_node->file->head = outfile_node1;
	cmd_node->file->tail = outfile_node1;
}
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_cmd_list	*cmd_list = malloc(sizeof(t_cmd_list));
	t_cmd_node	*cmd_node1 = malloc(sizeof(t_cmd_node));
	t_cmd_node	*cmd_node2 = malloc(sizeof(t_cmd_node));
	// t_cmd_node	*cmd_node3 = malloc(sizeof(t_cmd_node));
	// t_cmd_node	*cmd_node4 = malloc(sizeof(t_cmd_node));

	cmd_init1(cmd_node1);
	cmd_init3(cmd_node2);
	// cmd_init3(cmd_node3);
	// cmd_init2(cmd_node4);

	cmd_list->head = cmd_node1;
	cmd_list->head->next = cmd_node2;
	// cmd_node2->next = cmd_node3;
	// cmd_node3->next = cmd_node4;
	cmd_list->tail = cmd_node2;
	cmd_list->size = 2;

	if (redirect(cmd_list) != 0)
		return (1);
	execute_loop(cmd_list, envp);
	return (0);
}
