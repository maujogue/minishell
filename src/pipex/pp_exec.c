/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:53:34 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/05 13:50:37 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	close_p(t_pip *pip, int nb)
{
	int	i;

	i = 0;
	while (i < nb * 2)
	{
		close(pip->fds[i]);
		i++;
	}
}

void	wait_id(t_pip *pip)
{
	int	i;
	int	status;
	int	temp;

	temp = g_status;
	i = 0;
	status = 0;
	while (i <= pip->nb_arg)
	{
		wait(&status);
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
		i++;
	}
	if (g_status == 0)
		g_status = temp;
}

void	exec_cmd(t_all *all, t_pip *pip)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		free_exit(all, pip, 1, "Error\nFork failed");
	signals_in_process(pip->cmd[0]);
	if (pid == 0)
	{
		dup_pipe(all, pip);
		close_p(pip, pip->curr);
		if (is_builtin(pip) == 1)
			return (execve(pip->path_cmd, pip->cmd, pip->envp), perror(""));
		else if (ft_strlen_triple_char(pip->tab_cmd) > 1
			|| all->parspipex[pip->curr]->outfile
			|| all->parspipex[pip->curr]->outfile_append)
			ft_builtins(all, pip);
		close_p(pip, pip->nb_arg);
		free_exit(all, pip, 1, "");
	}
	else if (is_builtin(pip) == 0
		&& ft_strlen_triple_char(pip->tab_cmd) == 1
		&& !all->parspipex[pip->curr]->outfile
		&& !all->parspipex[pip->curr]->outfile_append)
		ft_builtins(all, pip);
}
