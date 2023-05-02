/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:43:44 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/02 14:54:27 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	init_files(t_all *all, t_pip *pip)
{
	int	i;

	i = 0;
	if (all->infile2)
	{
		pip->fd_infile = malloc(sizeof(int *) * (ft_strlen_array(all->infile2) + 1));
		while (all->infile2[i])
		{
			pip->fd_infile[i] = open(all->infile2[i], O_RDONLY);
			i++;
		}
	}
	if (all->outfile && all->outfile_append == 1)
	{	
		pip->fd_outfile = open(all->outfile,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (pip->fd_outfile == -1)
		{
			perror("");
			free_exit(all, pip, 1, "");
		}
	}
	else if (all->outfile)
	{	
		pip->fd_outfile = open(all->outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pip->fd_outfile == -1)
		{
			perror("");
			free_exit(all, pip, 1, "");
		}
	}
}

void	init_cmd(t_all *all, t_pip *pip)
{
	pip->cmd = ft_strdup_array(pip->tab_cmd[pip->curr / 2]);
	if (!pip->cmd)
		free_exit(all, pip, 1, "Error\nMalloc failed");
}

void	create_pipes(t_all *all, t_pip *pip)
{
	int	i;

	i = 0;
	pip->fds = malloc(sizeof(int) * (pip->nb_arg * (2 + 1)));
	if (!pip->fds)
		free_exit(all, pip, 1, "Error\nMalloc failed");
	while (i < pip->nb_arg)
	{
		if (pipe(&pip->fds[i * 2]))
			free_exit(all, pip, 1, "Error\nPipe failed");
		i ++;
	}
}

void	init_pip(t_all *all, t_pip *pip)
{
	pip->curr = 0;
	pip->envp = NULL;
	pip->tab_cmd = NULL;
	pip->fds = NULL;
	pip->cmd = NULL;
	pip->path_cmd = NULL;
	join_cmds(all->parspipex);
	pip->envp = lst_to_tab(all->listenv);
	pip->path = get_path_envp(pip->envp);
	pip->tab_cmd = get_pip_cmds(all->parspipex);
	create_pipes(all, pip);
	// all->outfile_append = 1;
	// all->outfile = "out";
	// all->heredoc_delim[0] = "ok1";
	// all->heredoc_delim[1] = "ok2";
	all->infile_position = malloc(sizeof(int *) * (ft_strlen_array(all->infile2) + 1));
	all->infile_position[0] = -1;
	all->infile_position[1] = 1;
	all->infile_position[2] = -1;
	init_files(all, pip);
}

int	pipex(t_all *all)
{
	t_pip	pip;

	pip.nb_arg = ft_strlen_parse(all->parspipex);
	if (pip.nb_arg >= 1)
	{
		init_pip(all, &pip);
		here_doc(all, &pip);
		while (pip.curr / 2 < pip.nb_arg)
		{
			init_cmd(all, &pip);
			exec_cmd(all, &pip);
			pip.curr += 2;
		}
		close_p(&pip);
		wait_id(&pip);
		free_exit(all, &pip, 0, NULL);
	}
	return (0);
}
