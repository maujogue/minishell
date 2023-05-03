/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:00 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/03 11:16:19 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int g_status;

int		ft_isspace(char c)
{
	if (c == '\f' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == ' ')
		return (1);
	return (0);
}

long long	ft_atoi_exit(const char *str, int i, int *pbm)
{
	int			j;
	long		neg;
	long long	sum;

	neg = 1;
	sum = 0;
	j = 0;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			neg *= -1;
	while (str[i] && (ft_isspace(str[i]) || str[i] == '0'))
		i++;
	while (str[i] >= '0' && str[i] <= '9' && ++j)
	{
		sum = (sum * 10) + (str[i] - 48);
		if (((i == 18 && neg == 1) && (str[i] > '7' && str[i] <= '9'))
			|| ((i == 19 && neg == -1) && (str[i] == '9')))
			*pbm = 1;
		i++;
	}
	while (str[i++])
		j++;
	if ((j > 19 && neg == 1) || (j > 20 && neg == -1))
		*pbm = 1;
	return (sum * neg);
}

int check_numeric(char *str)
{
    int i;

    i = 0;
    if (str[i] == '-' || str[i] == '+')
		i++;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (1);
        i++;
    }
    return (0);
}

void ft_exit(char **cmd)
{
    long long   code;
    int         err;

    if (ft_strlen_array(cmd) > 2)
    {
        write_error("exit\nbash: ", "exit", ": too many arguments\n");
        g_status = 1;
    }
    else if (cmd[1])
    {
        code = ft_atoi_exit(cmd[1], 0, &err);
        if (err == 1)
        {
            write_error("exit\nbash: exit: ", cmd[1],": numeric argument required\n");
            g_status = 2;
        }
        else
            g_status = code % 256;
    }
    else
        g_status = 0;
    exit(g_status);
}