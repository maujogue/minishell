/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:16 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/17 10:40:57 by maujogue         ###   ########.fr       */
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
