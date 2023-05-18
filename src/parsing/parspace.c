/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parspace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:29:20 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/18 13:19:51 by avaganay         ###   ########.fr       */
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
			res[i] = 127;
		else
			res[i] = cmd[i];
		i++;
	}
	res[len] = '\0';
	return (res);
}

char	*ft_replace_caret(char *src)
{
	size_t	len;
	char	*dest;
	size_t	i;

	i = 0;
	len = ft_strlen(src);
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (dest == NULL)
	{
		fprintf(stderr, "Error malloc.\n");
		return (NULL);
	}
	while (src[i])
	{
		if (src[i] == 127)
			dest[i] = ' ';
		else
			dest[i] = src[i];
		i++;
	}
	dest[len] = '\0';
	return (dest);
}
