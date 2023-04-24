/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:38:59 by avaganay          #+#    #+#             */
/*   Updated: 2023/04/24 10:21:16 by avaganay         ###   ########.fr       */
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
	if (cmd[i] == '\0' || ft_charspe(cmd[i]))
	{
		printf("minishell: syntax error near unexpected token '%c'\n", cmd[i]);
		return (NULL);
	}
	start = i;
	while (cmd[i] && cmd[i] != ' ')
	{
		i++;
		len++;
	}
	infile = ft_substr(cmd, start, len);
	return (infile);
}

void	ft_fillfile(t_all *all, char *cmd)
{
	int	i;
	int	is_infile;
	int	is_outfile;

	i = 0;
	is_infile = 0;
	is_outfile = 0;
	while (cmd[i])
	{
		if (cmd[i] == '<')
		{
			is_infile = 1;
			all->infile = ft_fillnamefile(cmd, i);
		}
		if (cmd[i] == '>')
		{
			is_outfile = 1;
			all->outfile = ft_fillnamefile(cmd, i);
		}
		i++;
	}
	if (is_infile == 0)
		all->infile = NULL;
	if (is_outfile == 0)
		all->outfile = NULL;
	if (all->infile == NULL)
		printf("infile: NULL\n");
	else
		printf("infile: %s\n", all->infile);
	if (all->outfile == NULL)
		printf("outfile: NULL\n");
	else
		printf("outfile: %s\n", all->outfile);
}
