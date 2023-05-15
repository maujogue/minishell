/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:02:41 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/15 18:44:13 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_print_listenv(t_all *all, char *cmd, int path_exists)
{
	t_listenv	*tmp;

	if (path_exists == 1)
	{
		write_error("bash: env: No such file or directory\n", "", "");
		return ;
	}
	if (cmd[3] != '\0' && (cmd[4] != ' ' && cmd[4] != '\0'))
	{
		printf("%s", cmd);
		printf("%s\n", ": No such file or directory");
		return ;
	}
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
		printf("declare -x %s=%s\n", lst->key, lst->content);
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
