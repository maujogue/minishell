/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:34:45 by avaganay          #+#    #+#             */
/*   Updated: 2023/04/13 16:05:29 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*ft_fillparscmd(char *cmd)
{
	int		len;
	int		nospace;
	char	*res;

	len = 0;
	nospace = 0;
	while (cmd[len] == ' ')
	{
		len++;
		nospace++;
	}
	while (cmd[len] != '\0' && cmd[len] != ' ')
		len++;
	res = ft_substr(cmd, nospace, len - nospace);
	return (res);
}

t_pars	*ft_cleanpipe(char *cmd)
{
	t_pars	*cmdpars;

	(void)cmd;
	cmdpars = malloc(sizeof(t_pars));
	cmdpars->cmd = ft_fillparscmd(cmd);
	printf("%s /", cmdpars->cmd);
	cmdpars->opt = ft_fillparsopt(cmd);
	printf("%s /", cmdpars->opt);
	cmdpars->arg = ft_fillparsarg(cmd);
	if  (cmdpars->arg != NULL)
		ft_print_tabarg(cmdpars->arg);
	else
		printf("(null)");
	printf("\n");
	return (cmdpars);
}

void	ft_fillparspipex(t_all *all, char **tabcmd)
{
	int	i;
	int	len;

	(void)all;
	i = 0;
	len = 0;
	while (tabcmd[len])
		len++;
	all->parspipex = malloc(sizeof(t_pars) * (len + 1));
	while (i < len)
	{
		// printf("ICI");
		// all->parspipex[i] = malloc(sizeof(char) * 15);
		printf("cmd %d:",i);
		all->parspipex[i] = ft_cleanpipe(tabcmd[i]);
		i++;
	}
}

void	ft_parsing(t_all *all, char *cmd)
{
	char	**tabcmd;

	// all->parspipex = NULL;
	tabcmd = ft_split(cmd, '|');
	// ft_print_tab_pipe(tabcmd);
	ft_fillparspipex(all, tabcmd);
}