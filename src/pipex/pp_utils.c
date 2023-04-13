/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:07:18 by maujogue          #+#    #+#             */
/*   Updated: 2023/04/13 16:57:54 by maujogue         ###   ########.fr       */
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

	if (!cmd || access(cmd, F_OK) == 0 || !pip->path)
		return (cmd);
	i = 1;
	tab = ft_split(path, ':');
	if (!tab)
		free_exit(all, pip, 1, "Error\nMalloc failed1");
	while (tab[i + 1])
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

int	check_cmd(t_all *all, t_pip *pip)
{
	char	*cmd;

	cmd = pip->cmd1[0];
	if (!cmd)
		return (1);
	else if (ft_strnstr(cmd, "./", 2) || (ft_strnstr(cmd, "/", 1)
			&& ft_strlen(cmd) == 1))
		return (1);
	else
	{
		pip->path_cmd1 = get_path_cmd(all, pip, cmd, pip->path);
		if (!pip->path_cmd1)
			return (1);
	}
	return (0);
}
