/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathisaujogue <mathisaujogue@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:15:00 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/16 15:54:08 by mathisaujog      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

extern int	g_status;


void	sigint_handler(int sig)
{
	g_status = 128 + sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	// rl_replace_line("", 0);
	// rl_on_new_line();
}

void	sigint_handler_in_process(int sig)
{
	g_status = 128 + sig;
	printf("\n");
}

void	sigquit_handler_in_process(int sig)
{
	g_status = 128 + sig;
	printf("Quit (core dumped)\n");
}

void	signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_in_process(void)
{
	signal(SIGINT, sigint_handler_in_process);
	signal(SIGQUIT, sigquit_handler_in_process);
}
