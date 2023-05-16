/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathisaujogue <mathisaujogue@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:28:44 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/16 15:00:19 by mathisaujog      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*get_env_content(t_listenv	*listenv, char *arg)
{
	while (listenv)
	{
		if (ft_strcmp(listenv->key, arg) == 0)
			return (ft_strdup(listenv->content));
		listenv = listenv->next;
	}
	return (NULL);
}

int	check_lst_key_exists(t_listenv	*listenv, char *arg)
{
	while (listenv)
	{
		if (ft_strcmp(listenv->key, arg) == 0)
			return (0);
		listenv = listenv->next;
	}
	return (1);
}

void	replace_env_arg(t_listenv	*listenv, char *arg, char *replacement)
{
	while (listenv)
	{
		if (ft_strcmp(listenv->key, arg) == 0)
		{
			// free(listenv->content);
			listenv->content = ft_strdup(replacement);
			return ;
		}
		listenv = listenv->next;
	}
}

t_listenv	*unset_env_var(char *cmd, t_listenv *lst)
{
	t_listenv	*prev;
	t_listenv	*tmp;

	tmp = lst;
	prev = NULL;
	while (lst)
	{
		if (ft_strcmp(cmd, lst->key) == 0)
		{
			// free(lst->key);
			// free(lst->content);
			if (prev)
			{
				prev->next = lst->next;
				free(lst);
				break ;
			}
			else
				return (free(lst), lst->next);
		}
		prev = lst;
		lst = lst->next;
	}
	lst = tmp;
	return (lst);
}

void	free_listenv(t_listenv *lst)
{
	t_listenv	*temp;

	while (lst)
	{
		temp = lst->next;
		if (!lst->content)
			free(lst->content);
		if (!lst->key)
			free(lst->key);
		if (!lst)
			free(lst);
		lst = temp;
	}
}

void	ft_env(t_all *all, t_pip *pip)
{
	if (ft_strlen_array(pip->cmd) == 1)
		ft_print_listenv(all, pip->cmd[0], !pip->path);
	else
	{
		g_status = 127;
		write_error("env: ‘",pip->cmd[1],"’: No such file or directory\n");
	}
}
