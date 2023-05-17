/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:53:34 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/17 13:57:46 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	close_p(t_pip *pip, int all)
{
	int	i;

	i = 0;
	while (i < pip->curr * all)
	{
		close(pip->fds[i]);
		i++;
	}
}

void	wait_id(t_pip *pip)
{
	int	i;
	int	status;

	i = 0;
	while (i <= pip->nb_arg)
	{
		wait(&status);
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
		i++;
	}
}

void	exec_cmd(t_all *all, t_pip *pip)
{
	int	pid;

	if (check_cmd(all, pip) == 1)
		return ;
	signals_in_process();
	pid = fork();
	if (pid < 0)
		free_exit(all, pip, 1, "Error\nFork failed");
	if (pid == 0)
	{
		dup_pipe(all, pip);
		close_p(pip, 2);
		if (is_builtin(all, pip) == 1)
			return (execve(pip->path_cmd, pip->cmd, pip->envp), perror(""));
		else if (ft_strlen_triple_char(pip->tab_cmd) > 1
			|| all->parspipex[pip->curr]->outfile)
			ft_builtins(all, pip);
		free_exit(all, pip, 0, "");
	}
	if (is_builtin(all, pip) == 0
		&& ft_strlen_triple_char(pip->tab_cmd) == 1
		&& !all->parspipex[pip->curr]->outfile)
		ft_builtins(all, pip);
}
