/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:08 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/23 16:53:34 by maujogue         ###   ########.fr       */
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
			split[1] = ft_strjoin_gnl(split[1], split[i]);
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
	split = ft_fusion_split(split);
	new->content = ft_strdup(split[1]);
	// free(new->content);
	new->next = NULL;
	free_array(split);
	return (new);
}

void	ft_lstenvadd_back(t_listenv **lst, t_listenv *new)
{
	t_listenv	*curr;

	curr = *lst;
	if (*lst == 0)
		*lst = new;
	else
	{
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new;
	}
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
	ft_lstenvadd_back(&listenv, node);
	return (listenv);
}

void	create_env(t_all *all, char **envp)
{
	int			i;
	t_listenv	*node;
	char		*str;

	i = 0;
	if (!envp[0])
	{
		str = getcwd(NULL, 0);
		all->listenv = create_node_env_i(all->listenv, "PWD=", str);
		free(str);
		all->listenv = create_node_env_i(all->listenv, "SHLVL=", "1");
		all->listenv = create_node_env_i(all->listenv, "_=", "/usr/bin/env");
	}
	while (envp[i])
	{
		node = ft_lstenv_new(envp[i]);
		if (!node)
			return ;
		ft_lstenvadd_back(&(all->listenv), node);
		i++;
	}
}

