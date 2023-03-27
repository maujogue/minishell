/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:15:34 by avaganay          #+#    #+#             */
/*   Updated: 2023/03/27 14:59:23 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void    ft_builtins(char *cmd, t_all *all, char **envp)
{
	char	**tabcmd;

	tabcmd = ft_split(cmd, ' ');
    if (ft_strncmp(cmd, "exit", 4) == 0)
        ft_exit(0);
    if (ft_strncmp(cmd, "clear", 5) == 0)
		clear_history();
	if (ft_strncmp(cmd, "echo", 4) == 0)
		ft_echo(all, cmd);
	if (ft_strncmp(cmd, "env", 3) == 0)
		ft_print_listenv(all, cmd);
	if (ft_strncmp(cmd, "export", 6) == 0)
		ft_export(envp, all, cmd);
	if (ft_strncmp(cmd, "unset", 5) == 0)
		ft_unset(all->listenv, cmd);
	if (ft_strncmp(cmd, "cd", 2) == 0)
		ft_cd(tabcmd[1]);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		ft_pwd();
	//ft_freetab(tabcmd);
}