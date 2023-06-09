/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:02 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/09 10:07:31 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	cd_get_full_path(t_all *all, t_pip *pip, char *pwd)
{
	char	*arg;

	arg = ft_strjoin(pwd, "/");
	if (!arg)
		free_exit(all, pip, 1, "bash: Malloc error\n");
	arg = ft_strjoin_gnl(arg, pip->cmd[1]);
	if (!arg)
		free_exit(all, pip, 1, "bash: Malloc error\n");
	if (chdir(arg) == 0)
	{
		if (replace_env_arg(all->listenv, "OLDPWD", pwd) == 1)
			free_exit(all, pip, 1, NULL);
		replace_env_pwd(all, pip, all->listenv, "PWD");
		free(arg);
	}
	else
		return (free(arg), g_status = 1,
			(void)printf("bash: cd: %s: No such file or directory\n",
				pip->cmd[1]));
}

void	cd_args(t_all *all, t_pip *pip, char *pwd)
{
	char	*arg;

	arg = ft_strdup(pip->cmd[1]);
	if (!arg)
		free_exit(all, pip, 1, "bash: Malloc error\n");
	if (chdir(arg) == 0 && ft_strncmp(arg, "/", 1) == 0)
	{
		if (replace_env_arg(all->listenv, "OLDPWD", pwd) == 1)
			free_exit(all, pip, 1, NULL);
		replace_env_pwd(all, pip, all->listenv, "PWD");
		return (free(arg));
	}
	else
		cd_get_full_path(all, pip, pwd);
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
