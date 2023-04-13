/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsopt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:45:27 by avaganay          #+#    #+#             */
/*   Updated: 2023/04/13 13:51:07 by avaganay         ###   ########.fr       */
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

char	*ft_fillparsopt(char *cmd)
{
	char	*res;
	int		i;
	int		len;
	int		start;

	i = ft_endcmd(cmd);
	len = 0;
    
	while (cmd[i])
	{
		if (cmd[i] == '-' && cmd[i - 1] == ' ')
		{
			start = i;
			while (cmd[i] != ' ')
			{
				i++;
				len++;
			}
			while (cmd[i] == ' ')
				i++;
			if (cmd[i] == '-')
			{
				len++;
				while (cmd[i] != ' ')
				{
					i++;
					len++;
				}
			}
			res = ft_substr(cmd, start, len);
			return (res);
		}
		i++;
	}
	return (NULL);
}