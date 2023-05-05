/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:37:27 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/05 15:23:17 by avaganay         ###   ########.fr       */
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
		if (cmd[i - 1] != '<' && cmd[i] == '<' && cmd[i + 1] == '<' && cmd[i + 2] != '<')
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
		if (cmd[i - 1] != '>' && cmd[i] == '>' && cmd[i + 1] == '>' && cmd[i + 2] != '>')
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
				pars->outfile_append = ft_filetodouble(pars->outfile_append, outfile_append);
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
			{
				infile = ft_fillnamefile(cmd, i);
				pars->infile = ft_filetodouble(pars->infile, infile);
			}
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
			{
				outfile = ft_fillnamefile(cmd, i);
				pars->outfile = ft_filetodouble(pars->outfile, outfile);
			}
		}
		i++;
	}
}

void	ft_fillparsfile(t_pars **pars, char *cmd, int number)
{
	int	i;
	int	is_infile;
	int	is_outfile;
	int	is_heredoc;
	int	is_outfile_append;

	i = 0;
	is_infile = 0;
	is_outfile = 0;
	is_heredoc = 0;
	is_outfile_append = 0;
	while (cmd[i])
	{
		if (cmd[i - 1] != '<' && cmd[i] == '<' && cmd[i + 1] != '<')
		{
			if (is_infile == 0)
				ft_fillpars_infile(pars[number], cmd);
			is_infile = 1;
		}
		if (cmd[i - 1] != '>' && cmd[i] == '>' && cmd[i + 1] != '>')
		{
			if (is_outfile == 0)
				ft_fillpars_outfile(pars[number], cmd);
			is_outfile = 1;
		}
		if (cmd[i - 1] != '<' && cmd[i] == '<' && cmd[i + 1] == '<' && cmd[i + 2] != '<')
		{
			if (is_heredoc == 0)
				ft_fillpars_heredoc(pars[number], cmd);
			is_heredoc = 1;
		}
		if (cmd[i - 1] != '>' && cmd[i] == '>' && cmd[i + 1] == '>' && cmd[i + 2] != '>')
		{
			if (is_outfile_append == 0)
				ft_fillpars_outfile_append(pars[number], cmd);
			is_outfile_append = 1;
		}
		i++;
	}
	if (is_infile == 0)
		pars[number]->infile = NULL;
	if (is_outfile == 0)
		pars[number]->outfile = NULL;
	if (is_heredoc == 0)
		pars[number]->heredoc = NULL;
	if (is_outfile_append == 0)
		pars[number]->outfile_append = NULL;
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

void	ft_initpars(t_pars *pars)
{
	pars->infile = NULL;
	pars->outfile = NULL;
	pars->heredoc = NULL;
	pars->outfile_append = NULL;
	pars->heredoc_last = 0;
	pars->outfile_last = 0;
}

void	ft_fillstructpars(t_pars **pars, char **tabcmd)
{
	int	number;
	int	i;

	number = 0;
	while (tabcmd[number])
	{
		ft_initpars(pars[number]);
		ft_fillparsfile(pars, tabcmd[number], number);
		pars[number]->heredoc_last = ft_is_heredoc_last(tabcmd[number]);
		pars[number]->outfile_last = ft_is_outfile_last(tabcmd[number]);
		//////////////////////////////////////////////////////////////
		if (pars[number]->infile  == NULL)
			printf("infile: NULL\n");
		else
		{
    		i = 0;
			printf("infile:\n");
			while (pars[number]->infile[i] != NULL)
			{
				printf("%s\n",pars[number]->infile[i]);
				i++;
			}
		}
		if (pars[number]->outfile  == NULL)
			printf("outfile: NULL\n");
		else
		{
    		i = 0;
			printf("outfile:\n");
			while (pars[number]->outfile[i] != NULL)
			{
				printf("%s\n",pars[number]->outfile[i]);
				i++;
			}
		}
		if (pars[number]->heredoc  == NULL)
			printf("heredoc: NULL\n");
		else
		{
    		i = 0;
			printf("heredoc:\n");
			while (pars[number]->heredoc[i] != NULL)
			{
				printf("%s\n",pars[number]->heredoc[i]);
				i++;
			}
		}
		if (pars[number]->outfile_append  == NULL)
			printf("outfile_append: NULL\n");
		else
		{
    		i = 0;
			printf("outfile_append:\n");
			while (pars[number]->outfile_append[i] != NULL)
			{
				printf("%s\n",pars[number]->outfile_append[i]);
				i++;
			}
		}
		printf("heredoc_last: %d\n", pars[number]->heredoc_last);
		printf("outfile_last: %d\n", pars[number]->outfile_last);
		printf("----------------\n");
		///////////////////////////////////////////////////////////
		number++;
	}
}