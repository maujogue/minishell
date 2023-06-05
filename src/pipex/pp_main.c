/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:43:44 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/05 15:35:14 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	init_cmd(t_all *all, t_pip *pip)
{
	pip->cmd = ft_strdup_array(pip->tab_cmd[pip->curr]);
	if (!pip->cmd)
		free_exit(all, pip, 1, "bash: Malloc error\n");
}

void	create_pipes(t_all *all, t_pip *pip)
{
	int	i;

	i = 0;
	pip->fds = malloc(sizeof(int) * (pip->nb_arg * (2)));
	if (!pip->fds)
		free_exit(all, pip, 0, "bash: Malloc error\n");
	while (i < pip->nb_arg)
	{
		if (pipe(&pip->fds[i * 2]))
			free_exit(all, pip, 0, "Error\nPipe failed");
		i++;
	}
}

void	init_pip(t_all *all, t_pip *pip)
{
	char	**envp;

	g_status = 0;
	pip->curr = 0;
	pip->envp = NULL;
	pip->tab_cmd = NULL;
	pip->fds = NULL;
	pip->cmd = NULL;
	pip->path = NULL;
	pip->path_cmd = NULL;
	join_cmds(all, pip, all->parspipex);
	envp = malloc(sizeof(char *) * (ft_lstsize_env(all->listenv) + 1));
	if (!envp)
		free_exit(all, pip, 0, "Error\nMalloc failed");
	pip->envp = lst_to_tab(all->listenv, envp);
	if (!pip->envp)
		free_exit(all, pip, 0, "Error\nMalloc failed");
	pip->path = get_path_envp(pip->envp);
	pip->tab_cmd = get_pip_cmds(all, pip, all->parspipex);
	create_pipes(all, pip);
}

int	is_no_command_with_files(int nb_arg, t_all *all)
{
	if (nb_arg == 1 && !(all->parspipex[0]->cmd) && (all->parspipex[0]->heredoc
			|| all->parspipex[0]->infile || all->parspipex[0]->outfile
			|| all->parspipex[0]->outfile_append))
		return (0);
	return (1);
}

int	pipex(t_all *all)
{
	t_pip	pip;

	pip.nb_arg = ft_strlen_parse(all->parspipex);
	if (pip.nb_arg >= 1)
	{
		init_pip(all, &pip);
		while (pip.curr < pip.nb_arg)
		{
			init_files(all, &pip);
			init_cmd(all, &pip);
			if (check_cmd(all, &pip) == 0)
				exec_cmd(all, &pip);
			free_each_pipe(&pip);
			pip.curr += 1;
		}
		close_p(&pip, pip.nb_arg);
		wait_id(&pip);
		free_pipex(all, &pip);
	}
	return (0);
}
