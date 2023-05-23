/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:05:28 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/23 16:14:01 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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

void	free_parse_tab(t_all *all)
{
	int	i;

	i = 0;
	if (!all->parspipex)
		return ;
	while (all->parspipex[i])
	{
		printf("\nOKKKKKKKKKKKKKKKKKKKK\n");
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

void	free_each_pipe(t_pip *pip)
{
	free_array(pip->cmd);
	free(pip->path_cmd);
	free(pip->fd_infile);
	free(pip->fd_outfile);
	free(pip->fd_outfile_append);
	pip->cmd = NULL;
	pip->path_cmd = NULL;
	pip->fd_infile = NULL;
	pip->fd_outfile = NULL;
	pip->fd_outfile_append = NULL;
}

void	free_pipex(t_all *all, t_pip *pip)
{
	free_array(pip->envp);
	free_triple_array(pip->tab_cmd);
	free(pip->path);
	free(pip->fds);
	free_parse_tab(all);
	(void)all;
	pip->envp = NULL;
	pip->tab_cmd = NULL;
	pip->path = NULL;
	pip->fds = NULL;
}

void	free_exit(t_all *all, t_pip *pip, int i, char *message)
{
	free_pipex(all, pip);
	free_each_pipe(pip);
	free_all(all);
	if (i != 0)
		exit(g_status);
	write(1, message, ft_strlen(message));
}
