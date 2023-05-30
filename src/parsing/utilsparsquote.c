/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsparsquote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:52:06 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/30 10:57:21 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_simplequote_start(char *cmd, int i)
{
	while (i >= 0)
	{
		if (cmd[i] == '\'')
			return (1);
		if (cmd[i] == '\"')
			return (0);
		i--;
	}
	return (0);
}

int	ft_doublequote_start(char *cmd, int i)
{
	while (i >= 0)
	{
		if (cmd[i] == '\"')
			return (1);
		if (cmd[i] == '\'')
			return (0);
		i--;
	}
	return (0);
}

char	*ft_double_quote_in_simple(char *cmd, int *i)
{
	char	*res_in_simple_quote;
	int		len;
	int		start;

	len = 0;
	*i += 1;
	start = *i;
	while (cmd[*i] != '\'' && cmd[*i])
	{
		*i += 1;
		len++;
	}
	res_in_simple_quote = ft_substr(cmd, start, len);
	return (res_in_simple_quote);
}

char	*ft_end_simple_quote_in_double(char *cmd, int *i, int len, int start)
{
	char	*res;

	while (cmd[*i] != '\"' && cmd[*i])
	{
		*i += 1;
		len++;
	}
	res = ft_substr(cmd, start, len);
	return (res);
}

char	*ft_simple_quote_in_double(char *cmd, int *i)
{
	char	*res;
	int		j;
	int		len;
	int		start;

	len = 0;
	*i += 1;
	j = *i;
	start = *i;
	if (cmd[*i] == '$' && cmd[*i + 1] == '\"')
		return (*i += 2, ft_substr(cmd, start, 1));
	while (cmd[j])
	{
		if (cmd[j] == '\'')
			break ;
		if (cmd[j] == '"' || cmd[j + 1] == '\0')
		{
			*i = start - 1;
			return (NULL);
		}
		j++;
	}
	res = ft_end_simple_quote_in_double(cmd, i, len, start);
	return (res);
}
