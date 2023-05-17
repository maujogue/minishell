/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:02:41 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/17 15:15:08 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_print_listenv(t_all *all)
{
	t_listenv	*tmp;

	tmp = all->listenv;
	while (all->listenv != NULL)
	{
		printf("%s", all->listenv->key);
		printf("%c", '=');
		printf("%s\n", all->listenv->content);
		all->listenv = all->listenv->next;
	}
	all->listenv = tmp;
}

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

void	ft_print_listexport(t_listenv *lst)
{
	while (lst != NULL)
	{
		if (lst->content)
			printf("declare -x %s=\"%s\"\n", lst->key, lst->content);
		else
			printf("declare -x %s\n", lst->key);
		lst = lst->next;
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
