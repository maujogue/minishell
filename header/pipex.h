/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:38:15 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/05 16:10:43 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "minishell.h"

/****************************FREE_UTILS**************************/

void	write_error(char *bash, char *str, char *message);
void	free_array(char **tab);
void	free_triple_array(char ***tab);
void	free_files(t_all *all, int i);
void	free_each_pipe(t_pip *pip);
void	free_exit(t_all *all, t_pip *pip, int i, char *message);
void	free_pipex(t_all *all, t_pip *pip);
void	free_pipex_files_tab(t_pip *pip);
void	free_parse_tab(t_all *all);

/****************************EXEC********************************/

void	create_pipes(t_all *all, t_pip *pip);
void	init_cmd(t_all *all, t_pip *pip);
int		check_cmd(t_all *all, t_pip *pip);
char	*get_path_envp(char **envp);
char	*get_path_cmd(t_all *all, t_pip *pip, char *cmd, char *path);

/****************************EXEC********************************/

void	exec_cmd(t_all *all, t_pip *pip);
int		pipex(t_all *all);
void	wait_id(t_pip *pip);
void	close_p(t_pip *pip, int all);
void	dup_pipe(t_all *all, t_pip *pip);

/****************************ALL_TO_PIP**************************/

char	***get_pip_cmds(t_all *all, t_pip *pip, t_pars **parspipex);
int		ft_strlen_parse(t_pars **parspipex);
char	**ft_strdup_array(char **s1);
int		ft_strlen_array(char **str);
char	**lst_to_tab(t_listenv	*listenv, char **envp);
int		ft_lstsize_env(t_listenv *lst);
void	join_cmds(t_all *all, t_pip *pip, t_pars **parspipex);

/****************************File_management********************/

void	init_all_here_doc(t_all *all, char **heredoc, t_pip *pip);
void	init_files(t_all *all, t_pip *pip);
void	write_new_heredoc(int fd, char *line);

#endif