/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:05:28 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/25 16:05:11 by maujogue         ###   ########.fr       */
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

void	close_fd_tab(int *tab)
{
	int	i;

	i = 0;
	while (tab[i] != -2 && tab[i] != -1)
	{
		close(tab[i]);
		i++;
	}
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

void	free_each_pipe(t_pip *pip)
{
	free_array(pip->cmd);
	free(pip->path_cmd);
	close_fd_tab(pip->fd_infile);
	close_fd_tab(pip->fd_outfile);
	close_fd_tab(pip->fd_outfile_append);
	if (pip->fd_heredoc != -2)
		close(pip->fd_heredoc);
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
