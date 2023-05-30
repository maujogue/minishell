/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsopt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:45:27 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/30 11:18:32 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_init_fillparscmd(char *cmd, int *len, int *nospace, int *is_cmd)
{
	*len = 0;
	*nospace = 0;
	*is_cmd = 0;
	while (cmd[*len] == ' ')
	{
		*len += 1;
		*nospace += 1;
	}
}

int	ft_endcmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] == ' ' && cmd[i])
		i++;
	if (cmd[i] == '<' || cmd[i] == '>')
	{
		while (cmd[i] == '<' || cmd[i] == '>')
			i++;
		while (cmd[i] == ' ')
			i++;
		while (cmd[i] && cmd[i] != ' ')
			i++;
		while (cmd[i] == ' ')
			i++;
	}
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

char	**ft_fillparsopt2(char *cmd)
{
	char	*res;
	char	**split;
	int		i;

	i = ft_endcmd(cmd);
	while (cmd[i] == ' ' && cmd[i])
		i++;
	if (cmd[i] == '\0')
		return (NULL);
	if (!(cmd[i] != '-' && cmd[i] != '\0'))
	{
		res = ft_fillopt(cmd, i);
		split = ft_split(res, ' ');
		free(res);
		return (split);
	}
	return (NULL);
}
