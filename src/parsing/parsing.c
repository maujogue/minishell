/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:34:45 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/23 15:47:52 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*ft_fill_cmd_is_file(char *cmd, int i)
{
	int		start;
	char	*res;

	while ((cmd[i] == '<' || cmd[i] == '>') && cmd[i] != '\0')
	{
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
	}
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
	int		is_cmd;

	len = 0;
	nospace = 0;
	is_cmd = 0;
	while (cmd[len] == ' ')
	{
		len++;
		nospace++;
	}
	while (cmd[len] != '\0' && cmd[len] != ' ')
	{
		if (cmd[len] != '<' && cmd[len] != '>')
			is_cmd = 1;
		if ((cmd[len] == '<' || cmd[len] == '>') && is_cmd == 0)
			return (ft_fill_cmd_is_file(cmd, len));
		if ((cmd[len] == '<' || cmd[len] == '>') && is_cmd == 1)
			return (ft_substr(cmd, nospace, len - nospace));
		len++;
	}
	res = ft_substr(cmd, nospace, len - nospace);
	return (res);
}

t_pars	*ft_cleanpipe(t_all *all, char *cmd)
{
	t_pars	*cmdpars;
	char	*cmdfinal;

	all->nb_simplequote = ft_countquote(cmd, '\'');
	all->nb_doublequote = ft_countquote(cmd, '\"');
	cmdfinal = ft_replace_var(all, cmd);
	// printf("CMD SANS VAR: %s\n", cmdfinal);
	cmdpars = malloc(sizeof(t_pars));
	cmdpars->cmd = ft_fillparscmd(cmdfinal);
	// printf("%s /", cmdpars->cmd);
	cmdpars->opt2 = ft_fillparsopt2(cmdfinal);
	// if (cmdpars->opt2 != NULL)
	// 	ft_print_tabarg(cmdpars->opt2);
	// else
	// 	printf("(null)");
	cmdpars->arg = ft_fillparsarg(all, cmdfinal);
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
		printf("cmd %d:\n", i);
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
	ft_fillstructpars(all->parspipex, tabcmd);
	free_array(tabcmd);
}
