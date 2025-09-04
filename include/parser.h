/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:38:52 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/09/04 17:03:11 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int		parse(t_cmd_list *cmds, t_lexer *lex);
void	print_parser_output(t_cmd_list *cmds);

#endif