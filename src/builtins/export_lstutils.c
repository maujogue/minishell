/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_lstutils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:39:58 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/15 19:00:02 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_listenv	*ft_lstexport_new(char *key, char *content)
{
	t_listenv	*new;

	new = malloc(sizeof(t_listenv));
	if (!new)
		return (NULL);
	new->key = key;
	new->content = content;
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

int	ft_lstexport_size(t_listenv *lst)
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

t_listenv	*ft_lst_dup(t_listenv *lst)
{
	t_listenv	*new;
	t_listenv	*temp;

	if (!lst)
		return (NULL);
	new = ft_lstexport_new(lst->key, lst->content);
	temp = new;
	while (lst)
	{
		new->next = ft_lstexport_new(lst->key, lst->content);
		new = new->next;
		lst = lst->next;
	}
	lst = temp;
	return (lst);
}

t_listenv	*ft_lstcat(t_listenv *lst1, t_listenv *lst2)
{
	t_listenv	*temp_original;
	t_listenv	*temp_final;
	t_listenv	*final;

	temp_original = lst1;
	final = ft_lst_dup(lst1);
	temp_final = final;
	final = ft_lstexport_last(lst1);
	while (lst2)
	{
		ft_lstexport_add_back(&final, ft_lst_dup(lst2));
		lst2 = lst2->next;
		final = final->next;
	}
	lst1 = temp_original;
	final = temp_final;
	ft_print_listexport(final);
	return (final);
}