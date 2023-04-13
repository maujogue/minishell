/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:31:57 by maujogue          #+#    #+#             */
/*   Updated: 2023/04/13 15:39:24 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	write_error(char *str)
{
	write(2, str, ft_strlen(str));
}

void	free_array(char **tab)
{
	int	i;

	i = -1;
	if (tab != NULL)
	{
		while (tab[++i])
			free(tab[i]);
		free(tab);
	}
}

void	free_fd(void)
{
	int	fd;

	fd = 0;
	while (close(fd) != -1)
		fd++;
	fd = 5;
	while (close(fd) != -1)
		fd++;
}

void	free_triple_array(char ***tab)
{
	int	i;

	i = -1;
	if (tab != NULL)
	{
		while (tab[++i])
			free_array(tab[i]);
	}
}

void	free_exit(t_pip *pip, int i, char *message)
{
	free_array(pip->cmd1);
	free(pip->path_cmd1);
	free_array(pip->envp);
	free_triple_array(pip->tab_cmd);
	free(pip->fds);
	free(pip->path);
	if (i == 0)
	{
		free_fd();
		exit(EXIT_SUCCESS);
	}
	else
	{
		write(2, message, ft_strlen(message));
		free_fd();
		exit(EXIT_FAILURE);
	}
}
