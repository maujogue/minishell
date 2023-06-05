/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_init_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:12:15 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/05 13:46:02 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	init_infile_tab(char **infile, t_pip *pip)
{
	int	i;

	i = 0;
	pip->fd_infile = malloc(sizeof(int) * (ft_strlen_array(infile) + 1));
	if (!pip->fd_infile)
		return (-1);
	if (infile)
	{
		while (infile[i])
		{
			pip->fd_infile[i] = open(infile[i], O_RDONLY);
			if (pip->fd_infile[i] == -1 && access(infile[i], F_OK) == 0)
				return (write_error("bash: ", infile[i],
						" : Permission denied\n"), g_status = 1, 1);
			else if (pip->fd_infile[i] == -1)
				return (write_error("bash: ", infile[i],
						" : No such file or directory\n"), g_status = 1, 1);
			i++;
		}
	}
	pip->fd_infile[i] = -2;
	return (0);
}

int	init_outfile_tab(char **outfile, t_pip *pip)
{
	int	i;

	i = 0;
	pip->fd_outfile = malloc(sizeof(int) * (ft_strlen_array(outfile) + 1));
	if (!pip->fd_outfile)
		return (-1);
	if (outfile)
	{
		while (outfile[i])
		{
			pip->fd_outfile[i] = open(outfile[i],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (pip->fd_outfile[i] == -1)
				return (write_error("bash: ", outfile[i],
						": Permission denied\n"), g_status = 1, 1);
			i++;
		}
	}
	pip->fd_outfile[i] = -2;
	return (0);
}

int	init_outfile_append_tab(char **outfile_append, t_pip *pip)
{
	int	i;

	i = 0;
	pip->fd_outfile_append = malloc(sizeof(int)
			* (ft_strlen_array(outfile_append) + 1));
	if (!pip->fd_outfile_append)
		return (-1);
	if (outfile_append)
	{
		while (outfile_append[i])
		{
			pip->fd_outfile_append[i] = open(outfile_append[i],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (pip->fd_outfile_append[i] == -1)
				return (write_error("bash: ", outfile_append[i],
						": Permission denied\n"), g_status = 1, 1);
			i++;
		}
	}
	pip->fd_outfile_append[i] = -2;
	return (0);
}

void	init_files(t_all *all, t_pip *pip)
{
	if (init_infile_tab(all->parspipex[pip->curr]->infile, pip) == -1)
		free_exit(all, pip, 1, "Error\nMalloc failed");
	if (init_outfile_tab(all->parspipex[pip->curr]->outfile, pip) == -1)
		free_exit(all, pip, 0, "Error\nMalloc failed");
	if (init_outfile_append_tab(all->parspipex[pip->curr]->outfile_append,
			pip) == -1)
		free_exit(all, pip, 0, "Error\nMalloc failed");
	init_all_here_doc(all, all->parspipex[pip->curr]->heredoc, pip);
}
