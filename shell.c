/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:40:09 by vramacha          #+#    #+#             */
/*   Updated: 2025/07/16 15:06:42 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	rl_redisplay();
}

//replicates Ctrl-C Ctrl-\ behaviour in bash
void	handle_signal_in_msh(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = sig_handler;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

void	restore_signal_in_child(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGTSTP);
	sigaddset(&act.sa_mask, SIGQUIT);
	act.sa_flags = 0;
	act.sa_handler = SIG_DFL;
	sigaction(SIGINT, &act, NULL);
}

int	main(void)
{
	const char	*prompt = "msh-1.0$ ";
	char		*linebuffer;
	int			len;
	
	handle_signal_in_msh();
	linebuffer = NULL;
	while (1)
	{
		if (linebuffer)
		{
			free(linebuffer);
			linebuffer = NULL;
		}
		linebuffer = readline(prompt);
		if (!linebuffer)
			exit(EXIT_SUCCESS);
		len = 0;
		while(linebuffer[len])
			len++;
		printf("len:%i\n", len);
		if (*linebuffer)
			add_history(linebuffer);
	}
}
