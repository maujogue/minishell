/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsimplequote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:33:10 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/15 16:21:42 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*ft_fill_var_quote(char *cmd, int *i)
{
	char	*res;
	int		start;
	int		len;

	len = 0;
	start = *i;
	if (cmd[*i] == '\"')
	{
		*i += 1;
		len = 1;
		while (cmd[*i] != '\"' && cmd[*i])
		{
			len++;
			*i += 1;
		}
		res = ft_substr(cmd, start, len + 1);
		return (res);
	}
	else if (cmd[*i] == '\'')
	{
		*i += 1;
		len = 1;
		while (cmd[*i] != '\"' && cmd[*i])
		{
			len++;
			*i += 1;
		}
		res = ft_substr(cmd, start, len);
		return (res);
	}
	while (cmd[*i] != '\"' && cmd[*i] != '\'' && cmd[*i])
	{
		len++;
		*i += 1;
	}
	res = ft_substr(cmd, start, len);
	return (res);
}

char	*ft_cmd_whitout_simplequote(char *cmd)
{
	char	*res;
	char	*var;
	int		i;

	i = 0;
	while (cmd[i] && cmd[i] != '$' && ft_is_charspe(cmd[i]) == 0)
		i++;
	res = ft_substr(cmd, 0, i);
	while (cmd[i])
	{
		var = ft_fill_var_quote(cmd, &i);
		res = ft_strjoin(res, var);
		i++;
	}
	return (res);
}
