/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:40:55 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/08 11:46:12 by avaganay         ###   ########.fr       */
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

void	ft_echo_var(t_all *all, char *arg)
{
	char		*key;
	int			i;
	t_listenv	*tmp;

	tmp = all->listexport;
	i = 0;
	key = ft_mallockey_var(arg, &i);
	if (!all->listexport)
		return ;
	while (all->listexport != NULL)
	{
		if (ft_strcmp(key, all->listexport->key) == 0)
		{
			if (all->listexport->content != NULL)
				printf("%s", all->listexport->content);
			all->listexport = tmp;
			return ;
		}
		all->listexport = all->listexport->next;
	}
	all->listexport = tmp;
	free(key);
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

void	ft_echo_env(t_all *all, char *arg)
{
	char		*key;
	int			i;
	t_listenv	*tmp;

	tmp = all->listenv;
	i = 0;
	key = ft_mallockey_env(arg, &i);
	ft_print_before_var(arg);
	if (!all->listenv)
		return ;
	while (all->listenv != NULL)
	{
		if (ft_strcmp(key, all->listenv->key) == 0)
		{
			if (all->listenv->content != NULL)
				printf("%s", all->listenv->content);
			all->listenv = tmp;
			return ;
		}
		all->listenv = all->listenv->next;
	}
	all->listenv = tmp;
	free(key);
}
