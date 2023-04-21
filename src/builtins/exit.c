/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:00 by maujogue          #+#    #+#             */
/*   Updated: 2023/04/21 11:16:02 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int check_numeric(char *str)
{
    int i;

    i = 0;
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
    if (ft_strlen_array(cmd) > 2)
    {
        write_error("exit\nbash: exit: too many arguments\n");
        exit(1);    
    }
    else if (cmd[1] && check_numeric(cmd[1]) == 1)
    {
        write_error("exit\nbash: exit: s: numeric argument required\n");
    }
    else if (cmd[1])
        exit(ft_atoi(cmd[1]));
    else
        exit(0);
}