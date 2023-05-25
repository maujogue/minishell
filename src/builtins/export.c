/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:11 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/25 16:15:21 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	check_invalid_identifier_export(char *str, char *cmd, int slash)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr("^`!&+,#\\*.%()[];<>{}|?", str[i]) != NULL
			|| (str[0] >= '0' && str[0] <= '9') || str[0] == '=' || slash == 1)
		{
			write_error("minishell: ", cmd, ": `");
			write_error("", str, "': not a valid identifier\n");
			g_status = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

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

void	sort_linked_list(t_listenv *head)
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

void	display_listexport(t_all *all)
{
	t_listenv	*export;
	t_listenv	*env_copy;

	env_copy = ft_lst_dup(all->listenv);
	export = ft_lstcat(env_copy, all->listexport);
	sort_linked_list(export);
	ft_print_listexport(export);
	// free_listenv(env_copy);
	// free_listenv(export);
}

void	ft_export(t_all *all, char **cmd)
{
	if (ft_strlen_array(cmd) == 1)
		display_listexport(all);
	if (ft_strlen_array(cmd) > 1)
		fill_export(all, cmd);
}
