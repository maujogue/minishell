/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:04:25 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/08 15:04:06 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*ft_strdupexport_utils(char *res, char *key, size_t *i)
{
	while (key && key[*i])
	{
		res[*i] = key[*i];
		i++;
	}
	res[*i] = '=';
	res[*i + 1] = '"';
	*i = *i + 2;
	return (res);
}

char	*ft_strdupexport(char *key, char *content)
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
	res = ft_strdupexport_utils(res, key, &i);
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
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (tabexport[i])
	{
		j = i + 1;
		while (tabexport[j])
		{
			if (ft_strcmp(tabexport[i], tabexport[j]) > 0)
			{
				tmp = tabexport[i];
				tabexport[i] = tabexport[j];
				tabexport[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (tabexport);
}

char	**ft_creat_tab_sort_export(t_listenv *listexport, t_all *all)
{
	char		**tab;
	int			i;
	int			sizenv;
	int			sizexport;
	t_listenv	*tmp;

	i = 0;
	tmp = all->listenv;
	sizenv = ft_lstexportsize(all->listenv);
	sizexport = ft_lstexportsize(listexport);
	tab = malloc(sizeof(char *) * (sizexport + sizenv + 1));
	while (i < sizenv)
	{
		tab[i] = ft_strdupexport(all->listenv->key, all->listenv->content);
		all->listenv = all->listenv->next;
		i++;
	}
	all->listenv = tmp;
	sizexport = sizexport + i;
	if (sizexport == i)
	{
		tab[i] = NULL;
		return (tab);
	}
	tmp = listexport;
	while (i <= sizexport && listexport)
	{
		if (listexport->content == NULL)
			tab[i] = ft_strdup(listexport->key);
		else
			tab[i] = ft_strdupexport(listexport->key, listexport->content);
		listexport = listexport->next;
		i++;
	}
	listexport = tmp;
	tab[i] = NULL;
	return (tab);
}

void	ft_print_listexport(t_all *all)
{
	char	**tabexport;

	tabexport = ft_creat_tab_sort_export(all->listexport, all);
	tabexport = ft_sort_tabexport(tabexport);
	ft_print_tabexport(tabexport);
}
