/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_cmds_to_pip.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:21:59 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/08 13:56:18 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_strlen_array(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] != NULL)
			i++;
	}
	return (i);
}

int	ft_strlen_triple_char(char ***str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] != NULL)
			i++;
	}
	return (i);
}

char	**ft_strdup_array(char **s1)
{
	char		**s2;
	int			i;

	i = 0;
	s2 = malloc(sizeof(char *) * (ft_strlen_array(s1) + 1));
	while (s1[i] != NULL)
	{
		s2[i] = ft_strdup(s1[i]);
		i++;
	}
	s2[i] = NULL;
	return (s2);
}

int	ft_strlen_parse(t_pars **parspipex)
{
	int	i;

	i = 0;
	if (parspipex)
	{
		while (parspipex[i] != NULL)
			i++;
	}
	return (i);
}

char	***get_pip_cmds(t_pars **parspipex)
{
	char	***tab_cmd;
	int		i;

	i = ft_strlen_parse(parspipex);
	tab_cmd = malloc(sizeof(char **) * (i + 1));
	i = -1;
	while (parspipex[++i])
		tab_cmd[i] = ft_strdup_array(parspipex[i]->tabfinal);
	tab_cmd[i] = NULL;
	return (tab_cmd);
}
