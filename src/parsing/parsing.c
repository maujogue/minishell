/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:34:45 by avaganay          #+#    #+#             */
/*   Updated: 2023/04/13 11:13:48 by maujogue         ###   ########.fr       */
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

char	*ft_fillparsopt(char *cmd)
{
	char	*res;
	int		i;
	int		len;
	int		start;

	i = 1;
	len = 0;
	while (cmd[i])
	{
		if (cmd[i] == '-' && cmd[i - 1] == ' ')
		{
			start = i;
			while (cmd[i] != ' ')
			{
				i++;
				len++;
			}
			while (cmd[i] == ' ')
				i++;
			if (cmd[i] == '-')
			{
				len++;
				while (cmd[i] != ' ')
				{
					i++;
					len++;
				}
			}
			res = ft_substr(cmd, start, len);
			return (res);
		}
		i++;
	}
	return (NULL);
}

int	ft_isopt(char *cmd, int i)
{
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] == '-')
		return (1);
	return (0);
}

int	ft_endcmdopt(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] == ' ' && cmd[i])
		i++;
	while (cmd[i] && cmd[i] != ' ')
		i++;
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
		if (cmd[i] != '\0' && cmd[i] != ' ')
			nb++;
		while (cmd[i] != ' ' && cmd[i])
			i++;
	}
	return (nb);
}

char	*ft_fillarg(char *cmd, int *i)
{
	char	*res;
	int		start;
	int		isarg;

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
	return (res);
}

char	**ft_fillparsarg(char *cmd)
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
		tab[count] = ft_fillarg(cmd, &i);
		count++;
		i++;
	}
	tab[count] = NULL;
	return (tab);
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