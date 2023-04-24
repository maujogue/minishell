/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:28:44 by maujogue          #+#    #+#             */
/*   Updated: 2023/04/24 15:12:20 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*get_env_content(t_listenv	*listenv, char *arg)
{
	while (listenv)
	{
		if (ft_strncmp(listenv->key, arg, ft_strlen(arg)) == 0)
			return (ft_strdup(listenv->content));
		listenv = listenv->next;
	}
	return (NULL);
}

void	replace_env_arg(t_listenv	*listenv, char *arg, char *replacement)
{
	while (listenv)
	{
		if (ft_strncmp(listenv->key, arg, ft_strlen(arg)) == 0)
		{
			free(listenv->content);
			listenv->content = ft_strdup(replacement);
			return ;
		}
		listenv = listenv->next;
	}
}

void	unset_env_var(char *cmd, t_listenv *tmp)
{
	t_listenv	*prev;

	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(cmd, tmp->key))
		{
			prev->next = tmp->next;
			free(tmp->key);
			free(tmp->content);
			free(tmp);
		}
		prev = tmp;
		tmp = tmp->next;
	}
}