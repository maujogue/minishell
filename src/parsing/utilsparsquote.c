/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsparsquote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:52:06 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/18 14:27:21 by avaganay         ###   ########.fr       */
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
