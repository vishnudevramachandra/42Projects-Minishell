/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vishnudevramachandra <vishnudevramachan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:38:52 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/09/04 17:43:18 by vishnudevra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "execute.h"

int		parse(t_cmd_list *cmds, t_lexer *lex);
void	print_parser_output(t_cmd_list *cmds);

#endif