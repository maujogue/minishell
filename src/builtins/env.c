/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:08 by maujogue          #+#    #+#             */
/*   Updated: 2023/03/06 13:02:42 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_listenv	*ft_lstenv_new(char *content)
{
	t_listenv	*new;

	new = malloc(sizeof(t_listenv));
	if (!new)
		return (NULL);
	new->content = content;
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
	int	i;
	t_listenv	*node;

	i = 0;
	while(envp[i])
	{
		node = ft_lstenv_new(envp[i]);
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
	return (listenv);
}