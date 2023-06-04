/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathisaujogue <mathisaujogue@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:15:00 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/04 18:14:51 by mathisaujog      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

extern int	g_status;

void	sigint_handler(int sig)
{
	g_status = 128 + sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_handler_inside_minishell(int sig)
{
	g_status = 128 + sig;
	rl_replace_line("\n", 0);
	rl_on_new_line();
	rl_replace_line("", 0);
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

void	signals_in_process(char *cmd)
{
	if (ft_strcmp("./minishell", cmd) == 0)
	{
		signal(SIGINT, sigint_handler_inside_minishell);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{	
		signal(SIGINT, sigint_handler_in_process);
		signal(SIGQUIT, sigquit_handler_in_process);
	}
}
