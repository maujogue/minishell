/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:53:34 by maujogue          #+#    #+#             */
/*   Updated: 2023/04/20 15:02:21 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	close_p(t_pip *pip)
{
	int	i;

	i = 0;
	while (i < pip->nb_arg * 2)
	{
		close(pip->fds[i]);
		i++;
	}
}

void	here_doc(t_all *all, t_pip *pip)
{
	char	*line;
	int		fd[2];
	int		i;

	i = 0;
	if (all->heredoc_delim)
	{
		if (pipe(fd) < 0)
			free_exit(all, pip, 1, "Error: open failed \n");
		while (i < ft_strlen_array(all->heredoc_delim))
		{
			while (1)
			{
				line = readline("heredoc>");
				if (ft_strncmp(line, all->heredoc_delim[i],
						ft_strlen(line)) == 0
					&& ft_strncmp(line, all->heredoc_delim[i],
						ft_strlen(all->heredoc_delim[i])) == 0)
					break ;
				write(fd[1], line, ft_strlen(line));
				write(fd[1], "\n", 1);
				free(line);
			}
			i++;
		}
		free(line);
		close(fd[1]);
		pip->fd_heredoc = fd[0];
	}
}

void	dup_pipe(t_all *all, t_pip *pip)
{
	if (all->infile && pip->curr == 0
		&& dup2(pip->fd_infile, STDIN_FILENO) < 0)
		free_exit(all, pip, 1, "Error: Dup2 failed 1\n");
	if (all->heredoc_delim // && pip->curr == all->nb_heredoc - 1)
		&& dup2(pip->fd_heredoc, STDIN_FILENO) < 0)
		free_exit(all, pip, 1, "Error: Dup2 failed 1\n");
	if (pip->curr != 0
		&& dup2(pip->fds[pip->curr - 2], STDIN_FILENO) < 0)
		free_exit(all, pip, 1, "Error: Dup2 failed 3\n");
	if (pip->curr / 2 < pip->nb_arg - 1
		&& dup2(pip->fds[pip->curr + 1], STDOUT_FILENO) < 0)
		free_exit(all, pip, 1, "Error: Dup2 failed 4\n");
	if (all->outfile && pip->curr / 2 == pip->nb_arg - 1
		&& dup2(pip->fd_outfile, STDOUT_FILENO) < 0)
		free_exit(all, pip, 1, "Error: Dup2 failed 5\n");
}

void	wait_id(t_pip *pip)
{
	int	i;

	i = -1;
	while (++i <= pip->nb_arg)
		wait(NULL);
}

void	exec_cmd(t_all *all, t_pip *pip)
{
	int	pid;

	if (check_cmd(all, pip) == 1)
	{
		write_error("No such file or directory\n");
		return ;
	}
	pid = fork();
	if (pid < 0)
		free_exit(all, pip, 1, "Error\nFork failed");
	if (pid == 0)
	{
		dup_pipe(all, pip);
		close_p(pip);
		if (ft_builtins(all, pip) == 1)
		{
			execve(pip->path_cmd, pip->cmd, pip->envp);
			perror("");
		}
		free_exit(all, pip, 1, "");
	}
	if (ft_builtins(all, pip) == -1)
		ft_exit(pip->cmd);
}
