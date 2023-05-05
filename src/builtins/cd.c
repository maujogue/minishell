/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:02 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/05 10:03:46 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	replace_env_pwd(t_listenv	*listenv, char *arg)
{
	while (listenv)
	{
		if (ft_strncmp(listenv->key, arg, ft_strlen(arg)) == 0)
		{
			free(listenv->content);
			listenv->content = ft_strdup(getcwd(NULL, 0));
			return ;
		}
		listenv = listenv->next;
	}
}

int	cd_empty_or_previous(t_all *all, t_pip *pip, char *pwd, char *old_pwd)
{
	char	*arg;
	char	*temp;

	arg = pip->cmd[1];
	if (!arg)
	{
		arg = get_env_content(all->listenv, "HOME");
		if (!arg)
			return (write_error("bash: cd: HOME not set\n", "", ""), 2);
		replace_env_arg(all->listenv, "OLDPWD", pwd);
		replace_env_arg(all->listenv, "PWD", arg);
		chdir(arg);
		free(arg);
		return (0);
	}
	else if (ft_strncmp(arg, "-\0", 2) == 0)
	{
		chdir(old_pwd);
		temp = pwd;
		replace_env_arg(all->listenv, "PWD", old_pwd);
		replace_env_arg(all->listenv, "OLDPWD", temp);
		return (0);
	}
	return (1);
}

void	cd_args(t_all *all, t_pip *pip, char *pwd)
{
	char	*arg;
	char	*temp;

	arg = pip->cmd[1];
	temp = arg;
	if (chdir(arg) == 0 && ft_strncmp(arg, "/", 1) == 0)
	{
		replace_env_arg(all->listenv, "OLDPWD", pwd);
		replace_env_pwd(all->listenv, "PWD");
		return ;
	}
	else
	{
		arg = ft_strjoin(pwd, "/");
		arg = ft_strjoin_gnl(arg, pip->cmd[1]);
		if (chdir(arg) == 0)
		{
			replace_env_arg(all->listenv, "OLDPWD", pwd);
			replace_env_pwd(all->listenv, "PWD");
			free(arg);
		}
		else
			printf("bash: cd: %s: No such file or directory\n", temp);
	}
}

void	ft_cd(t_all *all, t_pip *pip)
{
	char	*pwd;
	char	*old_pwd;

	if (ft_strlen_array(pip->cmd) > 2)
	{
		ft_printf("bash: cd: too many arguments\n");
		return ;
	}
	pwd = ft_strdup(get_env_content(all->listenv, "PWD"));
	old_pwd = ft_strdup(get_env_content(all->listenv, "OLDPWD"));
	if (cd_empty_or_previous(all, pip, pwd, old_pwd) == 1)
		cd_args(all, pip, pwd);
	free(pwd);
	free(old_pwd);
}
