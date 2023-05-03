/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:43:44 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/03 17:09:50 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

// int	init_file_tab(int	**fds, char ***file_tab, char file_type)
// {
// 	int	i;

// 	i = 0;
// 	if (file_tab)
// 	{
// 		*fds = malloc(sizeof(int) * (ft_strlen_array(*file_tab) + 1));
// 		while (file_tab[i])
// 		{
// 			if (file_type == 'i')
// 				*fds[i] = open(*file_tab[i], 	O_WRONLY, 0644);
// 			else if (file_type == 'o')
// 				*fds[i] = open(*file_tab[i], 	O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			else if (file_type == 'a')
// 				*fds[i] = open(*file_tab[i], 	O_WRONLY | O_CREAT | O_APPEND, 0644);
// 			if (*fds[i] == -1)
// 				return (1);
// 			printf("-->%d\n", *fds[i]);
// 			i++;
// 		}
// 		*fds[i] = 2;
// 	}
// 	return (0);
// }

int	init_infile_tab(t_all *all, t_pip *pip)
{
	int	i;

	i = 0;
	if (all->parspipex[pip->curr]->infile)
	{
		pip->fd_infile = malloc(sizeof(int) * (ft_strlen_array(all->parspipex[pip->curr]->infile) + 1));
		while (all->parspipex[pip->curr]->infile[i])
		{
			pip->fd_infile[i] = open(all->parspipex[pip->curr]->infile[i], 	O_WRONLY, 0644);
			if (pip->fd_infile[i] == -1)
				return (1);
			i++;
		}
		pip->fd_infile[i] = -2;
	}
	return (0);
}

int	init_outfile_tab(t_all *all, t_pip *pip)
{
	int	i;

	i = 0;
	if (all->parspipex[pip->curr]->outfile)
	{
		pip->fd_outfile = malloc(sizeof(int) * (ft_strlen_array(all->parspipex[pip->curr]->outfile) + 1));
		while (all->parspipex[pip->curr]->outfile[i])
		{
			pip->fd_outfile[i] = open(all->parspipex[pip->curr]->outfile[i], 	O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (pip->fd_outfile[i] == -1)
				return (1);
			i++;
		}
		pip->fd_outfile[i] = -2;
	}
	return (0);
}

int	init_outfile_append_tab(t_all *all, t_pip *pip)
{
	int	i;

	i = 0;
	if (all->parspipex[pip->curr]->outfile_append)
	{
		pip->fd_outfile_append = malloc(sizeof(int) * (ft_strlen_array(all->parspipex[pip->curr]->outfile_append) + 1));
		while (all->parspipex[pip->curr]->outfile_append[i])
		{
			pip->fd_outfile_append[i] = open(all->parspipex[pip->curr]->outfile_append[i], 	O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (pip->fd_outfile_append[i] == -1)
				return (1);
			i++;
		}
		pip->fd_outfile_append[i] = -2;
	}
	return (0);
}



void	init_files(t_all *all, t_pip *pip)
{
	// init_fd_tab(pip, all->parspipex[pip->curr]->heredoc);
	// if (init_file_tab(&pip->fd_infile, &(all->parspipex[pip->curr]->infile), 'i') == 1
	// 	|| init_file_tab(&pip->fd_outfile, &(all->parspipex[pip->curr]->outfile), 'o') == 1)
		// || init_file_tab(pip->fd_outfile_append, all->parspipex[pip->curr]->outfile_append, 'a') == 1)
	// {
	// 	perror("");
	// 	free_exit(all, pip, 1, "");
	// }
	init_infile_tab(all, pip);
	init_outfile_tab(all, pip);
	init_outfile_append_tab(all, pip);
	ft_printf("%d %d\n", pip->fd_infile[0],pip->fd_infile[1]);
	ft_printf("%d %d\n", pip->fd_outfile[0],pip->fd_outfile[1]);
	ft_printf("%d %d\n", pip->fd_outfile_append[0],pip->fd_outfile_append[1]);
	// if (all->outfile && all->outfile_append == 1)
	// {	
	// 	pip->fd_outfile = open(all->outfile,
	// 			O_WRONLY | O_CREAT | O_APPEND, 0644);
	// 	if (pip->fd_outfile == -1)
	// 	{
	// 		perror("");
	// 		free_exit(all, pip, 1, "");
	// 	}
	// }
	// else if (all->outfile)
	// {	
	// 	pip->fd_outfile = open(all->outfile,
	// 			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// 	if (pip->fd_outfile == -1)
	// 	{
	// 		perror("");
	// 		free_exit(all, pip, 1, "");
	// 	}
	// }
}

void	init_cmd(t_all *all, t_pip *pip)
{
	pip->cmd = ft_strdup_array(pip->tab_cmd[pip->curr]);
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
}

int	pipex(t_all *all)
{
	t_pip	pip;

	pip.nb_arg = ft_strlen_parse(all->parspipex);
	if (pip.nb_arg >= 1)
	{
		init_pip(all, &pip);
		// here_doc(all, &pip);
		while (pip.curr < pip.nb_arg)
		{
			init_files(all, &pip);
			init_cmd(all, &pip);
			exec_cmd(all, &pip);
			pip.curr += 1;
		}
		close_p(&pip);
		wait_id(&pip);
		free_exit(all, &pip, 0, NULL);
	}
	return (0);
}
