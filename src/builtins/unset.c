/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathisaujogue <mathisaujogue@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:16 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/04 15:59:48 by mathisaujog      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	check_invalid_identifier_unset(char *str, char *cmd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr("^`!&+,#\\*.%()/[];<>{}|?:@=-", str[i]) != NULL
			|| (str[0] >= '0' && str[0] <= '9') || str[0] == '=')
		{
			write_error("minishell: ", cmd, ": `");
			write_error("", str, "': not a valid identifier\n");
			g_status = 1;
			return (1);
		}
		i++;
	}
	return (0);
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
			free(lst->key);
			free(lst->content);
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

void	ft_unset(t_all *all, t_pip *pip)
{
	int	i;

	i = 1;
	if (ft_strlen_array(pip->cmd) <= 1)
		return ;
	while (pip->cmd[i])
	{
		if (check_invalid_identifier_unset(pip->cmd[i], "unset") == 0)
		{
			all->listenv = unset_env_var(pip->cmd[i], all->listenv);
			all->listexport = unset_env_var(pip->cmd[i], all->listexport);
		}
		i++;
	}
}
