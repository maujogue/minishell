/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_dupes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:10:39 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/05 13:55:46 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	dup_infile(t_all *all, t_pip *pip)
{
	int	i;

	i = 0;
	if (pip->fd_infile[i] == -1)
	{
		write_error("bash: ", all->parspipex[pip->curr]->infile[pip->curr],
			" :No such file or directory\n");
		free_exit(all, pip, 1, "");
	}
	while (all->parspipex[pip->curr]->infile && pip->fd_infile[i] != -2)
	{
		if (dup2(pip->fd_infile[i], STDIN_FILENO) < 0)
			free_exit(all, pip, 1, "Error: Dup2 failed 1\n");
		i++;
	}
}

void	dup_outfile(t_all *all, t_pip *pip)
{
	int	i;

	i = 0;
	while (all->parspipex[pip->curr]->outfile && pip->fd_outfile[i] != -2)
	{
		if (dup2(pip->fd_outfile[i], STDOUT_FILENO) < 0)
			free_exit(all, pip, 1, "Error: Dup2 failed 1\n");
		i++;
	}
}

void	dup_outfile_append(t_all *all, t_pip *pip)
{
	int	i;

	i = 0;
	while (all->parspipex[pip->curr]->outfile_append
		&& pip->fd_outfile_append[i] != -2)
	{
		if (dup2(pip->fd_outfile_append[i], STDOUT_FILENO) < 0)
			free_exit(all, pip, 1, "Error: Dup2 failed 1\n");
		i++;
	}
}

void	dup_heredoc(t_all *all, t_pip *pip)
{
	if (all->parspipex[pip->curr]->heredoc
		&& dup2(pip->fd_heredoc, STDIN_FILENO) < 0)
		free_exit(all, pip, 1, "Error: Dup2 failed 1\n");
}

void	dup_pipe(t_all *all, t_pip *pip)
{
	if (all->parspipex[pip->curr]->heredoc_last == 1)
	{
		dup_infile(all, pip);
		dup_heredoc(all, pip);
	}
	else
	{
		dup_heredoc(all, pip);
		dup_infile(all, pip);
	}
	if (pip->curr != 0 && !(all->parspipex[pip->curr]->heredoc)
		&& dup2(pip->fds[(pip->curr * 2) - 2], STDIN_FILENO) < 0)
		free_exit(all, pip, 1, "Error: Dup2 failed 3\n");
	if (pip->curr < pip->nb_arg - 1 && dup2(pip->fds[pip->curr * 2 + 1], 1) < 0)
		free_exit(all, pip, 1, "Error: Dup2 failed 4\n");
	if (all->parspipex[pip->curr]->outfile_last == 1)
	{
		dup_outfile_append(all, pip);
		dup_outfile(all, pip);
	}
	else
	{
		dup_outfile(all, pip);
		dup_outfile_append(all, pip);
	}
}