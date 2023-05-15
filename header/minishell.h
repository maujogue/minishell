/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:42:36 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/15 16:03:09 by avaganay         ###   ########.fr       */
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

t_listenv	*unset_env_var(char *cmd, t_listenv *tmp);
char		*get_env_content(t_listenv	*listenv, char *arg);
void		replace_env_arg(t_listenv	*listenv, char *arg, char *replacement);

/****************************EXPORT_UTILS***************************/

void		free_listenv(t_listenv *lst);
t_listenv	*ft_lstexport_new(char *var);
t_listenv	*ft_lstexportlast(t_listenv *lst);
void		ft_lstexportadd_back(t_listenv **lst, t_listenv *new);
int			ft_lstexportsize(t_listenv *lst);
void		ft_replace_double(char *var, t_listenv *listexport, t_all **all);
int			ft_check_double_var(char *var, t_listenv *listexport, t_all **all);
int			ft_check_name_var(char *var);
void		ft_export_fillkeycontentvar(t_listenv *new, char *var);
char		*ft_substrexportkey(char const *s, unsigned int start, size_t len);
char		*ft_substrexportcontent(char const *s,
				unsigned int start, size_t len);
void		ft_sort_env(char **envp);

/****************************PARSING*********************************/

void		ft_parsing(t_all *all, char *cmd);
void		ft_initpars(t_pars *pars);
int			ft_isredir(char *cmd, int i);
void		ft_jump_redir(char *cmd, int *i);
void		ft_jumpfile(char *cmd, int *i);
int			ft_isopt(char *cmd, int i);
int			ft_is_charspe(char c);
int			ft_strlen_triple_char(char ***str);
void		ft_fillstructpars(t_pars **pars, char **tabcmd);
int			ft_strlen_triple_char(char ***str);

/****************************PARSING_ARG*****************************/

char		**ft_fillparsopt2(char *cmd);
char		**ft_fillparsarg(t_all *all, char *cmd);

/****************************PARSING_FILE****************************/

void		ft_fillpars_infile(t_pars *pars, char *cmd);
void		ft_fillpars_outfile(t_pars *pars, char *cmd);
void		ft_fillpars_outfile_append(t_pars *pars, char *cmd);
void		ft_fillpars_heredoc(t_pars *pars, char *cmd);
char		*ft_fillnamefile(char *cmd, int i);
char		**ft_filetodouble(char **tab, char *file);

/****************************PARSING_VAR_QUOTE***********************/

char		*ft_replace_var(t_all *all, char *cmd);

int			ft_countquote(char *cmd, char quote);
char		*ft_parsquote(char *cmd);
char		*ft_fill_piece_simplequote(char *cmd, int *i);
char		*ft_wherequote(t_all *all, char *cmd, int *i);
int			ft_simplequote_start(char *cmd, int i);
char		*ft_cmd_whitout_simplequote(char *cmd);

/****************************SIGNALS********************************/

void		signals(void);
void		signals_in_process(void);
#endif
