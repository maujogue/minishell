/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:15:00 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/19 10:21:59 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

extern int	g_status;


void	sigint_handler(int sig)
{
	g_status = 128 + sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	sigint_handler_inside_minishell(int sig)
{
	g_status = 128 + sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
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

void	signals_inside_minishell(void)
{
	signal(SIGINT, sigint_handler_inside_minishell);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_in_process(void)
{
	signal(SIGINT, sigint_handler_in_process);
	signal(SIGQUIT, sigquit_handler_in_process);
}
