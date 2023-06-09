/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_dupes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:10:39 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/09 11:32:40 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	dup_infile(t_all *all, t_pip *pip)
{
	int	i;

	i = 0;
	while (all->parspipex[pip->curr]->infile && pip->fd_infile[i] != -2)
	{
		if (pip->fd_infile[i] == -1)
		{
			close_p(pip, pip->nb_arg);
			free_exit(all, pip, 1, NULL);
		}
		else if (dup2(pip->fd_infile[i], STDIN_FILENO) < 0)
			free_exit(all, pip, 1, "Error: Dup2 failed\n");
		i++;
	}
}

void	dup_outfile(t_all *all, t_pip *pip)
{
	int	i;

	i = 0;
	while (all->parspipex[pip->curr]->outfile && pip->fd_outfile[i] != -2)
	{
		if (pip->fd_outfile[i] == -1)
		{
			close_p(pip, pip->nb_arg);
			free_exit(all, pip, 1, NULL);
		}
		if (dup2(pip->fd_outfile[i], STDOUT_FILENO) < 0)
			free_exit(all, pip, 1, "Error: Dup2 failed\n");
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
		if (pip->fd_outfile_append[i] == -1)
		{
			close_p(pip, pip->nb_arg);
			free_exit(all, pip, 1, NULL);
		}
		if (dup2(pip->fd_outfile_append[i], STDOUT_FILENO) < 0)
			free_exit(all, pip, 1, "Error: Dup2 failed\n");
		i++;
	}
}

void	dup_heredoc(t_all *all, t_pip *pip)
{
	if (all->parspipex[pip->curr]->heredoc
		&& dup2(pip->fd_heredoc, STDIN_FILENO) < 0)
		free_exit(all, pip, 1, "Error: Dup2 failed\n");
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
		free_exit(all, pip, 1, "Error: Dup2 failed\n");
	if (pip->curr < pip->nb_arg - 1 && dup2(pip->fds[pip->curr * 2 + 1], 1) < 0)
		free_exit(all, pip, 1, "Error: Dup2 failed\n");
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
