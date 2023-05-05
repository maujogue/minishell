/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:42:36 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/05 14:51:27 by maujogue         ###   ########.fr       */
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
# include <sys/ioctl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "typedef.h"
# include "pipex.h"

/****************************BUILTINS********************************/

int			ft_builtins(t_all *all, t_pip *pip);
int			is_builtin(t_all *all, t_pip *pip);

void		ft_cd(t_all *all, t_pip *pip);
void		ft_echo(t_all *all, char **tabecho);
void		ft_echo_var(t_all *all, char *arg);
void		ft_echo_env(t_all *all, char *arg);
void		ft_exit(char **cmd);
void		ft_export(char **envp, t_all *all, char **cmd);
void		ft_pwd(char **cmd);
void		ft_unset(t_all *all, t_pip *pip);
t_listenv	*ft_env(char **envp);

/****************************PRINT_UTILS*****************************/

void		ft_print_listenv(t_all *all, char *cmd, int path_exists);
void		ft_print_tab(char **tab);
void		ft_print_tab_pipe(char **tab);
void		ft_print_tabexport(char **tab);
void		ft_print_listexport(t_listenv *listexport, t_all *all);
void		ft_print_tabarg(char **tab);

/****************************STRCMP_UTILS****************************/

int			ft_strncmpecho(const char *s1, const char *s2, size_t n);
int			ft_strncmpexport(const char *s1, const char *s2, size_t n);
int			ft_strncmpunset(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);

t_listenv	*unset_env_var(char *cmd, t_listenv *tmp);
char		*get_env_content(t_listenv	*listenv, char *arg);
void		replace_env_arg(t_listenv	*listenv, char *arg, char *replacement);

/****************************EXPORT_UTILS***************************/

void		free_listenv(t_listenv *lst);
t_listenv	*ft_lstexport_new(char *var);
t_listenv	*ft_lstexportlast(t_listenv *lst);
void		ft_lstexportadd_back(t_listenv **lst, t_listenv *new);
int			ft_lstexportsize(t_listenv *lst);

/****************************PARSING********************************/

void		ft_parsing(t_all *all, char *cmd);
int			ft_find_pipe(char *cmd);
int			ft_isopt(char *cmd, int i);
char		*ft_fillparsopt(char *cmd);
char		**ft_fillparsopt2(char *cmd);
char		**ft_fillparsarg(char *cmd);
char		*ft_fillnamefile(char *cmd, int i);
char		**ft_filetodouble(char **tab, char *file);
void		ft_fillfile_heredoc(t_all *all, char *cmd);
void		ft_fillheredoc(t_all *all, char *cmd);
int			ft_strlen_triple_char(char ***str);
void		ft_fillstructpars(t_pars **pars, char **tabcmd);

void		ft_freetab(char **tab);

/****************************SIGNALS********************************/

void		signals(void);
void		signals_in_process(void);
#endif
