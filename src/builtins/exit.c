/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:00 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/26 13:57:43 by maujogue         ###   ########.fr       */
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

int	check_multiple_number_arg(char **tab_cmd)
{
	int	i;
	int	err;

	i = 1;
	err = 0;
	while (tab_cmd[i])
	{
		ft_atoi_exit(tab_cmd[i], &err);
		if (err == 1)
			return (1);
		i++;
	}
	if (i == 2)
		return (1);
	write_error("exit\nbash: ", "exit", ": too many arguments\n");
	g_status = 1;
	return (0);
}

void	exit_arg_code(t_pip *pip)
{
	long long	code;
	int			err;

	err = 0;
	code = ft_atoi_exit(pip->cmd[1], &err);
	if (err == 1)
	{
		write_error("exit\nbash: exit: ",
			pip->cmd[1], ": numeric argument required\n");
		g_status = 2;
	}
	else if (ft_strlen_array(pip->cmd) > 2)
	{
		write_error("exit\nbash: ", "exit", ": too many arguments\n");
		g_status = 1;
	}
	else
		g_status = code % 256;
}

void	ft_exit(t_all *all, t_pip *pip)
{
	if (pip->cmd[1] && check_multiple_number_arg(pip->cmd) == 0)
		return ;
	else if (pip->cmd[1])
		exit_arg_code(pip);
	else
		g_status = 0;
	close_p(pip, pip->nb_arg);
	free_exit(all, pip, 1, "");
}
