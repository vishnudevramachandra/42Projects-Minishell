/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:39:18 by vramacha          #+#    #+#             */
/*   Updated: 2025/09/23 10:46:46 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "./libft/libft.h"

size_t	lb_heredoc(char *buf, size_t len, t_mini *mini, t_lexer *lex)
{
	t_token	*tok;
	size_t	len_sps;
	size_t	i;
	int		unclosed_quote;

	tok = get_last_token(lex);
	tok->type = HEREDOC;
	len_sps = ft_strspn(buf + len, " \t");
	buf = buf + len + len_sps;
	i = 0;
	unclosed_quote = 0;
	while (!ft_strchr(" \t|<>", *(buf + i)))
	{
		if (ft_strchr("'\"", *(buf + i)))
			unclosed_quote++;
		i++;
	}
	if (unclosed_quote % 2)
	{
		ft_putendl_fd("msh: syntax error due to unclosed quote", 2);
		return (set_status(mini, 258), clx(lex), len_sps + ft_strlen(buf));
	}
	incr_lex(lex);
	add_word_to_tok(buf, i, lex);
	return (len_sps + i);
}
