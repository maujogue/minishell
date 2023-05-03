/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:37:27 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/03 15:02:17 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_fillparsoutfile(t_pars *pars, char *cmd)
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

	i = 0;
	is_infile = 0;
	is_outfile = 0;
	while (cmd[i])
	{
		if (cmd[i - 1] != '<' && cmd[i] == '<' && cmd[i + 1] != '<')
		{
			is_infile = 1;
			pars[number]->infile = ft_fillnamefile(cmd, i);
		}
		if (cmd[i - 1] != '>' && cmd[i] == '>' && cmd[i + 1] != '>')
		{
			is_outfile = 1;
			ft_fillparsoutfile(pars[number], cmd);
		}
		i++;
	}
	if (is_infile == 0)
		pars[number]->infile = NULL;
	if (is_outfile == 0)
		pars[number]->outfile = NULL;
}

void	ft_fillstructpars(t_pars **pars, char **tabcmd)
{
	int	number;

	number = 0;
	while (tabcmd[number])
	{
		ft_fillparsfile(pars, tabcmd[number], number);
		//////////////////////////////////////////////////////////////
		if (pars[number]->infile == NULL)
			printf("infile: NULL\n");
		else
			printf("infile: %s\n", pars[number]->infile);
		if (pars[number]->outfile  == NULL)
			printf("outfile: NULL\n");
		else
		{
			int i;

    		i = 0;
			printf("outfile:\n");
			while (pars[number]->outfile[i] != NULL)
			{
				printf("%s\n",pars[number]->outfile[i]);
				i++;
			}
		}
		printf("----------------\n");
		///////////////////////////////////////////////////////////
		number++;
	}
}