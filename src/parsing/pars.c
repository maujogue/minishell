/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:37:27 by avaganay          #+#    #+#             */
/*   Updated: 2023/06/09 11:16:22 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_init_pars_number(t_pars **pars, int number)
{
	pars[number]->infile = NULL;
	pars[number]->outfile = NULL;
	pars[number]->heredoc = NULL;
	pars[number]->outfile_append = NULL;
}

void	ft_fillparsfile(t_all *all, t_pars **pars, char *c, int number)
{
	int	i;

	i = 0;
	ft_init_pars_number(pars, number);
	while (c[i])
	{
		if (is(c, i) && ((i == 0 && c[i] == '<' && c[i + 1] != '<') || (i != 0
					&& c[i - 1] != '<' && c[i] == '<' && c[i + 1] != '<')))
			ft_fillpars_infile(all, pars[number], c);
		if (is(c, i) && ((i == 0 && c[i] == '>' && c[i + 1] != '>') || (i != 0
					&& c[i - 1] != '>' && c[i] == '>' && c[i + 1] != '<')))
			ft_fillpars_outfile(all, pars[number], c);
		if (is(c, i) && ((i == 0 && c[i] == '<' && c[i + 1] == '<'
					&& c[i + 2] != '<')
				|| (i != 0 && c[i - 1] != '<' && c[i] == '<'
					&& c[i + 1] == '<' && c[i + 2] != '<'))
			&& !pars[number]->heredoc)
			ft_fillpars_heredoc(all, pars[number], c);
		if (is(c, i) && ((i == 0 && c[i] == '>' && c[i + 1] == '>'
					&& c[i + 2] != '>')
				|| (i != 0 && c[i - 1] != '>' && c[i] == '>'
					&& c[i + 1] == '>' && c[i + 2] != '>')))
			ft_fillpars_outfile_append(all, pars[number], c);
		i++;
	}
}

int	ft_is_heredoc_last(char *cmd)
{
	int	i;

	i = ft_strlen(cmd);
	while (i != 0)
	{
		if (cmd[i] == '>')
			return (0);
		if (cmd[i] == '<')
		{
			if (cmd[i + 1] != '<' && cmd[i - 1] == '<' && cmd[i - 2] != '<')
				return (1);
			else
				return (0);
		}
		i--;
	}
	return (0);
}

int	ft_is_outfile_last(char *cmd)
{
	int	i;

	i = ft_strlen(cmd);
	while (i != 0)
	{
		if (cmd[i] == '<')
			return (0);
		if (cmd[i] == '>')
		{
			if (cmd[i + 1] != '>' && cmd[i - 1] != '>')
				return (1);
			else
				return (0);
		}
		i--;
	}
	return (0);
}

void	ft_fillstructpars(t_all *all, t_pars **pars, char **tabcmd)
{
	int	number;

	number = 0;
	while (tabcmd[number])
	{
		ft_initpars(pars[number]);
		ft_fillparsfile(all, pars, tabcmd[number], number);
		pars[number]->heredoc_last = ft_is_heredoc_last(tabcmd[number]);
		pars[number]->outfile_last = ft_is_outfile_last(tabcmd[number]);
		number++;
	}
}
