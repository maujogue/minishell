/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:38:15 by maujogue          #+#    #+#             */
/*   Updated: 2023/04/13 16:05:21 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "minishell.h"

void	write_error(char *str);
void	free_array(char **tab);
void	free_fd(void);
void	free_exit(t_pip *pip, int i, char *message);

void	create_pipes(t_pip *pip);
void	init_cmd(t_pip *pip);
int		check_cmd(t_pip *pip);
char	*get_path_envp(char **envp);
char	*get_path_cmd(t_pip *pip, char *cmd, char *path);

void	exec_cmd(t_all *all, t_pip *pip);
int		pipex(t_all *all);
void    wait_id(t_pip *pip);
void	dup_pipe(t_all *all, t_pip *pip);
void	close_p(t_pip *pip);

char    ***get_pip_cmds(t_pars **parspipex);
int     ft_strlen_parse(t_pars **parspipex);
char	**ft_strdup_array(char **s1);
int     ft_strlen_array(char **str);
char    **lst_to_tab(t_listenv	*listenv);
int     ft_lstsize_env(t_listenv *lst);
void	join_cmds(t_pars **parspipex);
#endif