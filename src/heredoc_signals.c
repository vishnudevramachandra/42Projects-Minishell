/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:00:00 by swied             #+#    #+#             */
/*   Updated: 2025/09/21 16:39:17 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

static volatile sig_atomic_t	g_heredoc_interrupted = 0;

/* Signal handler for heredoc input */
void	heredoc_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_heredoc_interrupted = 1;
		write(STDERR_FILENO, "\n", 1);
		exit(130);
	}
}

/* Setup signal handling for heredoc */
void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = heredoc_signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

/* Restore default signal handling */
void	restore_default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/* Get heredoc interrupt status */
int	get_heredoc_interrupted(void)
{
	return (g_heredoc_interrupted);
}

/* Reset heredoc interrupt status */
void	reset_heredoc_interrupted(void)
{
	g_heredoc_interrupted = 0;
}
