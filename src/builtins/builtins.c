/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathisaujogue <mathisaujogue@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:15:34 by avaganay          #+#    #+#             */
/*   Updated: 2023/04/28 12:30:58 by mathisaujog      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*ft_clean_cmd(char *cmd)
{
	char	*res;
	int		i;
	int		len;
	int		j;
	
	i = 0;
	j = 0;
	len = 0;
	while (cmd[i])
	{
		if (cmd[i] != '"' && cmd[i] != '\'')
			len++;
		i++;	
	}
	res = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != '"' && cmd[i] != '\'')
		{
			res[j] = cmd[i];
			j++;
		}
		i++;	
	}
	res[j] = '\0';
	return (res);
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
		ft_print_listenv(all, pip->cmd[0], !pip->path);
	else if (ft_strncmpexport(pip->cmd[0], "export\0", 7) == 0)
		ft_export(pip->envp, all, pip->cmd);
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