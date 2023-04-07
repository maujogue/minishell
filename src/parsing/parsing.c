/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:34:45 by avaganay          #+#    #+#             */
/*   Updated: 2023/04/07 17:36:24 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_find_pipe(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

t_pars	*ft_cleanpipe(char *cmd)
{
	t_pars	*cmdpars;
	int		len;

	cmdpars = NULL;
	len = 0;
	while (cmd[len] && cmd[len] != ' ')
		len++;
	cmdpars->cmd = ft_substr(cmd, 0, len);
	return (cmdpars);
}

void	ft_fillparspipex(t_all *all, char **tabcmd)
{
	int	i;

	i = 0;
	while (tabcmd[0])
	{
		all->parspipex[0] = ft_cleanpipe(tabcmd[i]);
		i++;
	}
}

void	ft_parsing(t_all *all, char *cmd)
{
	char	**tabcmd;

	all->parspipex = NULL;
	tabcmd = ft_split(cmd, '|');
	// ft_print_tab(tabcmd);
	ft_fillparspipex(all, tabcmd);
}