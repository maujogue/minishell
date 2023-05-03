/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:08:22 by maujogue          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/03 15:12:10 by maujogue         ###   ########.fr       */
=======
/*   Updated: 2023/05/03 15:05:15 by avaganay         ###   ########.fr       */
>>>>>>> 776d6d93125d07a84924c46d16c15406cfe6dcb8
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

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
	char	*opt;
	char	**opt2;
	char	**arg;
	char	**infile;
	char	**outfile;
	char	**heredoc;
	char	**outfile_append;
	int		heredoc_last;
} t_pars;

typedef struct s_all
{
	t_listenv	*listenv;
	t_listenv	*listexport;
	t_pars		**parspipex;
	char		*infile;
	char		**infile2;
	int			*infile_position;
	char		*outfile;
	int			outfile_append;
	char		**heredoc_delim;
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
	int		*fd_heredoc;
}	t_pip;

#endif