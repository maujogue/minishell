/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillpars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:04:36 by avaganay          #+#    #+#             */
/*   Updated: 2023/06/01 14:01:56 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_fillpars_heredoc(t_all *all, t_pars *pars, char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if ((i == 0 && cmd[i] == '<' && cmd[i + 1] == '<' && cmd[i + 2] != '<')
			|| (i != 0 && cmd[i - 1] != '<' && cmd[i] == '<'
				&& cmd[i + 1] == '<' && cmd[i + 2] != '<'))
		{
			if (pars->heredoc == NULL)
				pars->heredoc = ft_if_fillpars_heredoc_outfileappend(all, cmd,
						i);
			else
				pars->heredoc = ft_filetodouble(pars->heredoc,
						ft_fillnamefile(cmd, i + 1));
		}
		i++;
	}
}

void	ft_fillpars_outfile_append(t_all *all, t_pars *pars, char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if ((i == 0 && cmd[i] == '>' && cmd[i + 1] == '>' && cmd[i + 2] != '>')
			|| (i != 0 && cmd[i - 1] != '>' && cmd[i] == '>'
				&& cmd[i + 1] == '>' && cmd[i + 2] != '>'))
		{
			if (pars->outfile_append == NULL)
				pars->outfile_append = ft_if_fillpars_heredoc_outfileappend(all,
						cmd, i);
			else
				pars->outfile_append = ft_filetodouble(pars->outfile_append,
						ft_fillnamefile(cmd, i + 1));
		}
		i++;
	}
}

void	ft_fillpars_infile(t_all *all, t_pars *pars, char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if ((i == 0 && cmd[i] == '<' && cmd[i + 1] != '<') || (i != 0
				&& cmd[i - 1] != '<' && cmd[i] == '<' && cmd[i + 1] != '<'))
		{
			if (pars->infile == NULL)
				pars->infile = ft_if_fillpars_infile_outfile(all, cmd, i);
			else
				pars->infile = ft_filetodouble(pars->infile,
						ft_fillnamefile(cmd, i));
		}
		i++;
	}
}

void	ft_fillpars_outfile(t_all *all, t_pars *pars, char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if ((i == 0 && cmd[i] == '>' && cmd[i + 1] != '>') || (i != 0
				&& cmd[i - 1] != '>' && cmd[i] == '>' && cmd[i + 1] != '>'))
		{
			if (pars->outfile == NULL)
				pars->outfile = ft_if_fillpars_infile_outfile(all, cmd, i);
			else
				pars->outfile = ft_filetodouble(pars->outfile,
						ft_fillnamefile(cmd, i));
		}
		i++;
	}
}
