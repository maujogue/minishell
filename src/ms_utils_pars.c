/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_pars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:04:41 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/26 10:48:34 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_is_charspe(char c)
{
	if ((c >= 33 && c <= 47) || (c >= 58 && c <= 64)
		|| (c >= 91 && c <= 94) || (c >= 123 && c <= 125))
		return (1);
	return (0);
}

int	ft_is_solo_pipe(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
		{
			if (cmd[i + 1] != '|')
				write(2 ,"bash: syntax error near unexpected token `|'\n", 45);
			else
				write(2 ,"bash: syntax error near unexpected token `||'\n", 46);
			return (1);
		}
		if (cmd[i] != ' ' && cmd[i] != '|')
			return (0);
		i++;
	}
	return (0);
}

int	ft_is_solo_bracket_left(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '<')
		{
			if (cmd[i + 1] != '<')
				write(2 ,"bash: syntax error near unexpected token `<'\n", 45);
			else
				write(2 ,"bash: syntax error near unexpected token `<<'\n", 46);
			return (1);
		}
		if (cmd[i] != ' ' && cmd[i] != '<')
			return (0);
		i++;
	}
	return (0);
}

int	ft_is_solo_bracket_right(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '>')
		{
			if (cmd[i + 1] != '>')
				write(2 ,"bash: syntax error near unexpected token `>'\n", 45);
			else
				write(2 ,"bash: syntax error near unexpected token `>>'\n", 46);
			return (1);
		}
		if (cmd[i] != ' ' && cmd[i] != '>')
			return (0);
		i++;
	}
	return (0);
}