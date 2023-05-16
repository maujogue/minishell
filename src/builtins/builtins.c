/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathisaujogue <mathisaujogue@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:15:34 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/16 15:46:03 by mathisaujog      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	check_invalid_identifier(char *str, char *cmd)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if ((str[i] >= 33 && str[i] <= 47) || str[i] == '^' || str[i] == '`'
				|| str[i] == '[' || str[i] == ']' || str[i] == ';' || str[i] == '<'
				|| str[i] == '}' || str[i] == '{' || str[i] == '|' || str[i] == '>'
				|| str[i] == '?' || str[i] == '@' || str[i] == '=' || str[i] == ':')
			{
				write_error("minishell: ", cmd, ": '");
				ft_putchar_fd(str[i], 2);
				write_error("", "", "': not a valid identifier\n");
				g_status = 1;
				return (1);
			}
		i++;
	}
	return (0);
}

int	is_builtin(t_all *all, t_pip *pip)
{
	(void)all;
	if (ft_strncmp(pip->cmd[0], "exit\0", 5) == 0
		|| ft_strncmpecho(pip->cmd[0], "echo\0", 5) == 0
		|| ft_strncmp(pip->cmd[0], "env\0", 4) == 0
		|| ft_strncmpexport(pip->cmd[0], "export\0", 7) == 0
		|| ft_strncmpunset(pip->cmd[0], "unset\0", 6) == 0
		|| ft_strncmp(pip->cmd[0], "cd\0", 3) == 0
		|| ft_strncmp(pip->cmd[0], "pwd\0", 4) == 0)
		return (0);
	return (1);
}

int	ft_builtins(t_all *all, t_pip *pip)
{
	if (ft_strncmp(pip->cmd[0], "exit\0", 5) == 0)
		ft_exit(pip->cmd);
	else if (ft_strncmpecho(pip->cmd[0], "echo\0", 5) == 0)
		ft_echo(all, pip->cmd);
	else if (ft_strncmp(pip->cmd[0], "env\0", 4) == 0)
		ft_env(all, pip);
	else if (ft_strncmpexport(pip->cmd[0], "export\0", 7) == 0)
		ft_export(all, pip->cmd);
	else if (ft_strncmpunset(pip->cmd[0], "unset\0", 6) == 0)
		ft_unset(all, pip);
	else if (ft_strncmp(pip->cmd[0], "cd\0", 3) == 0)
		ft_cd(all, pip);
	else if (ft_strncmp(pip->cmd[0], "pwd\0", 4) == 0)
		ft_pwd(pip->cmd);
	else
		return (1);
	return (0);
}
