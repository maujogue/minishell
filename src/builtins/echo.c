/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:06 by maujogue          #+#    #+#             */
/*   Updated: 2023/04/07 13:41:27 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_nbargecho(char **tabecho)
{
	int	i;

	i = 0;
	while (tabecho[i])
	{
		i++;
	}
	return (i);
}

void	ft_printecho(t_all *all, char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '$' || ((arg[0] >= 33 && arg[0] <= 41) && arg[1] == '$') || ((arg[0] >= 91 && arg[0] <= 93) && arg[1] == '$'))
	{
		ft_echo_var(all, arg);
		ft_echo_env(all, arg);
		return ;
	}
	while (arg[i] == '"')
		i++;
	while (arg[i])
	{
		if (arg[i] != '"')
			printf("%c", arg[i]);
		i++;
	}
}

int	ft_echosolo(char *cmd)
{
	int	i;

	i = 4;
	while (cmd[i] == 'e' || cmd[i] == 'c' || cmd[i] == 'h' || cmd[i] == 'o' || cmd[i] == '"' || cmd[i] == '\'')
		i++;
	while (cmd[i] == ' ')
	{
		if (cmd[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

void    ft_echo(t_all *all, char *cmd)
{
    char    **tabecho;
    int     i;
	int		argn;
	
	if (ft_echosolo(cmd))
	{
		printf("\n");
		return ;
	}
	if (ft_strcmp(cmd, "echo") == 0)
	{
		printf("\n");
		return ;
	}
	(void)all;
	i = 1;
	argn = 0;
    tabecho = ft_split(cmd, ' ');
	while ((ft_strcmp(tabecho[i], "-n") == 0) || (ft_strcmp(tabecho[i], "\"-n\"") == 0))
	{
		i++;
		argn = 1;
	}
	// if ((ft_strcmp(tabecho[1], "-n") == 0) || (ft_strcmp(tabecho[1], "\"-n\"") == 0)) 
	// {
	// 	i = 2;
	// 	argn = 1;
	// }
    while (tabecho[i])
	{
		ft_printecho(all, tabecho[i]);
		if (tabecho[2] && tabecho[2][0] != '\0' && i != ft_nbargecho(tabecho) - 1)
			printf(" ");
		i++;
	}
	if (argn == 0)
		printf("\n");
	
}
