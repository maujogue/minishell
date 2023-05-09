/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:28:48 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/09 16:58:15 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <signal.h>

int	g_status;

void	incr_shell_lvl(t_all *all, int n)
{
	char	*lvl_char;
	int		lvl_int;

	lvl_char = get_env_content(all->listenv, "SHLVL");
	lvl_int = ft_atoi(lvl_char);
	lvl_int += n;
	free(lvl_char);
	lvl_char = ft_itoa(lvl_int);
	replace_env_arg(all->listenv, "SHLVL", lvl_char);
	free(lvl_char);
}

void	ft_init_all(t_all *all, char **envp)
{
	all->listenv = NULL;
	all->listenv = create_env(envp);
	all->listexport = NULL;
	all->exit_code = 0;
	incr_shell_lvl(all, 1);
}

void	ft_initpars(t_pars *pars)
{
	pars->infile = NULL;
	pars->outfile = NULL;
	pars->heredoc = NULL;
	pars->outfile_append = NULL;
	pars->heredoc_last = 0;
	pars->outfile_last = 0;
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	t_all	all;

	(void) argc;
	(void) argv;
	ft_init_all(&all, envp);
	while (1)
	{
		signals();
		cmd = readline(">>");
		if (!cmd)
		{
			printf("exit\n");
			exit(0);
		}
		add_history(cmd);
		ft_parsing(&all, cmd);
		pipex(&all);
	}
	incr_shell_lvl(&all, -1);
	return (0);
}
