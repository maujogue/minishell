/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:28:48 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/05 15:12:18 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <signal.h>

void	ft_init_all(t_all *all, char **envp)
{
	all->listenv = NULL;
	all->listenv = ft_env(envp);
	all->listexport = NULL;
	all->infile2 = NULL;
	all->outfile = NULL;
	all->parspipex = NULL;
	all->heredoc_delim = NULL;
	all->outfile_append = 0;
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	t_all	all;

	(void) argc;
	(void) argv;
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
		ft_parsing(&all, cmd);
		pipex(&all);
	}
	return (0);
}
