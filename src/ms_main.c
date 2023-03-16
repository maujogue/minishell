/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:28:48 by avaganay          #+#    #+#             */
/*   Updated: 2023/03/16 12:02:09 by avaganay         ###   ########.fr       */
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
	t_listenv *listenv;

	listenv = ft_env(envp);
	while (1)
	{
		cmd = readline(">>");
		if (ft_strlen(cmd) > 0)
			add_history(cmd);
		printf("%s\n", cmd);
		if (ft_strncmp(cmd, "clear", 5) == 0)
			clear_history();
		if (ft_strncmp(cmd, "env", 3) == 0)
			ft_print_listenv(listenv, cmd);
		// if (ft_strncmp(cmd, "export", 6) == 0)
		// 	ft_export(envp);
		if (ft_strncmp(cmd, "unset", 5) == 0)
			ft_unset(listenv, cmd);
	}
	return 0;
}
