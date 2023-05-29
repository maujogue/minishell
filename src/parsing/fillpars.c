/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillpars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:04:36 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/29 13:23:21 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	is_in(char *str, int i)
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
	if (single_quote_count % 2 == 1 && double_quote_count % 2 == 0)
		return (0);
	if (single_quote_count % 2 == 0 && double_quote_count % 2 == 1)
		return (0);
	return (1);
}

// void	ft_fillpars_heredoc(t_pars *pars, char *cmd)
// {
// 	int		i;
// 	char	*heredoc;
// 	char	**res;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if (cmd[i - 1] != '<' && cmd[i] == '<'
// 			&& cmd[i + 1] == '<' && cmd[i + 2] != '<')
// 		{
// 			if (pars->heredoc == NULL)
// 			{
// 				pars->heredoc = NULL;
// 				heredoc = ft_fillnamefile(cmd, i + 1);
// 				res = malloc(sizeof(char *) * 2);
// 				res[0] = heredoc;
// 				res[1] = NULL;
// 				pars->heredoc = res;
// 				free(heredoc);
// 				free_array(res);
// 			}
// 			else
// 			{
// 				res = ft_filetodouble(pars->heredoc,
// 						ft_fillnamefile(cmd, i + 1));
// 				pars->heredoc = res;
// 				free_array(res);
// 			}
// 		}
// 		i++;
// 	}
// }

void	ft_fillpars_heredoc(t_pars *pars, char *cmd)
{
	int		i;
	char	*heredoc;
	char	**res;

	i = 0;
	while (cmd[i])
	{
		if ((i == 0 && cmd[i] == '<' && cmd[i + 1] == '<' && cmd[i + 2] != '<')
			|| (i != 0 && cmd[i - 1] != '<' && cmd[i] == '<'
				&& cmd[i + 1] == '<' && cmd[i + 2] != '<'))
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
				pars->heredoc = ft_filetodouble(pars->heredoc,
						ft_fillnamefile(cmd, i + 1));
		}
		i++;
	}
}


// void	ft_fillpars_outfile_append(t_pars *pars, char *cmd)
// {
// 	int		i;
// 	char	*outfile_append;
// 	char	**res;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if ((i == 0 && cmd[i] == '>' && cmd[i + 1] == '>' && cmd[i + 2] != '>')
// 			|| (i != 0 && cmd[i - 1] != '>' && cmd[i] == '>'
// 				&& cmd[i + 1] == '>' && cmd[i + 2] != '>'))
// 		{
// 			if (pars->outfile_append == NULL)
// 			{
// 				pars->outfile_append = NULL;
// 				outfile_append = ft_fillnamefile(cmd, i + 1);
// 				res = malloc(sizeof(char *) * 2);
// 				res[0] = outfile_append;
// 				res[1] = NULL;
// 				pars->outfile_append = res;
// 				free(outfile_append);
// 				free_array(res);
// 				res = NULL;
// 			}
// 			else
// 			{
// 				res = ft_filetodouble(pars->outfile_append,
// 						ft_fillnamefile(cmd, i + 1));
// 				pars->outfile_append = res;
// 				free_array(res);
// 			}
// 		}
// 		if (cmd[i])
// 			i++;
// 	}
// }
void	ft_fillpars_outfile_append(t_pars *pars, char *cmd)
{
	int		i;
	char	*outfile_append;
	char	**res;

	i = 0;
	while (cmd[i])
	{
		if ((i == 0 && cmd[i] == '>' && cmd[i + 1] == '>' && cmd[i + 2] != '>')
			|| (i != 0 && cmd[i - 1] != '>' && cmd[i] == '>'
				&& cmd[i + 1] == '>' && cmd[i + 2] != '>'))
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
				pars->outfile_append = ft_filetodouble(pars->outfile_append,
						ft_fillnamefile(cmd, i + 1));
		}
		i++;
	}
}

// void	ft_fillpars_infile(t_pars *pars, char *cmd)
// {
// 	int		i;
// 	char	*infile;
// 	char	**res;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if ((i == 0 && cmd[i] == '<' && cmd[i + 1] != '<') || (i != 0
// 				&& cmd[i - 1] != '<' && cmd[i] == '<' && cmd[i + 1] != '<'))
// 		{
// 			if (pars->infile == NULL)
// 			{
// 				pars->infile = NULL;
// 				infile = ft_fillnamefile(cmd, i);
// 				res = malloc(sizeof(char *) * 2);
// 				res[0] = infile;
// 				res[1] = NULL;
// 				pars->infile = res;
// 				free(infile);
// 				free_array(res);
// 			}
// 			else
// 			{
// 				res = ft_filetodouble(pars->infile,
// 						ft_fillnamefile(cmd, i));
// 				pars->infile = res;
// 				free_array(res);
// 			}
// 		}
// 		i++;
// 	}
// }

void	ft_fillpars_infile(t_pars *pars, char *cmd)
{
	int		i;
	char	*infile;
	char	**res;

	i = 0;
	while (cmd[i])
	{
		if ((i == 0 && cmd[i] == '<' && cmd[i + 1] != '<') || (i != 0
				&& cmd[i - 1] != '<' && cmd[i] == '<' && cmd[i + 1] != '<'))
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

// void	ft_fillpars_outfile(t_pars *pars, char *cmd)
// {
// 	int		i;
// 	char	*outfile;
// 	char	**res;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if ((i == 0 && cmd[i] == '>' && cmd[i + 1] != '>') || (i != 0
// 				&& cmd[i - 1] != '>' && cmd[i] == '>' && cmd[i + 1] != '>'))
// 		{
// 			if (pars->outfile == NULL)
// 			{
// 				pars->outfile = NULL;
// 				outfile = ft_fillnamefile(cmd, i);
// 				res = malloc(sizeof(char *) * 2);
// 				res[0] = outfile;
// 				res[1] = NULL;
// 				pars->outfile = res;
// 				free(outfile);
// 				free_array(res);
// 			}
// 			else
// 			{
// 				res = ft_filetodouble(pars->outfile,
// 						ft_fillnamefile(cmd, i));
// 				pars->outfile = res;
// 				free_array(res);
// 			}
// 		}
// 		i++;
// 	}
// }
void	ft_fillpars_outfile(t_pars *pars, char *cmd)
{
	int		i;
	char	*outfile;
	char	**res;

	i = 0;
	while (cmd[i])
	{
		if ((i == 0 && cmd[i] == '>' && cmd[i + 1] != '>') || (i != 0
				&& cmd[i - 1] != '>' && cmd[i] == '>' && cmd[i + 1] != '>'))
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
