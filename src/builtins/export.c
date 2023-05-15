/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:11 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/15 15:59:40 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_export_fill_lstvar(t_listenv **listexport, char **var, t_all **all)
{
	int			i;
	int			n;
	t_listenv	*new;

	i = 1;
	n = 0;
	while (var[n])
		n++;
	n--;
	while (i <= n)
	{
		if (ft_check_name_var(var[i]) == 0)
		{
			new = malloc(sizeof(t_listenv));
			ft_export_fillkeycontentvar(new, var[i]);
			new->next = NULL;
			if (ft_check_double_var(var[i], *listexport, all) == 1)
			{
				printf("DOUBLE FIND\n");
				if (new->content && new->content[0])
				{		
					if (ft_check_double_var(var[i], (*all)->listenv, all) == 1)
						ft_replace_double(var[i],(*all)->listenv, all);
					else
						ft_lstexportadd_back(&(*all)->listenv, new);
				}
				else if (new->content)
				{
					ft_replace_double(var[i], *listexport, all);
				}
			}
			else
			{
				// if (new->content && new->content[0])
				// 	ft_lstexportadd_back(&(*all)->listenv, new);
				// else
					ft_lstexportadd_back(listexport, new);
			}
		}
		i++;
	}
}

void	ft_export(t_all *all, char **cmd)
{
	if (ft_strlen_array(cmd) == 1)
		ft_print_listexport(all->listexport, all);
	if (ft_strlen_array(cmd) > 1)
		ft_export_fill_lstvar(&all->listexport, cmd, &all);
}
