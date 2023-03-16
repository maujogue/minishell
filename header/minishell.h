/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:42:36 by avaganay          #+#    #+#             */
/*   Updated: 2023/03/16 12:01:34 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>

#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_listenv
{
	char			*key;
	char			*content;
	struct s_listenv	*next;
}	t_listenv;

t_listenv *ft_env(char **envp);
void    ft_export(char  **envp);
t_listenv   ft_unset(t_listenv *listenv, char *cmd);

void    ft_print_listenv(t_listenv *listenv, char *cmd);
void	ft_print_tab(char **tab);

void    ft_freetab(char **tab);

#endif
