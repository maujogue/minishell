/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:28:48 by avaganay          #+#    #+#             */
/*   Updated: 2023/04/13 10:04:29 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <signal.h>

void handler()
{
	write(1, "nope\n", 5);
}


int	main(int argc, char** argv, char **envp)
{
	(void)argc;
	(void) argv;
	char *cmd;
	//t_listenv *listenv;
	t_all	all;

	// all->listenv = NULL;
	all.listenv = ft_env(envp);
	all.listexport = NULL;
	while (1)
	{
		cmd = readline(">>");
		add_history(cmd);
		if (ft_find_pipe(cmd))
		{
			ft_parsing(&all, cmd);
			pipex(&all);
		}
		else
			ft_builtins(cmd, &all, envp);
		//printf("%s\n", cmd);
	}
	return 0;
}
