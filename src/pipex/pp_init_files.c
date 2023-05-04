/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_init_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:12:15 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/04 14:02:16 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	init_infile_tab(t_all *all, t_pip *pip)
{
	int	i;

	i = 0;
	pip->fd_infile = malloc(sizeof(int) * (ft_strlen_array(all->parspipex[pip->curr]->infile) + 1));
	if (all->parspipex[pip->curr]->infile)
	{
		while (all->parspipex[pip->curr]->infile[i])
		{
			pip->fd_infile[i] = open(all->parspipex[pip->curr]->infile[i], 	O_RDONLY);
			if (pip->fd_infile[i] == -1)
				return (1);
			i++;
		}
	}
	pip->fd_infile[i] = -2;
	return (0);
}

int	init_outfile_tab(t_all *all, t_pip *pip)
{
	int	i;

	i = 0;
	pip->fd_outfile = malloc(sizeof(int) * (ft_strlen_array(all->parspipex[pip->curr]->outfile) + 1));
	if (all->parspipex[pip->curr]->outfile)
	{
		while (all->parspipex[pip->curr]->outfile[i])
		{
			pip->fd_outfile[i] = open(all->parspipex[pip->curr]->outfile[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (pip->fd_outfile[i] == -1)
				return (1);
			i++;
		}
	}
	pip->fd_outfile[i] = -2;
	return (0);
}

int	init_outfile_append_tab(t_all *all, t_pip *pip)
{
	int	i;

	i = 0;
	pip->fd_outfile_append = malloc(sizeof(int) * (ft_strlen_array(all->parspipex[pip->curr]->outfile_append) + 1));
	if (all->parspipex[pip->curr]->outfile_append)
	{
		while (all->parspipex[pip->curr]->outfile_append[i])
		{
			pip->fd_outfile_append[i] = open(all->parspipex[pip->curr]->outfile_append[i], 	O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (pip->fd_outfile_append[i] == -1)
				return (1);
			i++;
		}
	}
	pip->fd_outfile_append[i] = -2;
	return (0);
}

void	here_doc(t_all *all, t_pip *pip)
{
	char	*line;
	int		fd[2];
	int		i;

	i = 0;
	if (all->parspipex[pip->curr]->heredoc)
	{
		if (pipe(fd) < 0)
			free_exit(all, pip, 1, "Error: open failed \n");
		while (all->parspipex[pip->curr]->heredoc[i])
		{
			while (1)
			{
                line = readline(">");
                if (!line)
                {
                    printf("exit\n");
                    exit(0);
                }
				if (ft_strncmp(line, all->parspipex[pip->curr]->heredoc[i], ft_strlen(line)) == 0
					&& ft_strncmp(line, all->parspipex[pip->curr]->heredoc[i],
						ft_strlen(all->parspipex[pip->curr]->heredoc[i])) == 0)
					break ;
                if (all->parspipex[pip->curr]->heredoc[i + 1] == NULL)
                {
                    write(fd[1], line, ft_strlen(line));
                    write(fd[1], "\n", 1);
                }
			}
            free(line);
			i++;
        }
		close(fd[1]);
		pip->fd_heredoc = fd[0];
	}
}

void	init_files(t_all *all, t_pip *pip)
{
	init_infile_tab(all, pip);
	init_outfile_tab(all, pip);
	init_outfile_append_tab(all, pip);
	here_doc(all, pip);
	// ft_printf("%d %d\n", pip->fd_infile[0],pip->fd_infile[1]);
	// ft_printf("%d %d\n", pip->fd_outfile[0],pip->fd_outfile[1]);
	// ft_printf("%d %d\n", pip->fd_outfile_append[0],pip->fd_outfile_append[1]);
}