/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:08 by maujogue          #+#    #+#             */
/*   Updated: 2023/03/16 12:03:18 by avaganay         ###   ########.fr       */
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
			split[1] = ft_strjoin(split[1], "=");
			split[1] = ft_strjoin(split[1], split[i]);
			i++;
		}
	}
	return (split);
}

t_listenv	*ft_lstenv_new(char *str)
{
	t_listenv	*new;
	char	**split;

	new = malloc(sizeof(t_listenv));
	if (!new)
		return (NULL);
	// printf("%s\n", str);
	split = ft_split(str, '=');
	if (!split)
		return (NULL);
	//ft_strlcpy(new->key, split[0], ft_strlen(split[0]) - 1);
	new->key = split[0];
	// printf("%s\n", new->key);
	// printf("%s\n", split[1]);
	split = ft_fusion_split(split);
	new->content = split[1];
	new->next = NULL;
	// ft_freetab(split);
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
	int	i;
	t_listenv	*node;

	i = 0;
	while(envp[i])
	{
		node = ft_lstenv_new(envp[i]);
		if (!node)
			return (NULL);
		ft_lstenvadd_back(&listenv, node);
		i++;
	}
	return (listenv);
}

t_listenv *ft_env(char **envp)
{
	t_listenv	*listenv;

	listenv = NULL;
	listenv = ft_fill_env(listenv, envp);
	if (!listenv)
		return (NULL);
	return (listenv);
}