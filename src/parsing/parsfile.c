/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:38:59 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/31 11:13:54 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_charspe(char c)
{
	if (c >= 33 && c <= 47)
		return (1);
	if (c >= 58 && c <= 64)
		return (1);
	if (c >= 91 && c <= 94)
		return (1);
	if (c >= 123 && c <= 125)
		return (1);
	return (0);
}

char	*ft_fillnamefile(char *cmd, int i)
{
	char	*infile;
	int		start;
	int		len;

	len = 0;
	i++;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	start = i;
	while (cmd[i] && cmd[i] != ' ')
	{
		i++;
		len++;
	}
	infile = ft_substr(cmd, start, len);
	return (infile);
}

int	ft_lentab(char **tab)
{
	int	len;

	len = 0;
	while (tab[len])
	{
		len++;
	}
	return (len);
}

char	**ft_filetodouble(char **tab, char *file)
{
	char	**res;
	int		len;
	int		i;

	i = 0;
	len = ft_lentab(tab);
	res = malloc(sizeof(char *) * (len + 2));
	if (!res)
		return (free_array(tab), exit(1), NULL);
	while (tab[i] != NULL)
	{
		res[i] = ft_strdup(tab[i]);
		i++;
	}
	res[i] = ft_strdup(file);
	if (!res)
		exit(1);
	res[i + 1] = NULL;
	free(file);
	free_array(tab);
	return (res);
}

int	ft__sizeinfile_position(char *cmd, char c)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (cmd[i])
	{
		while (cmd[i] != '|' && cmd[i])
		{
			if (cmd[i] == c)
			{
				size++;
				break ;
			}
			i++;
		}
		i++;
	}
	return (size);
}
