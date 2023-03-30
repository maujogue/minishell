/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:06 by maujogue          #+#    #+#             */
/*   Updated: 2023/03/30 16:53:12 by avaganay         ###   ########.fr       */
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

void	ft_printecho(t_all *all, char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '$' || (arg[0] == '"' && arg[1] == '$'))
	{
		ft_echo_var(all, arg);
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
		ft_printecho(all, tabecho[i]);
		if (tabecho[2] && tabecho[2][0] != '\0' && i != ft_nbargecho(tabecho) - 1)
			printf(" ");
		i++;
	}
	if (argn == 0)
		printf("\n");
	
}