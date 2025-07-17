/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:42:38 by swied             #+#    #+#             */
/*   Updated: 2025/07/17 15:27:30 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>

typedef struct s_file_node t_file_node;
typedef struct s_cmd_node t_cmd_node;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_file_node
{
	char			*filename;
	t_redir_type	redir_type;
	t_file_node		*next;
}	t_file_node;

typedef struct s_file_list
{
	t_file_node	*head;
	t_file_node	*tail;	
	ssize_t		size;
}	t_file_list;

typedef struct s_cmd_node
{
	int			cmd_type;
	char		**cmd;
	t_file_list	*file;
	t_cmd_node	*next;
}	t_cmd_node;

typedef struct s_cmd_list
{
	t_cmd_node	*head;
	t_cmd_node	*tail;
	ssize_t		size;
}	t_cmd_list;

typedef struct s_mini
{
	t_cmd_list	*cmd_list;
}	t_mini;

#endif