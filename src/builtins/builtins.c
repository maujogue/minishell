/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:15:34 by avaganay          #+#    #+#             */
/*   Updated: 2023/03/17 12:07:11 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void    ft_builtins(char *cmd, t_listenv *listenv, char **envp)
{
    if (ft_strncmp(cmd, "clear", 5) == 0)
		clear_history();
	if (ft_strncmp(cmd, "env", 3) == 0)
		ft_print_listenv(listenv, cmd);
	if (ft_strncmp(cmd, "export", 6) == 0)
		ft_export(envp);
	if (ft_strncmp(cmd, "unset", 5) == 0)
		ft_unset(listenv, cmd);
}