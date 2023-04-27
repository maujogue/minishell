/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:28:48 by avaganay          #+#    #+#             */
/*   Updated: 2023/04/27 15:49:37 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <signal.h>

int g_signal;

int	ft_find_pipe(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

void	ft_init_all(t_all *all, char **envp)
{
	all->listenv = NULL;
	all->listenv = ft_env(envp);
	all->listexport = NULL;
	all->infile = NULL;
	all->outfile = NULL;
	all->parspipex = NULL;
	all->heredoc_delim = NULL;
	all->outfile_append = 0;
}

int	main(int argc, char** argv, char **envp)
{
	(void) argc;
	(void) argv;
	char *cmd;
	t_all	all;

	ft_init_all(&all, envp);
	while (1)
	{
		signals();
		cmd = readline(">>");
		if (!cmd)
		{
			printf("exit\n");
			exit(0);
		}
		add_history(cmd);
		ft_fillfile_heredoc(&all, cmd);
		ft_parsing(&all, cmd);
		pipex(&all);
	}
	return 0;
}
