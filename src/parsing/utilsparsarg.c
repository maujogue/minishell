/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsparsarg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:39:38 by avaganay          #+#    #+#             */
/*   Updated: 2023/06/05 16:03:35 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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
