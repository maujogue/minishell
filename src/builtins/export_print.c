/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:04:25 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/05 14:23:05 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*ft_strdupexport(const char *key, char *content)
{
	char		*res;
	size_t		len;
	size_t		len2;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	len = ft_strlen(key);
	len2 = ft_strlen(content);
	res = malloc(sizeof(char) * (len + len2 + 4));
	if (!(res))
		return (NULL);
	while (key && key[i])
	{
		res[i] = key[i];
		i++;
	}
	res[i] = '=';
	res[i + 1] = '"';
	i = i + 2;
	while (content && content[j])
	{
		res[i] = content[j];
		i++;
		j++;
	}
	res[i] = '"';
	res[i + 1] = '\0';
	return (res);
}

char	**ft_sort_tabexport(char **tabexport)
{
	// char	*tmp;
	int	i;
	int	j;

	i = 0;
	while (tabexport[i])
	{
		j = i + 1;
		while (tabexport[j])
		{
			// if (ft_strncmp(tabexport[i], tabexport[j], ft_strlen(tabexport[i])) > 0)
			// {
			// 	tmp = tabexport[i];
			// 	tabexport[i] = tabexport[j];
			// 	tabexport[j] = tmp;
			// 	printf("%s\n", tmp);
			// }
			j++;
		}
		i++;
	}
	return (tabexport);
}

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
	while (i < sizenv)
	{
		// printf("i:%d\n", i);
		// printf("sizenv:%d\n", sizenv);
		// printf("sizexport:%d\n", sizexport);
		// printf("%s\n", all->listenv->content);
		tab[i] = ft_strdupexport(all->listenv->key, all->listenv->content);
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
	// printf("export%d\n", sizexport);
	// printf("%s\n", tab[i]);
	// tab[i] = ft_strdup(listexport->key);
	// tab[i] = malloc(1);
	while (i <= sizexport && listexport)
	{
		// printf("i%d\n", i);
		// printf("%s\n", tab[i]);
		if (listexport->content == NULL)
			tab[i] = ft_strdup(listexport->key);
		else
			tab[i] = ft_strdupexport(listexport->key, listexport->content);
		listexport = listexport->next;
		i++;
	} 
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
	tabexport = ft_sort_tabexport(tabexport);
	ft_print_tabexport(tabexport);
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
