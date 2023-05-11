/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:11 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/11 11:02:51 by maujogue         ###   ########.fr       */
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
			if (ft_check_double_var(var[i], *listexport, all) == 1)
			{
				printf("DOUBLE FIND\n");
				ft_replace_double(var[i], *listexport, all);
			}
			else
			{
				new = malloc(sizeof(t_listenv));
				ft_export_fillkeycontentvar(new, var[i]);
				new->next = NULL;
				ft_lstexportadd_back(listexport, new);
			}
		}
		i++;
	}
}

t_listenv	*ft_fill_var_export(t_listenv *listexport, t_all *all, char **cmd)
{
	if (ft_strlen_array(cmd) == 1)
		ft_print_listexport(listexport, all);
	return (listexport);
}

t_listenv	*ft_fill_var_env(t_listenv *listexport, t_all *all, char **cmd)
{
	if (ft_strlen_array(cmd) > 1)
		ft_export_fill_lstvar(&listexport, cmd, &all);
	return (listexport);
}

void	ft_export(char **envp, t_all *all, char **cmd)
{
	ft_sort_env(envp);
	all->listexport = ft_fill_var_export(all->listexport, all, cmd);
	all->listenv = ft_fill_var_env(all->listenv, all, cmd);
}
