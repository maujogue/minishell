/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_is_double_char_spe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:44:42 by avaganay          #+#    #+#             */
/*   Updated: 2023/06/09 11:40:07 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_if_is_double_char_spe(int in_quotes, char *cmd, int i)
{
	if (cmd[i] == '"' && !in_quotes)
		in_quotes = 1;
	else if (cmd[i] == '"' && in_quotes)
		in_quotes = 0;
	if (cmd[i] == '\'' && !in_quotes)
		in_quotes = 1;
	else if (cmd[i] == '\'' && in_quotes)
		in_quotes = 0;
	return (in_quotes);
}

void	ft_init_is_double_char_spe(int *i, int *in_quotes)
{
	*i = 0;
	*in_quotes = 0;
}

int	ft_is_double_char_spe(char *cmd, char c)
{
	int	i;
	int	in_quotes;

	ft_init_is_double_char_spe(&i, &in_quotes);
	while (cmd[i])
	{
		in_quotes = ft_if_is_double_char_spe(in_quotes, cmd, i);
		if (!in_quotes)
		{
			if (cmd[i] == c)
			{
				i++;
				if ((c == '>' || c == '<') && cmd[i] == c)
					i++;
				while (cmd[i] == ' ')
					i++;
				if (cmd[i] == c)
					return (
						printf("bash: syntax error near unexpected token `%c'\n",
							c), 1);
			}
		}
		i++;
	}
	return (0);
}
