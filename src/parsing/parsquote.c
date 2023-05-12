/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsquote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:24:04 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/12 14:12:31 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*ft_fill_piece_simplequote(char *cmd, int *i)
{
	char	*piece;
	int		len;
	int		start;

	len = 0;
	if (cmd[*i + 1] == '\0')
		return (NULL);
	*i += 1;
	start = *i;
	while (cmd[*i] != '\'')
	{
		len++;
		*i += 1;
	}
	piece = ft_substr(cmd, start, len);
	*i += 1;
	return (piece);
}

char	*ft_fill_cmdfinal_simplequote(char *cmd, int *i)
{
	char	*piece;

	if (cmd[*i] == '\'')
	{
		piece = ft_fill_piece_simplequote(cmd, i);
	}
	else
		piece = ft_substr(cmd, *i, 1);
	return (piece);
}

char	*ft_parsquote(char *cmd)
{
	char	*cmdfinal;
	int		i;
	char	*piece;

	i = 0;
	while (cmd[i] && cmd[i] != '\'' && cmd[i] != '\"')
		i++;
	cmdfinal = ft_substr(cmd, 0, i);
	while (cmd[i])
	{
		piece = ft_fill_cmdfinal_simplequote(cmd, &i);
		if (piece != NULL)
			cmdfinal = ft_strjoin(cmdfinal, piece);
		i++;
	}
	printf("Sans quote: %s\n\n\n", cmdfinal);
	return (cmdfinal);
}
