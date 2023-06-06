/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:47:43 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/06 11:09:24 by avaganay         ###   ########.fr       */
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
int			is_builtin(t_pip *pip);

void		ft_cd(t_all *all, t_pip *pip);
void		ft_env(t_all *all, t_pip *pip);
void		ft_echo(char **tabecho);
void		ft_exit(t_all *all, t_pip *pip);
void		ft_export(t_all *all, t_pip *pip);
void		ft_pwd(t_all *all, t_pip *pip);
void		ft_unset(t_all *all, t_pip *pip);
void		create_env(t_all *all, char **envp);

/****************************CD_UTILS*****************************/

void		replace_env_pwd(t_all *all, t_pip *pip,
				t_listenv	*listenv, char *arg);
int			cd_empty(t_all *all, t_pip *pip, char *pwd);
int			cd_previous(t_all *all, t_pip *pip, char *pwd, char *old_pwd);

/****************************ENV_UTILS****************************/

t_listenv	*unset_env_var(char *cmd, t_listenv *tmp);
char		*get_env_content(t_all *all, t_pip *pip, t_listenv	*listenv,
				char *arg);
int			check_lst_key_exists(t_listenv	*listenv, char *arg);
int			replace_env_arg(t_listenv	*listenv, char *arg, char *replacement);

/****************************EXPORT_UTILS***************************/

t_listenv	*ft_lstexport_new(char *key, char *content);
t_listenv	*ft_lstcat(t_listenv *lst1, t_listenv *lst2);
t_listenv	*ft_lst_dup(t_listenv *lst);
void		ft_lstexport_add_back(t_listenv **lst, t_listenv *new);
void		free_listenv(t_listenv *lst);
void		fill_export(t_all *all, t_pip *pip);
int			check_invalid_identifier_export(char *str, char *cmd, int slash);

/****************************PARSING*********************************/

void		ft_print_listexport(t_listenv *lst);
void		ft_print_listenv(t_all *all);
void		ft_parsing(t_all *all, char *cmd);
void		ft_initpars(t_pars *pars);
void		ft_jump_redir(char *cmd, int *i);
void		ft_jumpfile(char *cmd, int *i);
int			ft_isopt(char *cmd, int i);
int			ft_is_charspe(char c);
int			ft_strlen_triple_char(char ***str);
void		ft_fillstructpars(t_all *all, t_pars **pars, char **tabcmd);
int			ft_strlen_triple_char(char ***str);
char		*ft_fill_caret_when_space(t_all *all, char *cmd);
char		*ft_replace_caret(char *src);
int			ft_is_solo_pipe(char *cmd);
int			ft_is_solo_bracket_left(char *cmd);
int			ft_is_solo_bracket_right(char *cmd);
int			ft_is_double_char_spe(char *cmd, char c);
char		**ft_split_with_quote(char *str, char c, int in_single_quotes);

/****************************PARSING_ARG*****************************/

char		**ft_fillparsopt2(char *cmd);
char		**ft_fillparsarg(t_all *all, char *cmd);
void		ft_init_fillparscmd(char *cmd, int *len, int *nospace, int *is_cmd);

/****************************PARSING_FILE****************************/

int			is(char *str, int i);
void		ft_fillpars_infile(t_all *all, t_pars *pars, char *cmd);
void		ft_fillpars_outfile(t_all *all, t_pars *pars, char *cmd);
void		ft_fillpars_outfile_append(t_all *all, t_pars *pars, char *cmd);
void		ft_fillpars_heredoc(t_all *all, t_pars *pars, char *cmd);
char		**ft_if_fillpars_infile_outfile(t_all *all, char *cmd, int i);
char		**ft_if_fillpars_heredoc_outfileappend(t_all *all, char *cmd,
				int i);
char		*ft_fillnamefile(char *cmd, int i);
char		**ft_filetodouble(char **tab, char *file);

/****************************PARSING_VAR_QUOTE***********************/

char		*ft_replace_var(t_all *all, char *cmd);
char		*ft_fill_replace_var(t_all *all, char *cmd, int *i,
				int *var_already_fill);
int			ft_countquote(char *cmd, char quote);
char		*ft_parsquote(char *cmd);
char		*ft_fill_piece_simplequote(char *cmd, int *i);
char		*ft_wherequote(t_all *all, char *cmd, int *i);
int			ft_doublequote_start(char *cmd, int i);
char		*ft_cmd_whitout_simplequote(char *cmd);
char		*ft_double_quote_in_simple(char *cmd, int *i);
char		*ft_simple_quote_in_double(t_all *all, char *cmd, int *i);

/****************************SIGNALS********************************/

void		signals_in_process(char *cmd);
void		signals_in_heredoc(void);
void		sigint_handler(int sig);
void		sigint_handler_inside_minishell(int sig);

/****************************FREE***********************************/

void		free_all(t_all *all);
void		free_parse(t_pars *parspipex);

#endif
