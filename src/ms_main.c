/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:28:48 by avaganay          #+#    #+#             */
/*   Updated: 2023/04/04 15:01:42 by avaganay         ###   ########.fr       */
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
		ft_builtins(cmd, &all, envp);
		//printf("%s\n", cmd);
	}
	return 0;
}
