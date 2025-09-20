// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/07/25 17:42:42 by swied             #+#    #+#             */
// /*   Updated: 2025/09/01 00:29:23 by swied            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/execute.h"

int main(int argc, char **argv, char **envp)
{
	if (isatty(fileno(stdin)))
		interactive_shell(argc, argv, envp);
	else
		non_interactive_shell(argc, argv, envp);
	return (0);
}