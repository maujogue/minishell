/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsarg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:27:22 by avaganay          #+#    #+#             */
/*   Updated: 2023/04/14 14:50:28 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_isopt(char *cmd, int i)
{
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] == '-')
		return (1);
	return (0);
}

int	ft_endcmdopt(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] == ' ' && cmd[i])
		i++;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	while (ft_isopt(cmd, i))
	{
		while (cmd[i] == ' ')
			i++;
		while (cmd[i] != ' ' && cmd[i])
			i++;
		while (cmd[i] == ' ')
			i++;
	}
	return (i);
}

int	ft_nbargcmd(char *cmd, int i)
{
	int	nb;

	nb = 0;
	while (cmd[i])
	{
		while (cmd[i] == ' ')
			i++;
		if (cmd[i] != '\0' && cmd[i] != ' ')
			nb++;
		while (cmd[i] != ' ' && cmd[i])
			i++;
	}
	return (nb);
}

char	*ft_fillarg(char *cmd, int *i)
{
	char	*res;
	int		start;
	int		isarg;

	isarg = 0;
	while (cmd[*i] == ' ')
		*i += 1;
	start = *i;
	while (cmd[*i] != ' ' && cmd[*i])
	{
		isarg = 1;
		*i += 1;
	}
	if (isarg == 0)
		return (NULL);
	res = ft_substr(cmd, start, *i - start);
	return (res);
}

char	**ft_fillparsarg(char *cmd)
{
	char	**tab;
	int		i;
	int		nb;
	int		count;

	count = 0;
	i = ft_endcmdopt(cmd);
	nb = ft_nbargcmd(cmd, i);
	tab = malloc(sizeof(char *) * (nb + 1));
	if (nb == 0)
		return (NULL);
	while (cmd[i] && count < nb)
	{
		tab[count] = ft_fillarg(cmd, &i);
		count++;
		i++;
	}
	tab[count] = NULL;
	return (tab);
}
