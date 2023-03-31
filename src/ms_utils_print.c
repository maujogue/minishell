/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:02:41 by avaganay          #+#    #+#             */
/*   Updated: 2023/03/31 14:48:34 by avaganay         ###   ########.fr       */
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

void    ft_print_listexport(t_listenv *listexport, t_all *all)
{
	t_listenv *tmp;
	
	tmp = all->listenv;
	while (all->listenv != NULL)
	{
		printf("%s", all->listenv->key);
        printf("%c", '=');
		printf("%s\n", all->listenv->content);
		all->listenv = all->listenv->next;
	}
	all->listenv = tmp;
    if (listexport == NULL)
        return ;
    while (listexport != NULL)
	{
        if (listexport->content == NULL)
            printf("declare -x %s=\"\"\n", listexport->key);
		else
            printf("declare -x %s=\"%s\"\n", listexport->key, listexport->content);
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
