/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:28:48 by avaganay          #+#    #+#             */
/*   Updated: 2023/03/22 13:31:06 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <signal.h>

void handler()
{
	write(1, "nope\n", 5);
}


int	main(int argc, char** argv, char **envp) {
	(void)argc;
	(void) argv;
	char *cmd;
	//t_listenv *listenv;
	t_all	all;

	all.listenv = ft_env(envp);
	while (1)
	{
		cmd = readline(">>");
		if (ft_strlen(cmd) > 0)
			add_history(cmd);
		ft_builtins(cmd, &all, envp);
		//printf("%s\n", cmd);
	}
	return 0;
}
