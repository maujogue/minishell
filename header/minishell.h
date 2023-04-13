/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:42:36 by avaganay          #+#    #+#             */
/*   Updated: 2023/04/13 13:46:23 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "typedef.h"
# include "pipex.h"

void    	ft_builtins(char *cmd, t_all *all, char **envp);

void		ft_cd(char *path);
void		ft_echo(t_all *all, char *cmd);
void		ft_echo_var(t_all *all, char *arg);
void		ft_echo_env(t_all *all, char *arg);
t_listenv	*ft_env(char **envp);
void		ft_exit(int code);
void		ft_export(char **envp, t_all *all, char *cmd);
void		ft_pwd(void);
void    	ft_unset(t_listenv *listenv, t_all *all, char *cmd);

void    	ft_print_listenv(t_all *all, char *cmd);
void		ft_print_tab(char **tab);
void		ft_print_tab_pipe(char **tab);
void		ft_print_tabexport(char **tab);
void		ft_print_listexport(t_listenv *listexport, t_all *all);
void    	ft_print_tabarg(char **tab);

int			ft_strncmpecho(const char *s1, const char *s2, size_t n);
int			ft_strncmpexport(const char *s1, const char *s2, size_t n);
int			ft_strncmpunset(const char *s1, const char *s2, size_t n);

int			ft_strcmp(const char *s1, const char *s2);
t_listenv	*ft_lstexport_new(char *var);
t_listenv	*ft_lstexportlast(t_listenv *lst);
void		ft_lstexportadd_back(t_listenv **lst, t_listenv *new);
int			ft_lstexportsize(t_listenv *lst);

void		ft_parsing(t_all *all, char *cmd);
int			ft_find_pipe(char *cmd);
char		**ft_fillparsarg(char *cmd);
char		*ft_fillparsopt(char *cmd);

void		ft_freetab(char **tab);

#endif
