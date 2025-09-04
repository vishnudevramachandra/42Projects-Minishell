/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vishnudevramachandra <vishnudevramachan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 13:46:38 by vramacha          #+#    #+#             */
/*   Updated: 2025/09/04 17:45:12 by vishnudevra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/parser.h"

char	*get_redir_string(t_redir_type typ)
{
	if (typ < REDIR_OUT)
		return ("REDIR_IN");
	if (typ < REDIR_APPEND)
		return ("REDIR_OUT");
	if (typ < REDIR_HEREDOC)
		return ("REDIR_APPEND");
	return ("REDIR_HEREDOC");
}

void	print_cmd(char **cmd)
{
	int	i;

	i = 0;
	printf("cmd:");
	while (cmd && cmd[i])
	{
		printf(" %s", cmd[i]);
		i++;
	}
	printf("\n");
}

void	print_files(t_file_list *f)
{
	t_file_node	*f_node;
	int			i;

	if (f)
	{
		printf("         --FILE_LIST--;\n\
          head: %p, tail: %p, size: %lu, fd_infile: %i, fd_outfile: %i\n",
			f->head, f->tail, f->size, f->fd_infile, f->fd_outfile);
		f_node = f->head;
		i = 0;
		while (f_node)
		{
			printf("          \tfile(%i): %s, %s\n",
				i, get_redir_string(f_node->redir_type), f_node->filename);
			i++;
			f_node = f_node->next;
		}
	}
}

void	print_parser_output(t_cmd_list *cmds)
{
	t_cmd_node	*c_node;
	int			i;

	printf("--CMD_LIST--;\n head: %p, tail: %p, size: %lu, prev_fd: %i\n\n",
		cmds->head, cmds->tail, cmds->size, cmds->prev_fd);
	c_node = cmds->head;
	i = 0;
	while (c_node)
	{
		printf("cmd_node(%i) %p---------------------------------------------\n",
			i, c_node);
		print_cmd(c_node->cmd);
		printf("cmd_type: %i, file: %p, next: %p, hd_list: %p\n",
			c_node->cmd_type, c_node->file_list, c_node->next, c_node->hd_list);
		print_files(c_node->file_list);
		printf("cmd_node(%i) -----------------------------------------------\n\
			\n", i);
		i++;
		c_node = c_node->next;
	}
}
