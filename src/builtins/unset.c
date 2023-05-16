/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathisaujogue <mathisaujogue@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:16 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/16 15:45:56 by mathisaujog      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_check_valid_arg(char *str)
{
	int		i;

	i = 0;
	if (str[i] >= '0' && str[i] <= '9')
	{
		write_error("minishell: unset: '", str, "': not a valid identifier\n");
		g_status = 1;
		return (1);
	}
	return (check_invalid_identifier(str, "unset"));
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
