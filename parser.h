/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vishnudevramachandra <vishnudevramachan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:38:52 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/08/11 19:39:57 by vishnudevra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

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