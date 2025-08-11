/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vishnudevramachandra <vishnudevramachan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:40:09 by vramacha          #+#    #+#             */
/*   Updated: 2025/08/11 17:17:54 by vishnudevra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "./libft/libft.h"
#include "lexer.h"

// void	sig_handler(int signum, siginfo_t *info, void *context)
// {
// 	(void)context;
// 	(void)info;
// 	if (signum == SIGINT)
// 	{
// 		write(1, "\n", 1);
// 		//rl_replace_line("", 0);
// 		rl_on_new_line();
// 	}
// 	rl_redisplay();
// }

// //replicates Ctrl-C Ctrl-\ behaviour in bash
// void	handle_signal_in_msh(void)
// {
// 	struct sigaction	act;

// 	sigemptyset(&act.sa_mask);
// 	act.sa_flags = SA_SIGINFO;
// 	act.sa_sigaction = sig_handler;
// 	sigaction(SIGINT, &act, NULL);
// 	sigaction(SIGQUIT, &act, NULL);
// }

// void	restore_signal_in_child(void)
// {
// 	struct sigaction	act;

// 	sigemptyset(&act.sa_mask);
// 	sigaddset(&act.sa_mask, SIGTSTP);
// 	sigaddset(&act.sa_mask, SIGQUIT);
// 	act.sa_flags = 0;
// 	act.sa_handler = SIG_DFL;
// 	sigaction(SIGINT, &act, NULL);
// }

// char	*openingquote_in_str(const char *str)
// {
// 	if (ft_strchr(str, '"') && ft_strchr(str, '\''))
// 	{
// 		if (ft_strchr(str, '"') < ft_strchr(str, '\''))
// 			return (ft_strchr(str, '"'));
// 		else
// 			return (ft_strchr(str, '\''));
// 	}
// 	if (ft_strchr(str, '"'))
// 		return (ft_strchr(str, '"'));
// 	else
// 		return (ft_strchr(str, '\''));
// }

// char	*unclosedquote_in_str(const char *str)
// {
// 	char	*opening_quote;

// 	opening_quote = openingquote_in_str(str);
// 	if (!opening_quote)
// 		return (NULL);
// 	str = opening_quote + 1;
// 	while (*str)
// 	{
// 		if (*str == *opening_quote)
// 			return (unclosedquote_in_str(str + 1));
// 		str++;
// 	}
// 	return (opening_quote);
// }

// char	*strjoin_with_nl_and_free(char *s1, char *s2)
// {
// 	char	*joined_str;
// 	size_t	len;

// 	len = ft_strlen(s1);
// 	joined_str = malloc((len + ft_strlen(s2) + 2) * sizeof(char));
// 	if (!joined_str)
// 		return (NULL);
// 	ft_strlcpy(joined_str, s1, len + 1);
// 	joined_str[len] = '\n';
// 	ft_strlcpy(joined_str + len + 1, s2, ft_strlen(s2) + 1);
// 	free(s1);
// 	free(s2);
// 	return (joined_str);
// }

// char	*readline_withclosingquotes(const char *prompt)
// {
// 	char	*linebuffer;
// 	char	*unclosed_quote;
// 	char	*tmp;

// 	linebuffer = readline(prompt);
// 	if (!linebuffer)
// 		exit(EXIT_SUCCESS);
// 	unclosed_quote = unclosedquote_in_str(linebuffer);
// 	while (unclosed_quote)
// 	{
// 		tmp = readline(">");
// 		if (!tmp)
// 		{
// 			printf("msh: unexpected EOF while looking for matching `%c'\n",
// 				*unclosed_quote);
// 			free(linebuffer);
// 			return (NULL);
// 		}
// 		linebuffer = strjoin_with_nl_and_free(linebuffer, tmp);
// 		unclosed_quote = unclosedquote_in_str(linebuffer);
// 	}
// 	return (linebuffer);
// }

// int	main(void)
// {
// 	char	*linebuffer;
// 	t_lexer	lex;

// 	handle_signal_in_msh();
// 	linebuffer = NULL;
// 	while (1)
// 	{
// 		if (linebuffer)
// 		{
// 			free(linebuffer);
// 			linebuffer = NULL;
// 		}
// 		linebuffer = readline_withclosingquotes("msh-1.0$ ");
// 		if (linebuffer)
// 		{
// 			add_history(linebuffer);
// 			lexer_build(linebuffer, &lex);
// 		}
// 	}
// }
