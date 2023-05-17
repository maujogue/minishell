/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:08:22 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/17 11:20:43 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

extern int	g_status;

typedef struct s_listenv
{
	char				*key;
	char				*content;
	struct s_listenv	*next;
}	t_listenv;

typedef struct s_pars
{
	char	**tabfinal;
	char	*cmd;
	char	**opt2;
	char	**arg;
	char	**infile;
	char	**outfile;
	char	**heredoc;
	char	**outfile_append;
	int		heredoc_last;
	int		outfile_last;
}	t_pars;

typedef struct s_all
{
	t_listenv		*listenv;
	t_listenv		*listexport;
	t_pars			**parspipex;
	unsigned int	exit_code;
	int				nb_simplequote;
	int				nb_doublequote;
	int				pos_simplequote;
	int				pos_doublequote;
}	t_all;

typedef struct pip
{
	char	***tab_cmd;
	char	**envp;
	char	**cmd;
	char	*path_cmd;
	char	*path;
	int		nb_arg;
	int		curr;
	int		*fds;
	int		*fd_infile;
	int		*fd_outfile;
	int		*fd_outfile_append;
	int		fd_heredoc;
}	t_pip;

#endif