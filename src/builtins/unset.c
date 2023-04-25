/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:16 by maujogue          #+#    #+#             */
/*   Updated: 2023/04/25 12:24:17 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_check_valid_arg(char *str)
{
	int		i;

	i = 0;
	if (str[i] >= '0' && str[i] <= '9')
	{
		printf("minishell: unset: '%s': not a valid identifier\n", str);
		return (1);
	}
	while (str[i])
	{
		if ((str[i] >= 33 && str[i] <= 47) || str[i] == '^' || str[i] == '`'
			|| str[i] == '[' || str[i] == ']' || (str[i] >= 123 && str[i] <= 125)
			|| str[i] == '?' || str[i] == '@' || str[i] == '=' || str[i] == ':')
		{
			printf("minishell: unset: '%s': not a valid identifier\n", str);
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
	while (pip->cmd[i] && ft_check_valid_arg(pip->cmd[i]) == 0)
	{
		all->listenv = unset_env_var(pip->cmd[i], all->listenv);
		
		all->listexport = unset_env_var(pip->cmd[i], all->listexport);
		i++;
	}
}
