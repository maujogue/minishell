/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:07:18 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/05 14:46:47 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include <dirent.h>

char	*get_path_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			return (ft_strdup(envp[i] + 5));
		i++;
	}
	return (NULL);
}

char	*get_path_cmd(t_all *all, t_pip *pip, char *cmd, char *path)
{
	char	**tab;
	char	*temp_path;
	int		i;

	if ((cmd[0] == '.' || cmd[0] == '/'))
		return (ft_strdup(cmd));
	if (!pip->path || !cmd)
		return (NULL);
	i = 1;
	tab = ft_split(path, ':');
	if (!tab)
		free_exit(all, pip, 1, "bash: Malloc error\n");
	while (tab[i])
	{
		temp_path = ft_strjoin(tab[i], "/");
		temp_path = ft_strjoin_gnl(temp_path, cmd);
		if (access(temp_path, X_OK) == 0)
			return (free_array(tab), temp_path);
		free(temp_path);
		i++;
	}
	return (free_array(tab), NULL);
}

int	check_executables(char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if ((cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/')) && dir)
		return (free(dir), g_status = 126,
			write_error("bash: ", cmd, ": Is a directory\n"), 1);
	else if ((cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
		&& !dir && access(cmd, X_OK) == -1 && access(cmd, F_OK) == 0)
		return (free(dir), g_status = 126,
			write_error("bash: ", cmd, ": Permission denied\n"), 1);
	else if ((cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
		&& !dir && access(cmd, X_OK) == -1)
		return (free(dir), g_status = 127,
			write_error("bash: ", cmd, ": No such file or directory\n"), 1);
	free(dir);
	return (0);
}

int	check_point_slash(char *cmd)
{
	int	i;

	i = 0;
	if (ft_strcmp(cmd, ":\0") == 0
		|| ft_strcmp(cmd, "\n\0") == 0 || ft_strcmp(cmd, "!\0") == 0)
		return (1);
	if (ft_strcmp(".", cmd) == 0)
		return (g_status = 2,
			write_error("bash: ", cmd, ": filename argument required\n"), 1);
	while (cmd[i] && cmd[i] == '.')
		i++;
	if (cmd[i] == '\0')
		return (write_error("bash: ", cmd, ": command not found\n"), 1);
	return (0);
}

int	check_cmd(t_all *all, t_pip *pip)
{
	char	*cmd;
	int		exit;

	exit = 0;
	cmd = pip->cmd[0];
	if (!cmd || cmd[0] == '\0')
		return (1);
	if (check_point_slash(cmd) == 1 || check_executables(cmd) == 1)
		return (1);
	else if (is_builtin(pip) == 0)
		return (0);
	else
	{
		pip->path_cmd = get_path_cmd(all, pip, cmd, pip->path);
		if (!pip->path_cmd && !pip->path)
			return (g_status = 127,
				write_error("bash: ", cmd, ": No such file or directory\n"), 1);
		else if (!pip->path_cmd)
			return (g_status = 127,
				write_error("bash: ", cmd, ": command not found\n"), 1);
	}
	return (exit);
}
