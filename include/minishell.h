/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:42:38 by swied             #+#    #+#             */
/*   Updated: 2025/08/05 18:33:27 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdbool.h>

typedef struct s_file_node t_file_node;
typedef struct s_cmd_node t_cmd_node;
typedef	struct s_hd_list t_hd_list;
typedef struct s_hd_node t_hd_node;
typedef struct s_hd_line t_hd_line;
typedef struct s_env_list t_env_list;
typedef struct s_env_node t_env_node;

typedef struct s_env_node
{
	char				*variable;
	char				*value;
	bool				is_export;
	t_env_node			*next;
}	t_env_node;

typedef struct s_env_list
{
	t_env_node	*head;
	t_env_node	*tail;
	size_t		size;
}	t_env_list;

typedef struct s_hd_line
{
	char				*line;
	t_hd_line			*next;
}	t_hd_line;

typedef struct s_hd_node
{
	t_file_node			*file_node;
	t_hd_line			*lines;
	char				*lim;
	t_hd_node			*next;
}	t_hd_node;

typedef struct s_hd_list
{
	t_hd_node			*head;	
	t_hd_node			*tail;
	size_t				size;
}	t_hd_list;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_file_node
{
	char				*filename;
	t_redir_type		redir_type;
	t_file_node			*next;
}	t_file_node;

typedef struct s_file_list
{
	t_file_node		*head;
	t_file_node		*tail;	
	ssize_t			size;
	int				fd_infile;
	int				fd_outfile;
}	t_file_list;

typedef struct s_cmd_node
{
	int				cmd_type;
	char			**cmd;
	t_file_list		*file;
	t_cmd_node		*next;
	t_hd_list		*hd_list;
}	t_cmd_node;

typedef struct s_cmd_list
{
	t_cmd_node		*head;
	t_cmd_node		*tail;
	ssize_t			size;
	int				prev_fd;
	
}	t_cmd_list;

typedef struct s_mini
{
	t_cmd_list		*cmd_list;
	t_env_list		*env_list;
}	t_mini;

#endif