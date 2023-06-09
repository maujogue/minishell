/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_pars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:04:41 by avaganay          #+#    #+#             */
/*   Updated: 2023/06/09 10:45:00 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_is_solo_pipe(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
		{
			if (cmd[i + 1] != '|')
				write_error("", "bash: syntax error near unexpected token `|'\n",
					"");
			else
				write_error("",
					"bash: syntax error near unexpected token `||'\n", "");
			return (1);
		}
		if (cmd[i] != ' ' && cmd[i] != '|')
			return (0);
		i++;
	}
	return (0);
}

int	ft_solo_bracket(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != '<' && cmd[i] != '>' && cmd[i] != ' ')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_is_solo_bracket_left(char *cmd)
{
	int	i;
	int	solo_bracket;

	i = 0;
	solo_bracket = ft_solo_bracket(cmd);
	while (cmd[i])
	{
		if (cmd[i] == '<' && solo_bracket == 1)
		{
			if (cmd[i + 1] != '<')
				write_error("",
					"bash: syntax error near unexpected token `newline'\n", "");
			else
				write_error("",
					"bash: syntax error near unexpected token `newline'\n", "");
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
	int	solo_bracket;

	i = 0;
	solo_bracket = ft_solo_bracket(cmd);
	while (cmd[i])
	{
		if (cmd[i] == '>' && solo_bracket == 1)
		{
			if (cmd[i + 1] != '>')
				write_error("",
					"bash: syntax error near unexpected token `newline'\n", "");
			else
				write_error("",
					"bash: syntax error near unexpected token `newline'\n", "");
			return (1);
		}
		if (cmd[i] != ' ' && cmd[i] != '>')
			return (0);
		i++;
	}
	return (0);
}
