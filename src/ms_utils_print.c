/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:02:41 by avaganay          #+#    #+#             */
/*   Updated: 2023/03/21 15:53:14 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void    ft_print_listenv(t_listenv *listenv, char *cmd)
{
	if (cmd[3] != '\0' && (cmd[4] != ' ' && cmd[4] != '\0'))
	{
		printf("%s", cmd);
		printf("%s\n", ": No such file or directory");
		return ;
	}
    while (listenv != NULL)
	{
		printf("%s", listenv->key);
        printf("%c", '=');
		printf("%s\n", listenv->content);
		listenv = listenv->next;
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
