/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:34:45 by avaganay          #+#    #+#             */
/*   Updated: 2023/06/09 12:39:08 by avaganay         ###   ########.fr       */
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
	char	*temp;
	int		is_cmd;

	ft_init_fillparscmd(cmd, &len, &nospace, &is_cmd);
	while (cmd[len] != '\0' && cmd[len] != ' ')
	{
		if (cmd[len] != '<' && cmd[len] != '>')
			is_cmd = 1;
		if ((cmd[len] == '<' || cmd[len] == '>') && is_cmd == 0)
			return (ft_fill_cmd_is_file(cmd, len));
		if ((cmd[len] == '<' || cmd[len] == '>') && is_cmd == 1)
		{
			while (cmd[len] != '\"')
				len++;
			return (ft_replace_caret(ft_substr(cmd, nospace, len - nospace)));
		}
		len++;
	}
	temp = ft_substr(cmd, nospace, len - nospace);
	res = ft_replace_caret(temp);
	free(temp);
	return (res);
}

t_pars	*ft_cleanpipe(t_all *all, char *cmd)
{
	t_pars	*cmdpars;
	char	*cmdfinal;

	all->nb_simplequote = ft_countquote(cmd, '\'');
	all->nb_doublequote = ft_countquote(cmd, '\"');
	cmdfinal = ft_replace_var(all, cmd);
	cmdpars = malloc(sizeof(t_pars));
	if (!cmdpars)
		return (free_all(all), exit(1), NULL);
	cmdpars->cmd = ft_fillparscmd(cmdfinal);
	cmdpars->opt2 = ft_fillparsopt2(cmdfinal);
	cmdpars->arg = ft_fillparsarg(all, cmdfinal);
	free(cmdfinal);
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
	if (!all->parspipex)
		return (free_all(all), exit(1));
	while (i < len)
	{
		all->parspipex[i] = ft_cleanpipe(all, tabcmd[i]);
		i++;
	}
	all->parspipex[i] = NULL;
}

void	ft_parsing(t_all *all, char *cmd)
{
	char	**tabcmd;
	int		in_single_quotes;

	in_single_quotes = 0;
	if (cmd[0] == '\0')
		return ;
	if (ft_is_solo_pipe(cmd) || ft_is_solo_bracket_left(cmd)
		|| ft_is_solo_bracket_right(cmd) || ft_is_double_char_spe(cmd, '|')
		|| ft_is_double_char_spe(cmd, '<') || ft_is_double_char_spe(cmd, '>'))
		return ((void)(g_status = 2));
	tabcmd = ft_split_with_quote(cmd, '|', in_single_quotes);
	ft_fillparspipex(all, tabcmd);
	ft_fillstructpars(all, all->parspipex, tabcmd);
	all->exit_code = g_status;
	free_array(tabcmd);
}
