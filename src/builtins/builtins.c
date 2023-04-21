/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:15:34 by avaganay          #+#    #+#             */
/*   Updated: 2023/04/21 10:56:50 by maujogue         ###   ########.fr       */
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


int	ft_builtins(t_all *all, t_pip *pip)
{
	pip->cmd[0] = ft_clean_cmd(pip->cmd[0]);
    if (ft_strncmp(pip->cmd[0], "exit\0", 5) == 0)
        return (-1);
	else if (ft_strncmpecho(pip->cmd[0], "echo\0", 5) == 0)
		ft_echo(all, pip->cmd[0]);
	else if (ft_strncmp(pip->cmd[0], "env", 3) == 0)
		ft_print_listenv(all, pip->cmd[0]);
	else if (ft_strncmpexport(pip->cmd[0], "export\0", 7) == 0)
		ft_export(pip->envp, all, pip->cmd[0]);
	else if (ft_strncmpunset(pip->cmd[0], "unset\0", 6) == 0)
		ft_unset(all->listenv, all, pip->cmd[0]);
	else if (ft_strncmp(pip->cmd[0], "cd", 2) == 0)
		ft_cd(pip->cmd[1]);
	else if (ft_strncmp(pip->cmd[0], "pwd\0", 4) == 0)
		ft_pwd(pip->cmd);
	else
		return (1);
	free_exit(all, pip, 1, "");
	return (0);
}