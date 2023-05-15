/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:11 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/15 19:00:53 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	swap_nodes(t_listenv *a, t_listenv *b)
{
	char	*temp;

	temp = a->content;
	a->content = b->content;
	b->content = temp;
}

void	sort_linked_list(t_listenv *head)
{
	int			swapped;
	t_listenv	*ptr1;
	t_listenv	*lptr;

	lptr = NULL;
	if (head == NULL)
		return ;
	while (swapped)
	{
		swapped = 0;
		ptr1 = head;
		while (ptr1->next != lptr)
		{
			if (strcmp(ptr1->content, ptr1->next->content) > 0)
			{
				swap_nodes(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

int	get_index_of_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	if (!str[i + 1])
		return (-1);
	return (i);
}

t_listenv	*get_export_node(char *cmd)
{
	t_listenv	*node;
	char		*key;
	char		*content;

	content = ft_strrchr(cmd, '=');
	content = content + 1;
	if (get_index_of_equal(cmd) != -1)
		key = ft_substr(cmd, 0, get_index_of_equal(cmd));
	node = ft_lstexport_new(key, content);
	return (node);
}

void	fill_export(t_all *all, char **tab_cmd)
{
	int			i;
	t_listenv	*new;

	i = 1;
	(void)all;
	while (tab_cmd[i])
	{
		new = get_export_node(tab_cmd[i]);
		ft_printf("[%s] [%s] [%s]\n", tab_cmd[i], new->key, new->content);
		// if (is_node_empty == 0)
		ft_lstexport_add_back(&(all->listexport), new);
		ft_print_listexport(all->listexport);
		// ft_lstexport_add_back(&(all)->listenv, new);
		i++;
	}
}

void	display_listexport(t_all *all)
{
	t_listenv	*copy;
	t_listenv	*sorted_env;

	sorted_env = ft_lst_dup(all->listenv);
	sort_linked_list(sorted_env);
	copy = ft_lstcat(sorted_env, sorted_env);
	// ft_print_listexport(copy);
	(void)copy;
	// ft_print_listexport(all->listexport);
}

void	ft_export(t_all *all, char **cmd)
{
	if (ft_strlen_array(cmd) == 1)
		display_listexport(all);
	if (ft_strlen_array(cmd) > 1)
		fill_export(all, cmd);
}
