/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:34:45 by avaganay          #+#    #+#             */
/*   Updated: 2023/04/28 09:42:12 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*ft_fillparscmd(char *cmd)
{
	int		len;
	int		nospace;
	char	*res;
	// char	*reswithoutquote;

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
	// printf("ICI\n");
	// printf("%s\n", res);
	// len = 0;
	// nospace = 0;
	// while (res[len])
	// {
	// 	if (res[len] != '\"' && res[len] != '\'')
	// 		nospace++;
	// 	len++;
	// }
	// reswithoutquote = malloc(sizeof(char) * (nospace + 1));
	// len = 0;
	// nospace = 0;
	// while (res[len])
	// {
	// 	if (res[len] != '\"' && res[len] != '\'')
	// 	{
	// 		reswithoutquote[nospace] = res[len];
	// 		nospace++;
	// 	}
	// 	len++;
	// }
	// printf("%s\n", reswithoutquote);
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
	cmdpars->opt2 = ft_fillparsopt2(cmd);
	if (cmdpars->opt2 != NULL)
		ft_print_tabarg(cmdpars->opt2);
	else
		printf("(null)");
	cmdpars->arg = ft_fillparsarg(cmd);
	printf("/");
	if (cmdpars->arg != NULL)
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
		printf("cmd %d:", i);
		all->parspipex[i] = ft_cleanpipe(tabcmd[i]);
		i++;
	}
	all->parspipex[i] = NULL;
}

void	ft_parsing(t_all *all, char *cmd)
{
	char	**tabcmd;

	tabcmd = ft_split(cmd, '|');
	ft_fillparspipex(all, tabcmd);
}
