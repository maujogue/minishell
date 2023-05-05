/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:34:45 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/05 14:23:06 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*ft_fill_cmd_is_file(char *cmd, int i)
{
	int		start;
	char	*res;

	while (cmd[i] == '<' || cmd[i] == '>')
		i++;
	while (cmd[i] == ' ')
		i++;
	while (cmd[i] != ' ' && cmd[i])
		i++;
	if (cmd[i] == '\0')
		return (NULL);
	while (cmd[i] == ' ')
		i++;
	start = i;
	while (cmd[i] != ' ' && cmd[i])
		i++;
	res = ft_substr(cmd, start, i - start);
	return (res);
}

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
	{
		if (cmd[len] == '<' || cmd[len] == '>')
			return (ft_fill_cmd_is_file(cmd, len));
		len++;
	}
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

t_pars	*ft_cleanpipe(t_all *all, char *cmd)
{
	t_pars	*cmdpars;
	char	*cmdfinal;

	cmdfinal = ft_replace_var(all, cmd);
	printf("CMD SANS VAR: %s\n", cmdfinal);
	cmdpars = malloc(sizeof(t_pars));
	cmdpars->cmd = ft_fillparscmd(cmd);
	printf("%s /", cmdpars->cmd);
	cmdpars->opt2 = ft_fillparsopt2(cmd);
	if (cmdpars->opt2 != NULL)
		ft_print_tabarg(cmdpars->opt2);
	else
		printf("(null)");
	cmdpars->arg = ft_fillparsarg(all, cmd);
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
		all->parspipex[i] = ft_cleanpipe(all, tabcmd[i]);
		i++;
	}
	all->parspipex[i] = NULL;
}

void	ft_parsing(t_all *all, char *cmd)
{
	char	**tabcmd;

	tabcmd = ft_split(cmd, '|');
	ft_fillparspipex(all, tabcmd);
	// ft_fillfile_heredoc(all, cmd);
	ft_fillstructpars(all->parspipex, tabcmd);
}
