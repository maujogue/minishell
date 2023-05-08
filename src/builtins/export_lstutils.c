/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_lstutils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:39:58 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/08 10:48:07 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_listenv	*ft_lstexport_new(char *var)
{
	t_listenv	*new;

	new = malloc(sizeof(t_listenv));
	if (!new)
		return (NULL);
	new->content = var;
	new->next = NULL;
	return (new);
}

t_listenv	*ft_lstexportlast(t_listenv *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstexportadd_back(t_listenv **lst, t_listenv *new)
{
	t_listenv	*back;

	if (!(*lst) || lst == NULL)
	{
		*lst = new;
		return ;
	}
	back = ft_lstexportlast(*lst);
	back->next = new;
}

int	ft_lstexportsize(t_listenv *lst)
{
	t_listenv	*curr;
	int			i;

	curr = lst;
	i = 0;
	while (curr != NULL)
	{
		curr = curr->next;
		i++;
	}
	return (i);
}
