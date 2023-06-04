/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathisaujogue <mathisaujogue@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:19:50 by avaganay          #+#    #+#             */
/*   Updated: 2023/06/04 18:09:39 by mathisaujog      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	free_files(t_all *all, int i)
{
	free_array(all->parspipex[i]->infile);
	free_array(all->parspipex[i]->outfile);
	free_array(all->parspipex[i]->outfile_append);
	free_array(all->parspipex[i]->heredoc);
	all->parspipex[i]->infile = NULL;
	all->parspipex[i]->outfile = NULL;
	all->parspipex[i]->outfile_append = NULL;
	all->parspipex[i]->heredoc = NULL;
}

void	free_parse(t_pars *parspipex)
{
	if (!parspipex)
		return ;
	free_array(parspipex->tabfinal);
	free_array(parspipex->arg);
	free_array(parspipex->opt2);
	free(parspipex->cmd);
	parspipex->tabfinal = NULL;
	parspipex->arg = NULL;
	parspipex->opt2 = NULL;
	parspipex->cmd = NULL;
	free(parspipex);
	parspipex = NULL;
}

void	free_parse_tab(t_all *all)
{
	int	i;

	i = 0;
	if (!all->parspipex)
		return ;
	while (all->parspipex[i])
	{
		free_array(all->parspipex[i]->tabfinal);
		free_array(all->parspipex[i]->arg);
		free_array(all->parspipex[i]->opt2);
		free(all->parspipex[i]->cmd);
		free_files(all, i);
		all->parspipex[i]->tabfinal = NULL;
		all->parspipex[i]->arg = NULL;
		all->parspipex[i]->opt2 = NULL;
		all->parspipex[i]->cmd = NULL;
		free(all->parspipex[i]);
		all->parspipex[i] = NULL;
		i++;
	}
	free(all->parspipex);
	all->parspipex = NULL;
}

void	free_all(t_all *all)
{
	free_listenv(all->listenv);
	free_listenv(all->listexport);
	free_parse_tab(all);
	all->listenv = NULL;
	all->listexport = NULL;
}
