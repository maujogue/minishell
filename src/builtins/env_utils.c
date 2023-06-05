/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:08 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/05 14:03:10 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	**ft_fusion_split(char	**split)
{
	int		i;

	i = 2;
	if (split[2])
	{
		while (split[i])
		{
			split[1] = ft_strjoin_gnl(split[1], "=");
			if (!split[1])
				return (NULL);
			split[1] = ft_strjoin_gnl(split[1], split[i]);
			if (!split[1])
				return (NULL);
			i++;
		}
	}
	return (split);
}

t_listenv	*ft_lstenv_new(char *str)
{
	t_listenv	*new;
	char		**split;

	new = malloc(sizeof(t_listenv));
	if (!new)
		return (NULL);
	split = ft_split(str, '=');
	if (!split)
		return (free(new), NULL);
	new->key = ft_strdup(split[0]);
	if (!new->key)
		return (NULL);
	split = ft_fusion_split(split);
	if (!split)
		return (NULL);
	new->content = ft_strdup(split[1]);
	if (!new->content)
		return (free_array(split), NULL);
	new->next = NULL;
	free_array(split);
	return (new);
}

t_listenv	*create_node_env_i(t_listenv *listenv, char *key, char *content)
{
	char		*str;
	t_listenv	*node;

	str = ft_strjoin(key, content);
	if (!str)
		return (NULL);
	node = ft_lstenv_new(str);
	if (!node)
		return (NULL);
	free(str);
	ft_lstexport_add_back(&listenv, node);
	return (listenv);
}

void	create_env_i(t_all *all, char **envp)
{
	char		*str;

	if (!envp[0])
	{
		str = getcwd(NULL, 0);
		if (!str)
			free_exit(all, NULL, 1, "");
		all->listenv = create_node_env_i(all->listenv, "PWD=", str);
		if (!all->listenv)
			free_exit(all, NULL, 1, "");
		free(str);
		all->listenv = create_node_env_i(all->listenv, "SHLVL=", "1");
		if (!all->listenv)
			free_exit(all, NULL, 1, "");
		all->listenv = create_node_env_i(all->listenv, "_=", "/usr/bin/env");
		if (!all->listenv)
			free_exit(all, NULL, 1, "");
	}
}

void	create_env(t_all *all, char **envp)
{
	int			i;
	t_listenv	*node;

	i = 0;
	create_env_i(all, envp);
	while (envp[i])
	{
		node = ft_lstenv_new(envp[i]);
		if (!node)
			free_exit(all, NULL, 1, "");
		ft_lstexport_add_back(&(all->listenv), node);
		i++;
	}
}
