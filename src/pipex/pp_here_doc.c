/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:52:21 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/05 13:53:20 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	single_here_doc(char **heredoc, int fd[2], int i)
{
	char	*line;

	while (1)
	{
		line = readline(">");
		if (!line)
		{
			printf("exit\n");
			exit(0);
		}
		if (ft_strncmp(line, heredoc[i], ft_strlen(line)) == 0
			&& ft_strncmp(line, heredoc[i],
				ft_strlen(heredoc[i])) == 0)
			break ;
		if (heredoc[i + 1] == NULL)
		{
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
		}
	}
	free(line);
}

void	init_all_here_doc(t_all *all, char **heredoc, t_pip *pip)
{
	int		fd[2];
	int		i;

	i = 0;
	if (heredoc)
	{
		if (pipe(fd) < 0)
			free_exit(all, pip, 1, "Error: open failed \n");
		while (heredoc[i])
		{
			single_here_doc(heredoc, fd, i);
			i++;
		}
		close(fd[1]);
		pip->fd_heredoc = fd[0];
	}
}
