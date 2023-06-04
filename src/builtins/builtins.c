/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathisaujogue <mathisaujogue@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:15:34 by avaganay          #+#    #+#             */
/*   Updated: 2023/06/04 11:24:04 by mathisaujog      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	is_builtin(t_pip *pip)
{
	if (!pip->cmd)
		return (1);
	if (ft_strncmp(pip->cmd[0], "exit\0", 5) == 0
		|| ft_strncmp(pip->cmd[0], "echo\0", 5) == 0
		|| ft_strncmp(pip->cmd[0], "env\0", 4) == 0
		|| ft_strncmp(pip->cmd[0], "export\0", 7) == 0
		|| ft_strncmp(pip->cmd[0], "unset\0", 6) == 0
		|| ft_strncmp(pip->cmd[0], "cd\0", 3) == 0
		|| ft_strncmp(pip->cmd[0], "pwd\0", 4) == 0)
		return (0);
	return (1);
}

int	ft_builtins(t_all *all, t_pip *pip)
{
	if (ft_strncmp(pip->cmd[0], "exit\0", 5) == 0)
		ft_exit(all, pip);
	else if (ft_strncmp(pip->cmd[0], "echo\0", 5) == 0)
		ft_echo(pip->cmd);
	else if (ft_strncmp(pip->cmd[0], "env\0", 4) == 0)
		ft_env(all, pip);
	else if (ft_strncmp(pip->cmd[0], "export\0", 7) == 0)
		ft_export(all, pip);
	else if (ft_strncmp(pip->cmd[0], "unset\0", 6) == 0)
		ft_unset(all, pip);
	else if (ft_strncmp(pip->cmd[0], "cd\0", 3) == 0)
		ft_cd(all, pip);
	else if (ft_strncmp(pip->cmd[0], "pwd\0", 4) == 0)
		ft_pwd(all, pip);
	else
		return (1);
	return (0);
}
