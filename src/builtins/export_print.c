/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:04:25 by avaganay          #+#    #+#             */
/*   Updated: 2023/03/31 16:54:49 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char    **ft_creat_tab_sort_export(t_listenv *listexport, t_all *all)
{
	char	**tab;
	int		i;
	int		sizenv;
	int		sizexport;
	t_listenv	*tmp;

	i = 0;
	tmp = all->listenv;
	sizenv = ft_lstexportsize(all->listenv);
	sizexport = ft_lstexportsize(listexport);
	tab = malloc(sizeof(char *) * (sizexport + sizenv + 1));
	while (i < sizenv - 1)
	{
		// printf("i:%d\n", i);
		// printf("sizenv:%d\n", sizenv);
		// printf("sizexport:%d\n", sizexport);
		// printf("%s\n", all->listenv->content);
		tab[i] = ft_strdup(all->listenv->content);
		// tab[i] = malloc(sizeof(char) * ft_strlen(all->listenv->content));
		all->listenv = all->listenv->next;
		i++;
	}
	all->listenv = tmp;
	sizexport = sizexport + i;
	if (sizexport == i)
	{
		tab[i] = "\0";
		return (tab);
	}
	tmp = listexport;
	// while (i < sizexport)
	// {
		// tab[i] = ft_strdup(listexport->content);
		listexport = listexport->next;
	// } 
	listexport = tmp;
	tab[i] = "\0";
	return (tab);
}

void    ft_print_listexport(t_listenv *listexport, t_all *all)
{
    char		**tabexport;
	// t_listenv	*tmp;
	
	tabexport = ft_creat_tab_sort_export(listexport, all);
	// (void)tabexport;
	ft_print_tab(tabexport);
	// tmp = all->listenv;
	// while (all->listenv != NULL)
	// {
	// 	printf("%s", all->listenv->key);
    //     printf("%c", '=');
	// 	printf("%s\n", all->listenv->content);
	// 	all->listenv = all->listenv->next;
	// }
	// all->listenv = tmp;
    // if (listexport == NULL)
    //     return ;
    // while (listexport != NULL)
	// {
    //     if (listexport->content == NULL)
    //         printf("declare -x %s=\"\"\n", listexport->key);
	// 	else
    //         printf("declare -x %s=\"%s\"\n", listexport->key, listexport->content);
	// 	listexport = listexport->next;
	// }
}
