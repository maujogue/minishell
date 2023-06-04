/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathisaujogue <mathisaujogue@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:20:46 by mathisaujog       #+#    #+#             */
/*   Updated: 2023/06/04 16:51:26 by mathisaujog      ###   ########.fr       */
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
		if (!(temp = ft_strdup(content + 1)))
			return (free(key), free(content), NULL);
		free(content);
		if (!(content = ft_strdup(temp)))
			return (free(temp), free(key), NULL);
		free(temp);
		key = ft_substr(cmd, 0, get_index_of_equal(cmd));
	}
	else
		key = ft_strdup(cmd);
	if (!key)
		return (free(key), free(content), NULL);
	node = ft_lstexport_new(key, content);
	return (free(key), free(content), node);
}

void	fill_export_empty_variable(t_all *all, t_pip *pip, t_listenv *new)
{
	if (check_lst_key_exists(all->listexport, new->key) == 0)
	{
		if (replace_env_arg(all->listexport, new->key, new->content) == 1)
			free_exit(all, pip, 1, "bash: Malloc error\n");
	}
	else if (check_lst_key_exists(all->listenv, new->key) == 1)
		ft_lstexport_add_back(&(all->listexport), new);
}

void	fill_export_variable(t_all *all, t_pip *pip, t_listenv *new)
{
	if (check_lst_key_exists(all->listenv, new->key) == 0)
	{
		if (replace_env_arg(all->listenv, new->key, new->content) == 1)
			free_exit(all, pip, 1, "bash: Malloc error\n");
	}
	else if (check_lst_key_exists(all->listexport, new->key) == 0)
	{
		all->listexport = unset_env_var(new->key, all->listexport);
		ft_lstexport_add_back(&(all)->listenv, new);
	}
	else
		ft_lstexport_add_back(&(all)->listenv, new);
}

void	fill_export(t_all *all, t_pip *pip)
{
	int			i;
	t_listenv	*new;

	i = 1;
	while (pip->cmd[i])
	{
		if (check_invalid_identifier_export(pip->cmd[i], "export", 0) == 1)
			return ;
		if (!(new = get_export_node(pip->cmd[i])))
			free_exit(all, pip, 1, "bash: Malloc error\n");
		if (ft_strchr(new->key, '/') != 0 || ft_strchr(new->key, '@') != 0
			|| ft_strchr(new->key, '-') != 0 || ft_strchr(new->key, ':') != 0)
		{
			check_invalid_identifier_export(pip->cmd[i], "export", 1);
			return ;
		}
		if (new->content)
			fill_export_variable(all, pip, new);
		else
			fill_export_empty_variable(all, pip, new);
		i++;
	}
}
