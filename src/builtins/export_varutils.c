/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_varutils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:41:25 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/15 16:07:45 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_export_fillkeycontentvar(t_listenv *new, char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
		{
			new->key = ft_substrexportkey(var, 0, i);
			new->content = ft_substrexportcontent(var, i + 1, ft_strlen(var));
			return ;
		}
		if (var[i + 1] == '\0')
		{
			new->key = ft_substrexportkey(var, 0, i + 1);
			new->content = NULL;
			return ;
		}
		i++;
	}
}

int	ft_check_name_var(char *var)
{
	int	i;
	int	len;

	len = ft_strlen(var);
	i = 0;
	if (var[0] >= '0' && var[0] <= '9')
		return (g_status = 1, write_error("minishell: export: ", var
				, ": not a valid identifier\n"), 1);
	while (var[i] && var[i] != '=' && i <= len)
	{
		if (var[i] >= 33 && var[i] <= 47 && var[i] != 34 && var[i] != 39)
			return (g_status = 1, write_error("minishell: export: ", var
					, ": not a valid identifier\n"), 1);
		i++;
	}
	return (0);
}

char	*ft_fillkeyvar(char	*var)
{
	int		i;
	char	*res;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
		{
			res = ft_substr(var, 0, i);
			return (res);
		}
		i++;
	}
	return (var);
}

int	ft_check_double_var(char *var, t_listenv *listexport, t_all **all)
{
	t_listenv	*tmp;
	char		*keyvar;

	tmp = listexport;
	keyvar = ft_fillkeyvar(var);
	while (listexport)
	{
		if (ft_strcmp(keyvar, listexport->key) == 0)
			return (1);
		listexport = listexport->next;
	}
	listexport = tmp;
	tmp = (*all)->listenv;
	while ((*all)->listenv)
	{
		if (ft_strcmp(keyvar, (*all)->listenv->key) == 0)
			return (1);
		(*all)->listenv = (*all)->listenv->next;
	}
	(*all)->listenv = tmp;
	return (0);
}

void	ft_replace_double(char *var, t_listenv *listexport, t_all **all)
{
	t_listenv	*tmp;
	int			i;

	(void)all;
	i = 0;
	tmp = listexport;
	while (listexport)
	{
		if (ft_strncmp(var, listexport->key, ft_strlen(listexport->key)) == 0)
		{
			while (var[i] != '=' && var[i])
				i++;
			if (var[i])
			{
				printf("REPLACE NO =\n");
				listexport->content
					= ft_substrexportcontent(var, i + 1, ft_strlen(var));
				listexport = tmp;
			}
			return ;
		}
		listexport = listexport->next;
	}
	listexport = tmp;
}
