/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:04:25 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/08 13:34:23 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	**ft_sort_tabexport(char **tabexport)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (tabexport[i])
	{
		j = i + 1;
		while (tabexport[j])
		{
			if (ft_strcmp(tabexport[i], tabexport[j]) > 0)
			{
				tmp = tabexport[i];
				tabexport[i] = tabexport[j];
				tabexport[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (tabexport);
}

void	ft_print_listexport(t_all *all)
{
	char	**tabexport;

	tabexport = lst_to_tab(all->listenv);
	tabexport = ft_sort_tabexport(tabexport);
	ft_print_tabexport(tabexport);
}
