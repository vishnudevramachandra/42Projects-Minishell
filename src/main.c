/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:42:42 by swied             #+#    #+#             */
/*   Updated: 2025/08/24 08:42:08 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

void	cmd_init1(t_cmd_node *cmd_node)
{
	cmd_node->cmd = gc_malloc(sizeof(char *) * 4);
	cmd_node->cmd[0] = "export";
	cmd_node->cmd[1] = "te=123";
	cmd_node->cmd[2] = "st";
	cmd_node->cmd[3] = NULL;
	cmd_node->cmd_type = 1;

	cmd_node->file = gc_malloc(sizeof(t_file_list));
	cmd_node->file->size = 0;
	cmd_node->file->fd_infile = -1;
	cmd_node->file->fd_outfile = -1;
	cmd_node->file->head = gc_malloc(sizeof(t_file_node));
	cmd_node->file->head->redir_type = -1;
	cmd_node->file->head->filename = NULL;
	cmd_node->file->head->next = NULL;
	cmd_node->file->head = NULL;

}

void	cmd_init2(t_cmd_node *cmd_node)
{
	cmd_node->cmd = gc_malloc(sizeof(char *) * 3);
	cmd_node->cmd[0] = "export";
	cmd_node->cmd[1] = NULL;
	cmd_node->cmd_type = 1;
	cmd_node->hd_list = NULL;

	cmd_node->file = gc_malloc(sizeof(t_file_list));
	cmd_node->file->size = 0;
	cmd_node->file->head = NULL;
	cmd_node->file->fd_infile = -1;
	cmd_node->file->fd_outfile = -1;
	// t_file_node *infile1 = malloc(sizeof(t_file_node));
	// t_file_node *infile2 = malloc(sizeof(t_file_node));
	
	// cmd_node->file->head = infile1; 
	// infile1->next = infile2;
	// infile1->filename = "infile1";
	// infile2->filename = "infile2";
	// infile1->redir_type = REDIR_IN;
	// infile2->redir_type = REDIR_IN;
}

void	cmd_init3(t_cmd_node *cmd_node)
{
	cmd_node->cmd = gc_malloc(sizeof(char *) * 3);
	cmd_node->cmd[0] = "export";
	cmd_node->cmd[1] = NULL;
	cmd_node->cmd_type = 1;
	
	cmd_node->file = gc_malloc(sizeof(t_file_list));
	cmd_node->file->size = 0;
	cmd_node->file->fd_infile = -1;
	cmd_node->file->fd_outfile = -1;
	// t_file_node *infile1 = malloc(sizeof(t_file_node));
	// t_file_node *infile2 = malloc(sizeof(t_file_node));

	// cmd_node->file->head = infile1;
	// infile1->next = infile2;
	// cmd_node->file->tail = infile2;
	// infile1->filename = "infile1";
	// infile2->filename = "infile2";
	// cmd_node->file->tail = infile2;
	// infile1->redir_type = REDIR_IN;
	// infile2->redir_type = REDIR_IN;

}

void	cmd_init4(t_cmd_node *cmd_node)
{
	cmd_node->cmd = gc_malloc(sizeof(char *) * 2);
	cmd_node->cmd[0] = "../test";
	cmd_node->cmd[1] = NULL;
	cmd_node->cmd_type = 0;

	cmd_node->file = gc_malloc(sizeof(t_file_list));
	cmd_node->file->size = 0;
	cmd_node->file->fd_infile = -1;
	cmd_node->file->fd_outfile = -1;

	cmd_node->file->head = NULL;
}

void	cmd_init5(t_cmd_node *cmd_node)
{
	cmd_node->cmd = gc_malloc(sizeof(char *) * 2);
	cmd_node->cmd[0] = "pwd";
	cmd_node->cmd[1] = NULL;
	cmd_node->cmd_type = 1;

	cmd_node->file = gc_malloc(sizeof(t_file_list));
	cmd_node->file->size = 0;
	cmd_node->file->fd_infile = -1;
	cmd_node->file->fd_outfile = -1;

	cmd_node->file->head = NULL;
}

/* Hardcode of filling the cmd_list and running execution */
int	main(int argc, char **argv, char **envp)
{
	int	status = 0;
	(void)argc;
	(void)argv;

	t_cmd_list	*cmd_list = gc_malloc(sizeof(t_cmd_list));
	t_cmd_node	*cmd_node1 = gc_malloc(sizeof(t_cmd_node));
	t_cmd_node	*cmd_node2 = gc_malloc(sizeof(t_cmd_node));
	// t_cmd_node	*cmd_node3 = malloc(sizeof(t_cmd_node));
	// t_cmd_node	*cmd_node4 = malloc(sizeof(t_cmd_node));

	cmd_init1(cmd_node1);
	cmd_init2(cmd_node2);
	// cmd_init2(cmd_node3);
	// cmd_init5(cmd_node4);
	// cmd_init2(cmd_node4);

	cmd_list->head = cmd_node1;
	// cmd_list->tail = cmd_node2;
	// cmd_node1->next = cmd_node2;
	cmd_node1->next = NULL;
	// cmd_node3->next = cmd_node4;
	// cmd_list->tail = cmd_node2;
	cmd_list->size = 1;

	t_env_list *env_list;
	env_list = fill_env_list(envp);
	status = execute_loop(cmd_list, env_list);
	builtin_export(env_list, cmd_node2);
	free_all_garbage();
	return (status);
}
