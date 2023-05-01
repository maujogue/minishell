/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:02:41 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/01 22:57:35 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void    ft_print_listenv(t_all *all, char *cmd, int path_exists)
{
	t_listenv *tmp;
	
    if (path_exists == 1)
        return write_error("bash: env: No such file or directory\n", "", "");
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
    while (ft_strcmp(tab[i], "\0") != 0 || tab[i] != NULL)
    {
        printf("%s\n",tab[i]);
        i++;
    }
}

void	ft_print_tab_pipe(char **tab)
{
    int i;

    i = 0;
    while (tab[i] && ft_strcmp(tab[i], "\0") != 0)
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

void    ft_print_tabarg(char **tab)
{
    int i;
    
    i = 0;
    while (tab[i])
    {
        if (tab[i] != NULL)
            printf("   %s", tab[i]);
        i++;
    }
}
