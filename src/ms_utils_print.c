/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:02:41 by avaganay          #+#    #+#             */
/*   Updated: 2023/03/29 13:28:57 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void    ft_print_listenv(t_all *all, char *cmd)
{
	if (cmd[3] != '\0' && (cmd[4] != ' ' && cmd[4] != '\0'))
	{
		printf("%s", cmd);
		printf("%s\n", ": No such file or directory");
		return ;
	}
    while (all->listenv != NULL)
	{
		printf("%s", all->listenv->key);
        printf("%c", '=');
		printf("%s\n", all->listenv->content);
		all->listenv = all->listenv->next;
	}
}

void    ft_print_listexport(t_listenv *listexport)
{
    if (listexport == NULL)
        return ;
    while (listexport != NULL)
	{
		printf("declare -x %s\n", listexport->content);
		listexport = listexport->next;
	}
}

void	ft_print_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        printf("%s\n",tab[i]);
        i++;
    }
}

void	ft_print_export(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
		printf("%s", "declare -x ");
        printf("%s\n",tab[i]);
        i++;
    }
}
