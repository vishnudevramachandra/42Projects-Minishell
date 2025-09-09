/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:38:52 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/09/09 14:42:08 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "execute.h"
# include "lexer.h"

int			parse(t_cmd_list **cmds, t_lexer *lex);
void		free_and_exit(t_lexer *lex);
t_cmd_list	*init_cmds(t_cmd_list *cmds, t_lexer *lex);
t_cmd_node	*alloc_and_init_cmd_node(t_lexer *lex);
t_file_list	*alloc_and_init_file_list(t_lexer *lex);
void		print_parser_output(t_cmd_list *cmds);
void		add_file_to_filelist(
				t_file_list *files, char *name, t_redir_type typ, t_lexer *lex);
char		**update_cmd(char **cmd, char *word, t_lexer *lex);

#endif