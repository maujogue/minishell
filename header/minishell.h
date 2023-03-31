/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:42:36 by avaganay          #+#    #+#             */
/*   Updated: 2023/03/31 15:30:11 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>

# include <readline/readline.h>
# include <readline/history.h>


typedef struct s_listenv
{
	char				*key;
	char				*content;
	struct s_listenv	*next;
}	t_listenv;

typedef struct s_all
{
	t_listenv	*listenv;
	t_listenv	*listexport;
}	t_all;

void    ft_builtins(char *cmd, t_all *all, char **envp);

void		ft_cd(char *path);
void		ft_echo(t_all *all, char *cmd);
t_listenv	*ft_env(char **envp);
void		ft_exit(int code);
void		ft_export(char **envp, t_all *all, char *cmd);
void		ft_pwd(void);
void		ft_unset(t_listenv *listenv, char *cmd);

void    	ft_print_listenv(t_all *all, char *cmd);
void		ft_print_tab(char **tab);
void		ft_print_export(char **tab);
void		ft_print_listexport(t_listenv *listexport, t_all *all);

int			ft_strcmp(const char *s1, const char *s2);
t_listenv	*ft_lstexport_new(char *var);
t_listenv	*ft_lstexportlast(t_listenv *lst);
void		ft_lstexportadd_back(t_listenv **lst, t_listenv *new);
int			ft_lstexportsize(t_listenv *lst);

void		ft_freetab(char **tab);

#endif
