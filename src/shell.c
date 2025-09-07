/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vishnudevramachandra <vishnudevramachan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:40:09 by vramacha          #+#    #+#             */
/*   Updated: 2025/09/07 11:20:33 by vishnudevra      ###   ########.fr       */
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

void	init_shell(t_mini *mini, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	handle_signal_in_msh();
	mini->status = 0;
	mini->env_list = fill_env_list(envp);
}

char	*add_to_history_and_free(char *linebuffer)
{
	add_history(linebuffer);
	free(linebuffer);
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char		*linebuffer;
	t_lexer		lex;
	t_mini		mini;

	init_shell(&mini, argc, argv, envp);
	linebuffer = NULL;
	while (1)
	{
		if (linebuffer)
			linebuffer = add_to_history_and_free(linebuffer);
		linebuffer = readline("msh-1.0$ ");
		if (linebuffer)
		{
			if (lexer_build(&linebuffer, &lex, &mini)
				&& parse(&mini.cmd_list, &lex))
				mini.status = execute_loop(mini.cmd_list, mini.env_list);
			clx(&lex);
		}
		else
			builtin_exit();
	}
}
