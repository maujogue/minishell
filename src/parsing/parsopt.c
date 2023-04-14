/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsopt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:45:27 by avaganay          #+#    #+#             */
/*   Updated: 2023/04/14 14:53:48 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_endcmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] == ' ' && cmd[i])
		i++;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	return (i);
}

char	*ft_fillopt(char *cmd, int i)
{
	int		start;
	int		len;
	char	*res;

	start = i;
	len = 1;
	while (ft_isopt(cmd, i))
	{
		while (cmd[i] == ' ')
		{
			i++;
			len++;
		}
		while (cmd[i] != ' ' && cmd[i])
		{
			i++;
			len++;
		}
	}
	res = ft_substr(cmd, start, len);
	return (res);
}

char	*ft_fillparsopt(char *cmd)
{
	char	*res;
	int		i;

	i = ft_endcmd(cmd);
	while (cmd[i] == ' ' && cmd[i])
		i++;
	if (cmd[i] == '\0')
		return (NULL);
	if (!(cmd[i] != '-' && cmd[i] != '\0'))
	{
		res = ft_fillopt(cmd, i);
		return (res);
	}
	return (NULL);
}
