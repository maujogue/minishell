/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:37:27 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/03 14:19:40 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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
		// if (cmd[i - 1] != '>' && cmd[i] == '>' && cmd[i + 1] != '>')
		// {
		// 	is_outfile = 1;
		// 	pars->outfile = ft_fillnamefile(cmd, i);
		// }
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
		if (pars[number]->infile == NULL)
			printf("infile: NULL\n");
		else
			printf("infile: %s\n", pars[number]->infile);
		printf("----------------\n");
		number++;
	}
}