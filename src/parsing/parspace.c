/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parspace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:29:20 by avaganay          #+#    #+#             */
/*   Updated: 2023/06/09 11:12:03 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	is(char *str, int i)
{
	int	single_quote_count;
	int	double_quote_count;
	int	j;

	single_quote_count = 0;
	double_quote_count = 0;
	j = 0;
	while (j < i)
	{
		if (str[j] == '\'')
			single_quote_count++;
		else if (str[j] == '\"')
			double_quote_count++;
		j++;
	}
	if (single_quote_count % 2 == 1 && double_quote_count % 2 == 1)
		return (0);
	if (single_quote_count % 2 == 1 && double_quote_count % 2 == 0)
		return (0);
	if (single_quote_count % 2 == 0 && double_quote_count % 2 == 1)
		return (0);
	return (1);
}

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

void	ft_init_fill_caret_when_space(int *i, int *simplequoteopen,
	int *doublequoteopen)
{
	*i = 0;
	*simplequoteopen = 0;
	*doublequoteopen = 0;
}

char	*ft_fill_caret_when_space(t_all *all, char *cmd)
{
	size_t	len;
	char	*res;
	int		doublequoteopen;
	int		simplequoteopen;
	int		i;

	ft_init_fill_caret_when_space(&i, &simplequoteopen, &doublequoteopen);
	len = ft_strlen(cmd);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (free_all(all), exit(1), NULL);
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
