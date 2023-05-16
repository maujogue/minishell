/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathisaujogue <mathisaujogue@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:11 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/16 15:42:05 by mathisaujog      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	swap_nodes(t_listenv *a, t_listenv *b)
{
	char	*temp_key;
	char	*temp_content;

	temp_key = a->key;
	a->key = b->key;
	b->key = temp_key;
	temp_content = a->content;
	a->content = b->content;
	b->content = temp_content;
}

void sort_linked_list(t_listenv *head)
{
    t_listenv	*lptr;
	t_listenv	*ptr1;
    int			swapped;
	
	swapped = 1;
	lptr = NULL;
    while (swapped)
	{
        swapped = 0;
        ptr1 = head;
        while (ptr1->next != lptr)
		{
            if (ft_strcmp(ptr1->key, ptr1->next->key) > 0)
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
	printf("-->%d\n", i);
	return (i);
}

t_listenv	*get_export_node(char *cmd)
{
	t_listenv	*node;
	char		*key;
	char		*content;

	key = NULL;
	content = ft_strdup(ft_strrchr(cmd, '='));
	if (content)
	{	
		content = content + 1;
		key = ft_substr(cmd, 0, get_index_of_equal(cmd));
	}
	else
		key = ft_strdup(cmd);
	node = ft_lstexport_new(key, content);
	printf("{%s} {%s}\n", key, content);
	return (node);
}

void	fill_export(t_all *all, char **tab_cmd)
{
	int			i;
	t_listenv	*new;

	i = 1;
	while (tab_cmd[i])
	{
		if (check_invalid_identifier(tab_cmd[i], "export") == 1)
			return ;
		new = get_export_node(tab_cmd[i]);
		if (new->content)
		{
			if (check_lst_key_exists(all->listenv, new->key) == 0)
				replace_env_arg(all->listenv, new->key, new->content);
			else if (check_lst_key_exists(all->listexport, new->key) == 0)
			{
				all->listexport = unset_env_var(new->key, all->listexport);
				ft_lstexport_add_back(&(all)->listenv, new);
			}
			else
				ft_lstexport_add_back(&(all)->listenv, new);
		}
		else
		{
			if (check_lst_key_exists(all->listexport, new->key) == 0)
				replace_env_arg(all->listexport, new->key, new->content);
			else if (check_lst_key_exists(all->listenv, new->key) == 1)
				ft_lstexport_add_back(&(all->listexport), new);
		}
		i++;
	}
}

void	display_listexport(t_all *all)
{
	t_listenv	*export;
	t_listenv	*env_copy;

	env_copy = ft_lst_dup(all->listenv);
	export = ft_lstcat(env_copy, all->listexport);
	sort_linked_list(export);
	ft_print_listexport(export);
}

void	ft_export(t_all *all, char **cmd)
{
	if (ft_strlen_array(cmd) == 1)
		display_listexport(all);
	if (ft_strlen_array(cmd) > 1)
		fill_export(all, cmd);
}
