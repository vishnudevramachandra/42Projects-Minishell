/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:40:09 by vramacha          #+#    #+#             */
/*   Updated: 2025/09/25 10:39:13 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../include/minishell.h"
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/execute.h"
#define _GNU_SOURCE

void	init_shell(t_mini *mini, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	handle_signal_in_msh();
	mini->status = 0;
	mini->env_list = fill_env_list(envp);
	shell_lvl_up(mini->env_list);
}

char	*add_to_history_and_free(char *linebuffer)
{
	add_history(linebuffer);
	free(linebuffer);
	return (NULL);
}

static char	*handle_rdline_input(char *linebuffer)
{
	if (linebuffer)
		linebuffer = add_to_history_and_free(linebuffer);
	linebuffer = readline("msh-1.0$ ");
	return (linebuffer);
}

void	interactive_shell(int argc, char **argv, char **envp)
{
	char		*linebuffer;
	t_lexer		lex;
	t_mini		mini;

	init_shell(&mini, argc, argv, envp);
	linebuffer = NULL;
	while (1)
	{
		reset_stds();
		linebuffer = handle_rdline_input(linebuffer);
		if (linebuffer)
		{
			if (lexer_build(&linebuffer, &lex, &mini)
				&& parse(&mini.cmd_list, &lex))
			{
				clx(&lex);
				mini.status = execute_loop(mini.cmd_list, mini.env_list);
			}
			else
				clx(&lex);
		}
		else
			builtin_exit(NULL);
	}
}

void	non_interactive_shell(int argc, char **argv, char **envp)
{
	char		*linebuffer;
	char		*trimmed;
	t_lexer		lex;
	t_mini		mini;

	init_shell(&mini, argc, argv, envp);
	linebuffer = get_next_line(fileno(stdin));
	if (!linebuffer)
		exit(mini.status);
	trimmed = ft_strtrim(linebuffer, "\n");
	free(linebuffer);
	if (!trimmed || ft_strlen(trimmed) == 0)
		exit(mini.status);
	if (lexer_build(&trimmed, &lex, &mini) && parse(&mini.cmd_list, &lex))
	{
		clx(&lex);
		mini.status = execute_loop(mini.cmd_list, mini.env_list);
	}
	else
	{
		clx(&lex);
		mini.status = 2;
	}
	reset_stds();
	exit(mini.status);
}
