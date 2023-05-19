/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:06 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/19 15:27:16 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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
	if (!(str[i] == '-' && str[i + 1] == 'n'))
		return (1);
	if (str[i] == '-' && str[i + 1] == 'n')
		i++;
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

void	ft_echo(char **tabecho)
{
	int	i;
	int	argn;
	int	argecho;

	if (ft_strlen_array(tabecho) == 1)
		return ((void)printf("\n"));
	i = 1;
	argn = 0;
	argecho = 0;
	while (tabecho[i])
	{
		if (check_option_n(tabecho[i]) == 0 && argecho == 0)
			argn = 1;
		else
		{
			argecho = 1;
			printf("%s", tabecho[i]);
			if (tabecho[i] && tabecho[i][0] != '\0'
					&& i != ft_strlen_array(tabecho) - 1)
				printf(" ");
		}
		i++;
	}
	if (argn == 0)
		printf("\n");
}
