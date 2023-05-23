/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:00 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/23 15:16:37 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_isspace(char c)
{
	if (c == '\f' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == ' ')
		return (1);
	return (0);
}

long long	ft_atoi_exit(const char *str, int *err)
{
	int			i;
	long		neg;
	long long	sum;

	i = 0;
	neg = 1;
	sum = 0;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			neg *= -1;
	while (str[i] && (ft_isspace(str[i]) || str[i] == '0'))
		i++;
	while (str[i])
	{
		sum = (sum * 10) + (str[i] - 48);
		if (str[i] < '0' || str[i] > '9')
			*err = 1;
		i++;
	}
	return (sum * neg);
}

void	ft_exit(t_all *all, t_pip *pip)
{
	long long	code;
	int			err;

	if (ft_strlen_array(pip->cmd) > 2)
	{
		write_error("exit\nbash: ", "exit", ": too many arguments\n");
		g_status = 1;
	}
	else if (pip->cmd[1])
	{
		code = ft_atoi_exit(pip->cmd[1], &err);
		if (err == 1)
		{
			write_error("exit\nbash: exit: ",
				pip->cmd[1], ": numeric argument required\n");
			g_status = 2;
		}
		else
			g_status = code % 256;
	}
	else
		g_status = 0;
	free_exit(all, pip, 1, "");
}
