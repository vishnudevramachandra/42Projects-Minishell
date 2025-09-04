/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:40:09 by vramacha          #+#    #+#             */
/*   Updated: 2025/09/04 16:43:13 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "./libft/libft.h"
#include "lexer.h"
#include "parser.h"

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	char			nl;
	struct termios	term;

	(void)context;
	(void)info;
	if (signum != SIGINT)
		rl_redisplay();
	else
	{
		rl_replace_line("\n", 0);
		tcgetattr(0, &term);
		term.c_lflag &= ~ECHO;
		tcsetattr(0, TCSANOW, &term);
		nl = '\n';
		ioctl(1, TIOCSTI, &nl);
		term.c_lflag |= ECHO;
		tcsetattr(0, TCSANOW, &term);
		//TODO: set $? to have a value of 1
	}
}

//replicates Ctrl-C Ctrl-\ behaviour in bash
void	handle_signal_in_msh(void)
{
	struct termios		term;
	struct sigaction	act;

	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSAFLUSH, &term);
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = sig_handler;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

void	create_env_list(t_env_list *env_list)
{
	t_env_node	*node;

	node = malloc(sizeof(t_env_node));
	node->variable = "HOME";
	node->value = "/Users/root";
	node->is_export = 0;
	env_list->head = node;
	node->next = malloc(sizeof(t_env_node));
	node = node->next;
	node->variable = "var";
	node->value = "\ta:bs>mm c\t";
	node->is_export = 0;
	node->next = malloc(sizeof(t_env_node));
	node = node->next;
	node->variable = "IFS";
	node->value = " \t\n:";
	node->is_export = 0;
	node->next = NULL;
}

int	main(void)
{
	char		*linebuffer;
	t_lexer		lex;
	t_env_list	env_list;
	t_cmd_list	cmds;

	handle_signal_in_msh();
	create_env_list(&env_list); //for testing
	linebuffer = NULL;
	while (1)
	{
		if (linebuffer)
		{
			add_history(linebuffer);
			free(linebuffer);
			linebuffer = NULL;
		}
		linebuffer = readline("msh-1.0$ ");
		// linebuffer = "<text.txt cat ~/yo' bl<|'mama >\"ab$HOME*\"$var et"; //for testing
		if (linebuffer)
		{
			if (lexer_build(&linebuffer, &lex, &env_list))
				parse(&cmds, &lex);
			clear_lexer(&lex);
		}
		else
			exit(EXIT_SUCCESS); //gc_malloc_clear
		print_parser_output(&cmds); //for testing
		// break; //for testing
	}
}
