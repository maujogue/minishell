/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:28:48 by avaganay          #+#    #+#             */
/*   Updated: 2023/04/20 13:06:13 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <signal.h>

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
	all->listenv = ft_env(envp);
	all->listexport = NULL;
	all->infile = NULL;
	all->outfile = NULL;
	all->parspipex = NULL;
}

int	main(int argc, char** argv, char **envp)
{
	(void)argc;
	(void) argv;
	char *cmd;
	//t_listenv *listenv;
	t_all	all;

	// all->listenv = NULL;
	ft_init_all(&all, envp);
	while (1)
	{
		cmd = readline(">>");
		add_history(cmd);
		ft_fillfile(&all, cmd);
		ft_parsing(&all, cmd);
		pipex(&all);
	}
	return 0;
}
