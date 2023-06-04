/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathisaujogue <mathisaujogue@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:05:28 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/04 18:09:20 by mathisaujog      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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

void	free_pipex_files_tab(t_pip *pip)
{
	close_fd_tab(pip->fd_infile);
	close_fd_tab(pip->fd_outfile);
	close_fd_tab(pip->fd_outfile_append);
	if (pip->fd_heredoc != -2)
		close(pip->fd_heredoc);
	free(pip->fd_infile);
	free(pip->fd_outfile);
	free(pip->fd_outfile_append);
	pip->fd_infile = NULL;
	pip->fd_outfile = NULL;
	pip->fd_outfile_append = NULL;
}

void	free_each_pipe(t_pip *pip)
{
	free_array(pip->cmd);
	free(pip->path_cmd);
	pip->cmd = NULL;
	pip->path_cmd = NULL;
	free_pipex_files_tab(pip);
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

void	free_exit(t_all *all, t_pip *pip, int in_pipex_cmd, char *message)
{
	if (in_pipex_cmd == 1)
		free_each_pipe(pip);
	if (pip)
		free_pipex(all, pip);
	free_all(all);
	ft_putstr_fd(message, 2);
	exit(g_status);
}
