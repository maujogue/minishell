/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parspace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:29:20 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/17 15:38:44 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*ft_fill_caret(t_all *all, char *cmd, int *i)
{
	char	*res;
	int		len;
	int		start;

	len = 0;
	*i += 1;
	start = *i;
	while (cmd[*i] != '\"' && cmd[*i])
	{
		len++;
		*i += 1;
	}
	*i = start;
	res = malloc(sizeof(char) * (len + 1));
	len = 0;
	while (cmd[*i] != '\"' && cmd[*i])
	{
		if (cmd[*i] == ' ')
			res[len] = '^';
			// res[len] = 127;
		else
			res[len] = cmd[*i];
		len++;
		*i += 1;
	}
	res[len] = '\0';
	all->pos_doublequote++;
	return (res);
}

// char	*ft_fill_caret_when_space(t_all *all, char *cmd)
// {
// 	char	*res;
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	tmp = NULL;
// 	while (cmd[i])
// 	{
// 		printf("%c\n", cmd[i]);
// 		if (cmd[i] == '\'')
// 			all->pos_simplequote++;
// 		if (cmd[i] == '\"')
// 		{
// 			all->pos_doublequote++;
// 			if (all->pos_doublequote % 2 != 0)
// 			{
// 				printf("RES: %s\n", res);
// 				tmp = ft_fill_caret(all, cmd, &i);
// 				printf("TMP: %s\n", tmp);
// 				res = ft_strjoin(res, tmp);
// 			}
// 		}
// 		i++;
// 	}
// 	if (tmp == NULL)
// 		return (cmd);
// 	return (res);
// }

char	*ft_fill_caret_when_space(char *cmd)
{
	size_t	len;
	char	*res;
	int		quoteopen;
	int		i;

	i = 0;
	quoteopen = 0;
	len = ft_strlen(cmd);
	res = (char *)malloc((len + 1) * sizeof(char));
	while (cmd[i])
	{
		if (cmd[i] == '"')
			quoteopen = !quoteopen;
		if (cmd[i] == ' ' && quoteopen)
			res[i] = '^';
		else
			res[i] = cmd[i];
		i++;
	}
	res[len] = '\0';
	return (res);
}

// char	*ft_fill_caret_when_space(t_all *all, char *cmd)
// {
// 	char	*res;
// 	char	*tmp;
// 	int		i;
// 	int		start;

// 	i = 0;
// 	tmp = NULL;
// 	while (cmd[i])
// 	{
// 		start = i;
// 		while (cmd[i] != '\"' && cmd[i])
// 		{
// 			if (cmd[i] == '\'')
// 				all->pos_simplequote++;
// 			i++;
// 		}
// 		all->pos_doublequote++;
// 		tmp = ft_substr(cmd, start, i - start);
// 		printf("TMP: %s\n", tmp);
// 		res = ft_strjoin(res, tmp);
// 		tmp = ft_fill_caret(all, cmd, &i);
// 		res = ft_strjoin(res, tmp);
// 	}
// 	if (tmp == NULL)
// 		return (cmd);
// 	return (res);
// }
