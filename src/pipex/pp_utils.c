/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:07:18 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/15 10:58:04 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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
	char	*temp_path2;
	int		i;

	if (!pip->path || !cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	i = 1;
	tab = ft_split(path, ':');
	if (!tab)
		free_exit(all, pip, 1, "Error\nMalloc failed1");
	while (tab[i])
	{
		temp_path = ft_strjoin(tab[i], "/");
		temp_path2 = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (access(temp_path2, X_OK) == 0)
			return (free_array(tab), temp_path2);
		free(temp_path2);
		i++;
	}
	temp_path2 = ft_strjoin(tab[i], cmd);
	if (access(temp_path, F_OK) == 0)
		return (free_array(tab), temp_path2);
	return (free_array(tab), NULL);
}

int	check_point_slash(char *cmd)
{
	int	i;

	i = 0;
	if (ft_strcmp(".", cmd) == 0)
		return (write_error("bash: ", cmd, ": filename argument required\n"), 1);
	while (cmd[i] && cmd[i] == '.')
		i++;
	if (cmd[i] == '\0')
		return (write_error("bash: ", cmd, ": command not found\n"), 1);
	i = 0;
	while (cmd[i] && (cmd[i] == '/' || cmd[i] == '.'))
		i++;
	if (cmd[i] == '\0')
		return (write_error("bash: ", cmd, ": Is a directory\n"), 1);
	return (0);
}

int	check_cmd(t_all *all, t_pip *pip)
{
	char	*cmd;
	int		exit;

	exit = 0;
	cmd = pip->cmd[0];
	if (!cmd || cmd[0] == '\0')
		exit = 1;
	else if (is_builtin(all, pip) == 0)
		exit = 0;
	else if (check_point_slash(cmd) == 1)
		exit = 1;
	else
	{
		pip->path_cmd = get_path_cmd(all, pip, cmd, pip->path);
		if (!pip->path_cmd)
		{
			exit = 1;
			write_error("bash: ", cmd, ": command not found\n");
		}
	}
	if (exit == 1)
		g_status = 127;
	return (exit);
}
