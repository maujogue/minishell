/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:43:44 by maujogue          #+#    #+#             */
/*   Updated: 2023/04/12 13:22:43 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	init_files(t_all *all, t_pip *pip)
{
	if (all->infile)
	{
		pip->fd_infile = open(all->infile, O_RDONLY);
		if (pip->fd_infile == -1)
			perror(NULL);
	}
	if (all->outfile)
	{	
		pip->fd_outfile = open(all->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pip->fd_outfile == -1)
		{
			perror(NULL);
			free_exit(pip, 1, "");
		}
	}
}

void	init_cmd(t_pip *pip)
{
	pip->cmd1 = pip->tab_cmd[pip->curr / 2];
	if (!pip->cmd1)
		free_exit(pip, 1, "Error\nMalloc failed");
}

void	create_pipes(t_pip *pip)
{
	int	i;

	i = 0;
	pip->fds = malloc(sizeof(int) * (pip->nb_arg * 2));
	if (!pip->fds)
		free_exit(pip, 1, "Error\nMalloc failed");
	while (i < pip->nb_arg)
	{
		if (pipe(&pip->fds[i * 2]))
			free_exit(pip, 1, "Error\nPipe failed");
		i ++;
	}
}

void	init_pip(t_all *all, t_pip *pip)
{
	
	pip->curr = 0;
	pip->envp = NULL;
	pip->tab_cmd = NULL;
	pip->fds = NULL;
	pip->cmd1 = NULL;
	pip->path_cmd1 = NULL;
	pip->envp = lst_to_tab(all->listenv);
	pip->path = get_path_envp(pip->envp);
	pip->tab_cmd = struct_lst_to_tab(all->parspipex);
	create_pipes(pip);
	init_files(all, pip);
}

int	pipex(t_all *all)
{
	t_pip	pip;

	
	pip.nb_arg = ft_strlen_parse(all->parspipex);
	if (pip.nb_arg  >= 2)
	{
		init_pip(all, &pip);
		while (pip.curr / 2 < pip.nb_arg)
		{
			// ft_printf("%d|",pip->nb_arg);
			// if (!(pip->fd_infile == -1 && pip->curr != 0))
			free_array(pip.cmd1);
			free(pip.path_cmd1);
			init_cmd(&pip);
			exec_cmd(&pip);
			pip.curr += 2;
		}
		close_p(&pip);
		wait_id(&pip);
		free_exit(&pip, 0, NULL);
	}
	else if (pip.nb_arg < 2)
		write_error("Error: too much arguments (4 required)");
	return (0);
}
