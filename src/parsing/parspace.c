/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parspace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:29:20 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/26 13:40:42 by avaganay         ###   ########.fr       */
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

char	*ft_fill_caret_when_space(char *cmd)
{
	size_t	len;
	char	*res;
	int		doublequoteopen;
	int		simplequoteopen;
	int		i;

	i = 0;
	simplequoteopen = 0;
	doublequoteopen = 0;
	len = ft_strlen(cmd);
	res = (char *)malloc((len + 1) * sizeof(char));
	while (cmd[i])
	{
		if (cmd[i] == '\'')
			simplequoteopen = !simplequoteopen;
		if (cmd[i] == '\"')
			doublequoteopen = !doublequoteopen;
		if (cmd[i] == ' ' && (doublequoteopen || simplequoteopen))
			res[i] = '^';
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
		if (src[i] == '^')
			dest[i] = ' ';
		else
			dest[i] = src[i];
		i++;
	}
	dest[len] = '\0';
	return (dest);
}
