/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:08 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/05 14:21:31 by maujogue         ###   ########.fr       */
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

	new = malloc(sizeof(t_listenv) + 1);
	if (!new)
		return (NULL);
	split = ft_split(str, '=');
	if (!split)
		return (NULL);
	new->key = split[0];
	split = ft_fusion_split(split);
	new->content = split[1];
	new->next = NULL;
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

t_listenv	*ft_fill_env(t_listenv *listenv, char **envp)
{
	int			i;
	t_listenv	*node;

	i = 0;
	while (envp[i])
	{
		node = ft_lstenv_new(envp[i]);
		if (!node)
			return (NULL);
		ft_lstenvadd_back(&listenv, node);
		i++;
	}
	return (listenv);
}

t_listenv	*ft_env(char **envp)
{
	t_listenv	*listenv;

	listenv = NULL;
	listenv = ft_fill_env(listenv, envp);
	if (!listenv)
		return (NULL);
	return (listenv);
}
