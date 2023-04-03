/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:02:41 by avaganay          #+#    #+#             */
/*   Updated: 2023/04/03 14:39:58 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void    ft_print_listenv(t_all *all, char *cmd)
{
	t_listenv *tmp;
	
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
    int i;

    i = 0;
    while (ft_strcmp(tab[i], "\0") != 0)
    {
        printf("%s\n",tab[i]);
        i++;
    }
}

void	ft_print_tabexport(char **tab)
{
    int i;

    i = 0;
    while (ft_strcmp(tab[i], "\0") != 0)
    {
        printf("declare -x %s\n",tab[i]);
        i++;
    }
}
