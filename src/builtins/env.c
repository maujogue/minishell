/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:28:44 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/05 13:42:22 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*get_env_content(t_all *all, t_pip *pip, t_listenv	*listenv, char *arg)
{
	char	*res;

	while (listenv)
	{
		if (ft_strcmp(listenv->key, arg) == 0)
		{
			if (!listenv->content)
				res = NULL;
			else
			{
				res = ft_strdup(listenv->content);
				if (!res)
					free_exit(all, pip, 1, "bash: Malloc error\n");
				return (res);
			}
		}
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

int	replace_env_arg(t_listenv	*listenv, char *arg, char *replacement)
{
	while (listenv)
	{
		if (ft_strcmp(listenv->key, arg) == 0)
		{
			free(listenv->content);
			listenv->content = ft_strdup(replacement);
			if (!listenv->content)
				return (1);
			return (0);
		}
		listenv = listenv->next;
	}
	return (0);
}

void	ft_env(t_all *all, t_pip *pip)
{
	if (ft_strlen_array(pip->cmd) == 1)
		ft_print_listenv(all);
	else
	{
		g_status = 127;
		write_error("env: ‘", pip->cmd[1], "’: No such file or directory\n");
	}
}
