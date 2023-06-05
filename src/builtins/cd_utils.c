/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:11:09 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/05 14:14:10 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	replace_env_pwd(t_all *all, t_pip *pip, t_listenv	*listenv, char *arg)
{
	char	*pwd;

	while (listenv)
	{
		if (ft_strncmp(listenv->key, arg, ft_strlen(arg)) == 0)
		{
			free(listenv->content);
			pwd = getcwd(NULL, 0);
			if (!pwd)
				free_exit(all, pip, 1, "bash: Malloc error\n");
			if (!pwd)
				listenv->content = NULL;
			else
			{
				listenv->content = ft_strdup(pwd);
				if (!listenv->content)
					free_exit(all, pip, 1, "bash: Malloc error\n");
			}
			return ;
		}
		listenv = listenv->next;
	}
}

int	cd_empty(t_all *all, t_pip *pip, char *pwd)
{
	char	*arg;

	arg = pip->cmd[1];
	if (!arg)
	{
		arg = get_env_content(all, pip, all->listenv, "HOME");
		if (!arg)
			return (g_status = 1,
				write_error("bash: cd: HOME not set\n", "", ""), 2);
		if (access(arg, F_OK) != 0)
			return (free(arg), g_status = 1, write_error("bash: cd: ",
					arg, ": No such file or directory\n"), 2);
		if (replace_env_arg(all->listenv, "OLDPWD", pwd) == 1)
			free_exit(all, pip, 1, NULL);
		if (replace_env_arg(all->listenv, "PWD", arg) == 1)
			free_exit(all, pip, 1, NULL);
		chdir(arg);
		free(arg);
		return (0);
	}
	return (1);
}

int	cd_previous(t_all *all, t_pip *pip, char *pwd, char *old_pwd)
{
	char	*arg;
	char	*temp;

	arg = pip->cmd[1];
	if (arg && ft_strncmp(arg, "-\0", 2) == 0)
	{
		chdir(old_pwd);
		temp = pwd;
		if (replace_env_arg(all->listenv, "PWD", old_pwd) == 1)
			free_exit(all, pip, 1, NULL);
		if (replace_env_arg(all->listenv, "OLDPWD", temp) == 1)
			free_exit(all, pip, 1, NULL);
		return (0);
	}
	return (1);
}
