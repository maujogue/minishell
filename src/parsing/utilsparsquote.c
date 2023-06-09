/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsparsquote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:52:06 by avaganay          #+#    #+#             */
/*   Updated: 2023/06/09 11:39:03 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*ft_double_quote_in_simple(char *cmd, int *i)
{
	char	*res_in_simple_quote;
	int		len;
	int		start;

	len = 0;
	*i += 1;
	start = *i;
	while (cmd[*i] != '\'' && cmd[*i])
	{
		*i += 1;
		len++;
	}
	res_in_simple_quote = ft_substr(cmd, start, len);
	return (res_in_simple_quote);
}

char	*ft_replace_var_in_quote(t_all *all, char *str)
{
	char	*res;
	char	*var;
	int		i;
	int		var_already_fill;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	res = ft_substr(str, 0, i);
	while (str[i])
	{
		var_already_fill = 0;
		var = ft_fill_replace_var(all, str, &i, &var_already_fill);
		if (var != NULL)
			res = ft_strjoin_gnl(res, var);
		free(var);
		if (str[i] != '\0')
			i++;
	}
	return (res);
}

char	*ft_end_simple_quote_in_double(t_all *all, char *cmd, int len,
	int start)
{
	char	*res_no_var;
	char	*res;

	res_no_var = ft_substr(cmd, start, len);
	res = ft_replace_var_in_quote(all, res_no_var);
	return (res);
}

void	ft_simple_quote_in_double_while(char *cmd, int *i, int *len)
{
	while (cmd[*i] != '\"' && cmd[*i])
	{
		*i += 1;
		*len += 1;
	}
}

char	*ft_simple_quote_in_double(t_all *all, char *cmd, int *i)
{
	char	*res;
	int		j;
	int		len;
	int		start;

	len = 0;
	*i += 1;
	j = *i;
	start = *i;
	if (cmd[*i] == '$' && cmd[*i + 1] == '\"')
		return (*i += 2, ft_substr(cmd, start, 1));
	while (cmd[j])
	{
		if (cmd[j] == '\'')
			break ;
		if (cmd[j] == '"' || cmd[j + 1] == '\0')
		{
			*i = start - 1;
			return (NULL);
		}
		j++;
	}
	ft_simple_quote_in_double_while(cmd, i, &len);
	res = ft_end_simple_quote_in_double(all, cmd, len, start);
	return (res);
}
