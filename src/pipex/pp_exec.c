/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:53:34 by maujogue          #+#    #+#             */
/*   Updated: 2023/04/18 16:21:22 by maujogue         ###   ########.fr       */
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

// void	here_doc(t_all *all, t_pip *pip)
// {
// 	int	fd;
// 	char *line;

// 	if (all->heredoc)
// 	{
// 		fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
// 		if (fd < 0)
// 			free_exit(all, pip, 1, "Error: open failed \n");
// 		while (1)
// 		{
// 			line = readline("heredoc>");
// 			if (ft_strncmp(line, all->heredoc, ft_strlen(line)) == 0)
// 				break;
// 			write(fd, line, ft_strlen(line));
// 			write(fd, "\n", 1);
// 			free(line);
// 		}
// 		free(line);
// 		close(fd);
// 		pip->fd_heredoc = fd;
// 	}
// }

void	dup_pipe(t_all *all, t_pip *pip)
{
	if (all->infile && pip->curr == 0)
	{
		if (dup2(pip->fd_infile, STDIN_FILENO) < 0)
			free_exit(all, pip, 1, "Error: Dup2 failed 1\n");
	}
	if (pip->curr != 0)
	{
		if (dup2(pip->fds[pip->curr - 2], STDIN_FILENO) < 0)
			free_exit(all, pip, 1, "Error: Dup2 failed 11\n");
	}
	if (pip->curr / 2 < pip->nb_arg - 1)
	{
		if (dup2(pip->fds[pip->curr + 1], STDOUT_FILENO) < 0)
			free_exit(all, pip, 1, "Error: Dup2 failed 2\n");
	}
	if (all->outfile && pip->curr / 2 == pip->nb_arg - 1)
	{
		if (dup2(pip->fd_outfile, STDOUT_FILENO) < 0)
			free_exit(all, pip, 1, "Error: Dup2 failed 1\n");
	}
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
		execve(pip->path_cmd1, pip->cmd1, pip->envp);
		perror("");
		free_exit(all, pip, 1, "");
	}
}
