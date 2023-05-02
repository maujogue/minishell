/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsheredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:24:03 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/02 15:03:22 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	**ft_tabheredocdelim(char **tab, char *delim)
{
	char	**res;
	int		size;

	size = 0;
	if (tab == NULL)
	{
		res = malloc(sizeof(char *) * 2);
		res[0] = delim;
		res[1] = NULL;	
		return (res);
	}
	while (tab[size] != NULL)
		size++;
	res = malloc(sizeof(char *) * (size + 2));
	size = 0;
	while (tab[size] != NULL)
	{
		res[size] = ft_strdup(tab[size]);
		size++;
	}
	res[size] = delim;
	res[size + 1] = "\0";
	return (res);
}

void ft_fillheredocdelim(t_all *all, char *cmd, int *i)
{
    char    *delim;
    int     len;
    int     start;

    len = 0;
    while (cmd[*i] == '<')
        *i += 1;
    while (cmd[*i] == ' ')
        *i += 1;
    if (cmd[*i] == '<')
    {
        printf("minishell: syntax error near unexpected token `<<'");
        return ;
    }
	start = *i;
    while (cmd[*i] != ' ' && cmd[*i] != '<' && cmd[*i] != '|' && cmd[*i])
    {
        *i += 1;
        len++;
    }
    delim = ft_substr(cmd, start, len);
	all->heredoc_delim = ft_tabheredocdelim(all->heredoc_delim, delim);
}

void    ft_fillheredoc(t_all *all, char *cmd)
{
    int	i;

    i = 0;
    while (cmd[i] && cmd[i + 1])
    {
		if (cmd[i - 1] != '<' && cmd[i] == '<' && cmd[i + 1] == '<' && cmd[i + 2] != '<')
		{
			ft_fillheredocdelim(all, cmd, &i);
		}
		if (cmd[i - 1] != '>' && cmd[i] == '>' && cmd[i + 1] == '>' && cmd[i + 2] != '>')
		{
			all->outfile_append = 1;
		}
		i++;
	}
}