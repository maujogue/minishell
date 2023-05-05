/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmpbuil.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:26:42 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/05 14:38:55 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_strncmpecho(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (n == 0)
		return (n);
	while (s1[i] == '\'' || s1[i] == '\"')
	{
		n++;
		i++;
	}
	while ((s1[i] == s2[j]) && s1[i] && (i < n - 1) && s1[i] != ' ')
	{
		i++;
		j++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}

int	ft_strncmpexport(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (n == 0)
		return (n);
	while (s1[i] == '\'' || s1[i] == '\"')
	{
		n++;
		i++;
	}
	while ((s1[i] == s2[j]) && s1[i] && (i < n - 1) && s1[i] != ' ')
	{
		i++;
		j++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}

int	ft_strncmpunset(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (n == 0)
		return (n);
	while (s1[i] == '\'' || s1[i] == '\"')
	{
		n++;
		i++;
	}
	while ((s1[i] == s2[j]) && s1[i] && (i < n - 1) && s1[i] != ' ')
	{
		i++;
		j++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}
