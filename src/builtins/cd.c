/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathisaujogue <mathisaujogue@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:02 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/04 16:51:26 by mathisaujog      ###   ########.fr       */
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
			if (!(pwd = getcwd(NULL, 0)))
				free_exit(all, pip, 1, "bash: Malloc error\n");
			free(listenv->content);
			listenv->content = NULL;
			free(pwd);
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

void	cd_args(t_all *all, t_pip *pip, char *pwd)
{
	char	*arg;

	if (!(arg = ft_strdup(pip->cmd[1])))
		free_exit(all, pip, 1, "bash: Malloc error\n");
	if (chdir(arg) == 0 && ft_strncmp(arg, "/", 1) == 0)
	{
		if (replace_env_arg(all->listenv, "OLDPWD", pwd) == 1)
			free_exit(all, pip, 1, NULL);
		replace_env_pwd(all, pip, all->listenv, "PWD");
		return (free(arg));
	}
	else
	{
		free(arg);
		if (!(arg = ft_strjoin(pwd, "/")))
			free_exit(all, pip, 1, "bash: Malloc error\n");
		if (!(arg = ft_strjoin_gnl(arg, pip->cmd[1])))
			free_exit(all, pip, 1, "bash: Malloc error\n");
		if (chdir(arg) == 0)
		{
			if (replace_env_arg(all->listenv, "OLDPWD", pwd) == 1)
				free_exit(all, pip, 1, NULL);
			replace_env_pwd(all, pip, all->listenv, "PWD");
			free(arg);
		}
		else
			return (free(arg), g_status = 127,
				(void)printf("bash: cd: %s: No such file or directory\n",
					pip->cmd[1]));
	}
}

void	ft_cd(t_all *all, t_pip *pip)
{
	char	*pwd;
	char	*old_pwd;

	if (ft_strlen_array(pip->cmd) > 2)
	{
		ft_printf("bash: cd: too many arguments\n");
		g_status = 1;
		return ;
	}
	pwd = get_env_content(all, pip, all->listenv, "PWD");
	old_pwd = get_env_content(all, pip, all->listenv, "OLDPWD");
	if (cd_empty(all, pip, pwd) == 1
		&& cd_previous(all, pip, pwd, old_pwd) == 1)
		cd_args(all, pip, pwd);
	free(pwd);
	free(old_pwd);
}
