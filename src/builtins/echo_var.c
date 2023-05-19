/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:40:55 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/19 15:29:30 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*ft_mallockey_var(char *arg, int *i)
{
	char	*key;

	if (arg[0] == '\"' || arg[1] == '\"')
	{
		*i = 2;
		key = malloc(sizeof(char) * (ft_strlen(arg) - 3));
		while (arg[*i + 1])
		{
			key[*i - 2] = arg[*i];
			*i += 1;
		}	
	}
	else
	{
		*i = 1;
		key = malloc(sizeof(char) * (ft_strlen(arg) - 1));
		while (arg[*i])
		{
			key[*i - 1] = arg[*i];
			*i += 1;
		}
		key[*i - 1] = '\0';
	}
	return (key);
}

void	ft_print_before_var(char *arg)
{
	if (arg[0] != '$' && ((arg[0] >= 33 && arg[0] <= 46)
			|| arg[0] == 91 || arg[0] == 93))
		printf("%c", arg[0]);
}

char	*ft_mallockey_env(char *arg, int *i)
{
	char	*key;

	if (arg[0] == '\"' || arg[1] == '\"' || (arg[0] >= 91 && arg[0] <= 93)
		|| (arg[0] >= 33 && arg[0] <= 46 && arg[0] != 36))
	{
		*i = 2;
		key = malloc(sizeof(char) * (ft_strlen(arg) - 3));
		while (arg[*i])
		{
			key[*i - 2] = arg[*i];
			*i += 1;
		}	
	}
	else
	{
		*i = 1;
		key = malloc(sizeof(char) * (ft_strlen(arg) - 1));
		while (arg[*i])
		{
			key[*i - 1] = arg[*i];
			*i += 1;
		}
		key[*i - 1] = '\0';
	}
	return (key);
}
