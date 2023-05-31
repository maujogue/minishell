/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:02:41 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/30 11:10:29 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i] != NULL)
		{
			printf("%s\n", tab[i]);
			i++;
		}
	}
}

void	ft_print_tab_pipe(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] && ft_strcmp(tab[i], "\0") != 0)
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

void	ft_print_tabexport(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("declare -x %s\n", tab[i]);
		i++;
	}
}

void	ft_print_tabarg(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i] != NULL)
			printf("   %s", tab[i]);
		i++;
	}
}
