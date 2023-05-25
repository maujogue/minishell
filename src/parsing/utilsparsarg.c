/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsparsarg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:39:38 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/24 16:17:06 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_isredir(char *cmd, int i)
{
	while (cmd[i])
	{
		if (cmd[i] == '<' || cmd[i] == '>')
			return (1);
		i++;
	}
	return (0);
}

void	ft_jump_redir(char *cmd, int *i)
{
	while (cmd[*i] != ' ' && cmd[*i])
		*i += 1;
	while (cmd[*i] == ' ')
		*i += 1;
	while (cmd[*i] != ' ' && cmd[*i])
		*i += 1;
}

int	ft_isopt(char *cmd, int i)
{
	if (cmd[i] == '\0')
		return (0);
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] == '-')
		return (1);
	return (0);
}

void	ft_jumpfile(char *cmd, int *i)
{
	while (cmd[*i] != ' ' && cmd[*i])
		*i += 1;
	while (cmd[*i] == ' ')
		*i += 1;
	while (cmd[*i] != ' ' && cmd[*i])
		*i += 1;
}
