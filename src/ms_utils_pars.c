/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_pars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:04:41 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/31 16:26:42 by maujogue         ###   ########.fr       */
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
				write_error("", "bash: syntax error near unexpected token `|'\n", "");
			else
				write_error("", "bash: syntax error near unexpected token `||'\n", "");
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
				write_error("", "bash: syntax error near unexpected token `newline'\n", "");
			else
				write_error("", "bash: syntax error near unexpected token `newline'\n", "");
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
				write_error("", "bash: syntax error near unexpected token `newline'\n", "");
			else
				write_error("", "bash: syntax error near unexpected token `newline'\n", "");
			return (1);
		}
		if (cmd[i] != ' ' && cmd[i] != '>')
			return (0);
		i++;
	}
	return (0);
}

int ft_is_double_char_spe(char *cmd, char c)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == c)
		{
			i++;
			while (cmd[i] == ' ')
				i++;
			if (cmd[i] == c)
			{
				write_error("", "bash: syntax error near unexpected token `|'\n", "");
				return (1);
			}
		}
		i++;
	}
	return (0);
}
