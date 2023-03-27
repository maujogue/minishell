/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:06 by maujogue          #+#    #+#             */
/*   Updated: 2023/03/27 15:58:28 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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

void	ft_printecho(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] == '"')
		i++;
	while (arg[i])
	{
		if (arg[i] != '"')
			printf("%c", arg[i]);
		i++;
	}
}

void    ft_echo(t_all *all, char *cmd)
{
    char    **tabecho;
    int     i;
	int		argn;
	
	if (ft_strcmp(cmd, "echo") == 0)
	{
		printf("\n");
		return ;
	}
	(void)all;
	i = 1;
	argn = 0;
    tabecho = ft_split(cmd, ' ');
	if (ft_strcmp(tabecho[1], "-n") == 0) 
	{
		i = 2;
		argn = 1;
	}
    while (tabecho[i])
	{
		ft_printecho(tabecho[i]);
		if (tabecho[2] && tabecho[2][0] != '\0' && i != ft_nbargecho(tabecho) - 1)
			printf(" ");
		i++;
	}
	if (argn == 0)
		printf("\n");
	
}