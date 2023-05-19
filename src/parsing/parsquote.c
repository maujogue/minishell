/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsquote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:24:04 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/18 14:26:39 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_countquote(char *cmd, char quote)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == quote)
			res++;
		i++;
	}
	return (res);
}

char	*ft_wherequote(t_all *all, char *cmd, int *i)
{
	char	*var;
	int		start;
	int		len;

	len = 1;
	// printf("%d\n", all->pos_simplequote);
	// printf("%d\n", all->pos_doublequote);
	if (all->pos_simplequote % 2 != 0 && all->pos_doublequote % 2 == 0)
	{
		start = *i;
		while (cmd[*i] != '\'' && cmd[*i])
		{
			len++;
			*i += 1;
		}
		// printf("START: %d\n", start);
		// printf("LEN: %d\n", len);
		var = ft_substr(cmd, start, len - 1);
		// printf("VAR: %s\n", var);
		return (var);
	}
	if (all->pos_simplequote % 2 != 0 && all->pos_doublequote % 2 != 0)
	{
		if (ft_doublequote_start(cmd, *i))
		{
			while (cmd[*i] != '\'' && *i >= 0)
				*i -= 1;
			start = *i + 1;
			*i += 1;
			while (cmd[*i] != '\'' && cmd[*i])
			{
				len++;
				*i += 1;
			}
			var = ft_substr(cmd, start, len - 1);
			printf("VAR: %s\n", var);
			return (var);
		}
		// else
		// {
		// 	while (cmd[*i] != '\"' && *i >= 0)
		// 		*i -= 1;
		// 	start = *i + 1;
		// 	*i += 1;
		// 	while (cmd[*i] != '\"' && cmd[*i])
		// 	{
		// 		len++;
		// 		*i += 1;
		// 	}
		// 	var = ft_substr(cmd, start, len - 1);
		// 	printf("VAR: %s\n", var);
		// 	return (var);
		// }
	}
	return (NULL);
}

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
		piece = ft_fill_piece_simplequote(cmd, i);
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
