/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:52:21 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/26 16:34:40 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	sigint_handler_in_heredoc(int sig)
{
	(void) sig;
	g_status = 128 + sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	signals_in_heredoc(void)
{
	signal(SIGINT, sigint_handler_in_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	write_control_d_here_doc(int n, char *heredoc)
{
	char	*nbr;

	nbr = ft_itoa(n);
	write_error("bash: warning: here-document at line ", nbr, "");
	write_error(" delimited by end-of-file (wanted `", heredoc, "')\n");
	free(nbr);
}

void	single_here_doc(char **heredoc, int fd[2], int i)
{
	char	*line;
	int		n;

	n = 1;
	while (1)
	{
		if (g_status == 130)
			break ;
		line = readline(">");
		if (!line)
		{
			write_control_d_here_doc(n, heredoc[i]);
			break ;
		}
		if (ft_strncmp(line, heredoc[i], ft_strlen(line)) == 0
			&& ft_strncmp(line, heredoc[i], ft_strlen(heredoc[i])) == 0)
			break ;
		if (heredoc[i + 1] == NULL)
		{
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
		}
		n++;
		free(line);
	}
}

void	init_all_here_doc(t_all *all, char **heredoc, t_pip *pip)
{
	int		fd[2];
	int		i;

	i = 0;
	pip->fd_heredoc = -2;
	if (heredoc)
	{
		signals_in_heredoc();
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
