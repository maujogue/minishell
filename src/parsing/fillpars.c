/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillpars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:04:36 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/08 14:33:25 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_fillpars_heredoc(t_pars *pars, char *cmd)
{
	int		i;
	char	*heredoc;
	char	**res;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i - 1] != '<' && cmd[i] == '<'
			&& cmd[i + 1] == '<' && cmd[i + 2] != '<')
		{
			if (pars->heredoc == NULL)
			{
				pars->heredoc = NULL;
				heredoc = ft_fillnamefile(cmd, i + 1);
				res = malloc(sizeof(char *) * 2);
				res[0] = heredoc;
				res[1] = NULL;
				pars->heredoc = res;
			}
			else
			{
				heredoc = ft_fillnamefile(cmd, i + 1);
				pars->heredoc = ft_filetodouble(pars->heredoc, heredoc);
			}
		}
		i++;
	}
}

void	ft_fillpars_outfile_append(t_pars *pars, char *cmd)
{
	int		i;
	char	*outfile_append;
	char	**res;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i - 1] != '>' && cmd[i] == '>'
			&& cmd[i + 1] == '>' && cmd[i + 2] != '>')
		{
			if (pars->outfile_append == NULL)
			{
				pars->outfile_append = NULL;
				outfile_append = ft_fillnamefile(cmd, i + 1);
				res = malloc(sizeof(char *) * 2);
				res[0] = outfile_append;
				res[1] = NULL;
				pars->outfile_append = res;
			}
			else
			{
				outfile_append = ft_fillnamefile(cmd, i + 1);
				pars->outfile_append
					= ft_filetodouble(pars->outfile_append, outfile_append);
			}
		}
		i++;
	}
}

void	ft_fillpars_infile(t_pars *pars, char *cmd)
{
	int		i;
	char	*infile;
	char	**res;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i - 1] != '<' && cmd[i] == '<' && cmd[i + 1] != '<')
		{
			if (pars->infile == NULL)
			{
				pars->infile = NULL;
				infile = ft_fillnamefile(cmd, i);
				res = malloc(sizeof(char *) * 2);
				res[0] = infile;
				res[1] = NULL;
				pars->infile = res;
			}
			else
				pars->infile = ft_filetodouble(pars->infile,
						ft_fillnamefile(cmd, i));
		}
		i++;
	}
}

void	ft_fillpars_outfile(t_pars *pars, char *cmd)
{
	int		i;
	char	*outfile;
	char	**res;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i - 1] != '>' && cmd[i] == '>' && cmd[i + 1] != '>')
		{
			if (pars->outfile == NULL)
			{
				pars->outfile = NULL;
				outfile = ft_fillnamefile(cmd, i);
				res = malloc(sizeof(char *) * 2);
				res[0] = outfile;
				res[1] = NULL;
				pars->outfile = res;
			}
			else
				pars->outfile = ft_filetodouble(pars->outfile,
						ft_fillnamefile(cmd, i));
		}
		i++;
	}
}
