/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsparsquote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:52:06 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/26 15:02:33 by avaganay         ###   ########.fr       */
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
