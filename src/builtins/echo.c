/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:06 by maujogue          #+#    #+#             */
/*   Updated: 2023/04/04 14:35:49 by avaganay         ###   ########.fr       */
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


void	ft_echo_var(t_all *all, char *arg)
{
	char *key;
	int	i;
	t_listenv *tmp;

	tmp = all->listexport;
	i = 0;
	if (arg[0] == '\"' || arg[1] == '\"')
	{
		i = 2;
		key = malloc(sizeof(char) * (ft_strlen(arg) - 3));
		while (arg[i + 1])
		{
			key[i - 2] = arg[i];
			i++;
		}	
	}
	else
	{
		i = 1;
		key = malloc(sizeof(char) * (ft_strlen(arg) - 1));
		while (arg[i])
		{
			key[i - 1] = arg[i];
			i++;
		}
		key[i - 1] = '\0';
	}
	if (!all->listexport)
		return ;
	while (all->listexport != NULL)
	{
		// printf("%s\n", key);
		if (ft_strcmp(key, all->listexport->key) == 0)
		{
			// printf("ICICICICI");
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
	if (arg[0] != '$' && ((arg[0] >= 33 && arg[0] <= 46) || arg[0] == 91 || arg[0] == 93))
		printf("%c", arg[0]);
}

void	ft_echo_env(t_all *all, char *arg)
{
	char *key;
	int	i;
	t_listenv *tmp;

	tmp = all->listenv;
	i = 0;
	if (arg[0] == '\"' || arg[1] == '\"' || (arg[0] >= 91 && arg[0] <= 93) || (arg[0] >= 33 && arg[0] <= 46 && arg[0] != 36))
	{
		i = 2;
		key = malloc(sizeof(char) * (ft_strlen(arg) - 3));
		while (arg[i])
		{
			key[i - 2] = arg[i];
			i++;
		}	
	}
	else
	{
		i = 1;
		key = malloc(sizeof(char) * (ft_strlen(arg) - 1));
		while (arg[i])
		{
			key[i - 1] = arg[i];
			i++;
		}
		key[i - 1] = '\0';
	}
	ft_print_before_var(arg);
	if (!all->listenv)
		return ;
	while (all->listenv != NULL)
	{
		// printf("%s\n", key);
		if (ft_strcmp(key, all->listenv->key) == 0)
		{
			// printf("ICICICICI");
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
