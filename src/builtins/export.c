/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathisaujogue <mathisaujogue@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:11 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/04 16:51:26 by mathisaujog      ###   ########.fr       */
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

void	display_listexport(t_all *all, t_pip *pip)
{
	t_listenv	*export;
	t_listenv	*env_copy;

	env_copy = ft_lst_dup(all->listenv);
	if (!env_copy)
		free_exit(all, pip, 1, "bash: Malloc error\n");
	export = ft_lstcat(env_copy, all->listexport);
	if (!export)
		free_exit(all, pip, 1, "bash: Malloc error\n");
	sort_linked_list(export);
	ft_print_listexport(export);
	free_listenv(env_copy);
	free_listenv(export);
}

void	ft_export(t_all *all, t_pip *pip)
{
	if (ft_strlen_array(pip->cmd) == 1)
		display_listexport(all, pip);
	if (ft_strlen_array(pip->cmd) > 1)
		fill_export(all, pip);
}
