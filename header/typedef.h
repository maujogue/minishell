/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:08:22 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/03 13:39:00 by maujogue         ###   ########.fr       */
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
	int		*fd_infile;
	int		fd_outfile;
	int		nb_arg;
	int		curr;
	int		*fds;
	int		fd_heredoc;
}	t_pip;

#endif