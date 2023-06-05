/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_lstutils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:39:58 by avaganay          #+#    #+#             */
/*   Updated: 2023/06/05 14:01:47 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_listenv	*ft_lstexport_new(char *key, char *content)
{
	t_listenv	*new;

	new = malloc(sizeof(t_listenv));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->content = ft_strdup(content);
	new->next = NULL;
	return (new);
}

t_listenv	*ft_lstexport_last(t_listenv *lst)
{
	t_listenv	*curr;

	curr = lst;
	if (!lst)
		return (lst);
	while (curr->next != NULL)
		curr = curr->next;
	return (curr);
}

void	ft_lstexport_add_back(t_listenv **lst, t_listenv *new)
{
	t_listenv	*curr;

	curr = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new;
	}
}

t_listenv	*ft_lst_dup(t_listenv *lst)
{
	t_listenv	*new;
	t_listenv	*temp_lst;
	t_listenv	*temp_new;

	if (!lst)
		return (NULL);
	new = ft_lstexport_new(lst->key, lst->content);
	if (!new)
		return (NULL);
	temp_lst = lst;
	temp_new = new;
	lst = lst->next;
	while (lst)
	{
		new->next = ft_lstexport_new(lst->key, lst->content);
		if (!new->next)
			return (NULL);
		new = new->next;
		lst = lst->next;
	}
	lst = temp_lst;
	new = temp_new;
	return (new);
}

t_listenv	*ft_lstcat(t_listenv *lst1, t_listenv *lst2)
{
	t_listenv	*temp_original;
	t_listenv	*temp_final;
	t_listenv	*final;
	t_listenv	*dup;

	final = ft_lst_dup(lst1);
	if (!final)
		return (NULL);
	temp_original = lst1;
	temp_final = final;
	final = ft_lstexport_last(final);
	dup = ft_lst_dup(lst2);
	ft_lstexport_add_back(&final, dup);
	lst1 = temp_original;
	final = temp_final;
	return (final);
}
