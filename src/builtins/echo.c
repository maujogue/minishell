/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathisaujogue <mathisaujogue@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:06 by maujogue          #+#    #+#             */
/*   Updated: 2023/04/28 11:33:53 by mathisaujog      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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

int	ft_echo_infini_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\"')
	{
		i++;
		if (str[i] == '-' && str[i + 1] == 'n')
			i++;
		while (str[i] == 'n' && str[i])
			i++;
		if (str[i] == '\"')
			i++;
		if (str[i] == '\0')
			return (1);	
	}
	else
	{
		if (str[i] == '-' && str[i + 1] == 'n')
			i++;
		while (str[i] == 'n' && str[i])
			i++;
		if (str[i] == '\0')
			return (1);	
	}
	return (0);
}

int	check_option_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1] == 'n')
		i++;
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

void    ft_echo(t_all *all, char **tabecho)
{
    int     i;
	int		argn;
	
	if (ft_strlen_array(tabecho) == 1)
	{
		printf("\n");
		return ;
	}
	(void)all;
	i = 1;
	argn = 0;
    while (tabecho[i])
	{
		if (check_option_n(tabecho[i]) == 0)
			argn = 1;
		else
		{
			ft_printecho(all, tabecho[i]);
			if (tabecho[i] && tabecho[i][0] != '\0' && i != ft_strlen_array(tabecho) - 1)
				printf(" ");
		}
		i++;
	}
	if (argn == 0)
		printf("\n");
}
