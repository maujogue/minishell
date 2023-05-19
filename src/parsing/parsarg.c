/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsarg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:27:22 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/18 12:29:29 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_endcmdopt(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] == ' ' && cmd[i])
		i++;
	while (cmd[i] && cmd[i] != ' ')
	{
		if (cmd[i] == '<' || cmd[i] == '>')
		{
			ft_jumpfile(cmd, &i);
		}
		i++;
	}
	while (ft_isopt(cmd, i))
	{
		while (cmd[i] == ' ')
			i++;
		while (cmd[i] != ' ' && cmd[i])
			i++;
		while (cmd[i] == ' ')
			i++;
	}
	return (i);
}

int	ft_nbargcmd(char *cmd, int i)
{
	int	nb;

	nb = 0;
	while (cmd[i])
	{
		while (cmd[i] == ' ')
			i++;
		if (cmd[i] == '<' || cmd [i] == '>')
		{
			while (cmd[i] != ' ' && cmd[i])
				i++;
			while (cmd[i] == ' ')
				i++;
		}
		else if (cmd[i] != '\0' && cmd[i] != ' ')
			nb++;
		while (cmd[i] != ' ' && cmd[i])
			i++;
	}
	return (nb);
}

char	*ft_fillarg(t_all *all, char *cmd, int *i)
{
	char	*res;
	int		start;
	int		isarg;

	(void)all;
	isarg = 0;
	while (cmd[*i] == ' ')
		*i += 1;
	start = *i;
	while (cmd[*i] != ' ' && cmd[*i])
	{
		isarg = 1;
		*i += 1;
	}
	if (isarg == 0)
		return (NULL);
	res = ft_substr(cmd, start, *i - start);
	res = ft_replace_caret(res);
	return (res);
}

char	**ft_fillparsarg(t_all *all, char *cmd)
{
	char	**tab;
	int		i;
	int		nb;
	int		count;

	count = 0;
	i = ft_endcmdopt(cmd);
	nb = ft_nbargcmd(cmd, i);
	tab = malloc(sizeof(char *) * (nb + 1));
	if (nb == 0)
		return (NULL);
	while (cmd[i] && count < nb)
	{
		while (cmd[i] == ' ')
			i++;
		if (cmd[i] == '<' || cmd [i] == '>')
			ft_jump_redir(cmd, &i);
		tab[count] = ft_fillarg(all, cmd, &i);
		count++;
		i++;
	}
	tab[count] = NULL;
	return (tab);
}
