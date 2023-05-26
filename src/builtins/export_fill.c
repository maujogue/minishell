/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:20:46 by mathisaujog       #+#    #+#             */
/*   Updated: 2023/05/26 11:15:57 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	get_index_of_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	return (i);
}

t_listenv	*get_export_node(char *cmd)
{
	t_listenv	*node;
	char		*key;
	char		*content;
	char		*temp;

	key = NULL;
	content = ft_strdup(ft_strchr(cmd, '='));
	if (content)
	{	
		temp = ft_strdup(content + 1);
		free(content);
		content = ft_strdup(temp);
		free(temp);
		key = ft_substr(cmd, 0, get_index_of_equal(cmd));
	}
	else
		key = ft_strdup(cmd);
	node = ft_lstexport_new(key, content);
	free(key);
	free(content);
	return (node);
}

void	fill_export_empty_variable(t_all *all, t_listenv *new)
{
	if (check_lst_key_exists(all->listexport, new->key) == 0)
		replace_env_arg(all->listexport, new->key, new->content);
	else if (check_lst_key_exists(all->listenv, new->key) == 1)
		ft_lstexport_add_back(&(all->listexport), new);
}

void	fill_export_variable(t_all *all, t_listenv *new)
{
	if (check_lst_key_exists(all->listenv, new->key) == 0)
		replace_env_arg(all->listenv, new->key, new->content);
	else if (check_lst_key_exists(all->listexport, new->key) == 0)
	{
		all->listexport = unset_env_var(new->key, all->listexport);
		ft_lstexport_add_back(&(all)->listenv, new);
	}
	else
		ft_lstexport_add_back(&(all)->listenv, new);
}

void	fill_export(t_all *all, char **tab_cmd)
{
	int			i;
	t_listenv	*new;

	i = 1;
	while (tab_cmd[i])
	{
		if (check_invalid_identifier_export(tab_cmd[i], "export", 0) == 1)
			return ;
		new = get_export_node(tab_cmd[i]);
		if (ft_strchr(new->key, '/') != 0 || ft_strchr(new->key, '@') != 0
			|| ft_strchr(new->key, '-') != 0 || ft_strchr(new->key, ':') != 0)
		{
			check_invalid_identifier_export(tab_cmd[i], "export", 1);
			return ;
		}
		if (new->content)
			fill_export_variable(all, new);
		else
			fill_export_empty_variable(all, new);
		i++;
	}
}
