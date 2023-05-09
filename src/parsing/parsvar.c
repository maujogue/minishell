/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsvar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:47:34 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/09 14:35:31 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*ft_fill_replace_var(t_listenv *listenv, char *var)
{
	while (listenv)
	{
		if (ft_strcmp(var, listenv->key) == 0)
			return (listenv->content);
		listenv = listenv->next;
	}
	return (NULL);
}

char	*ft_fill_to_replace_var(t_all *all, char *cmd,
	int *i, int *var_already_fill)
{
	char	*var;
	int		start;

	if (cmd[*i + 1] == '?')
		return (*var_already_fill = 1, ft_itoa(all->exit_code));
	start = *i + 1;
	while (cmd[*i] != ' ' && cmd[*i])
		*i += 1;
	var = ft_substr(cmd, start, *i - start);
	return (var);
}
//////////////////////////////TEST
char	*ft_replace_var(t_all *all, char *cmd)
{
	char	*cmdfinal;
	int		i;
	char	*var;
	int		var_already_fill;

	i = 0;
	while (cmd[i] && cmd[i] != '$')
		i++;
	cmdfinal = ft_substr(cmd, 0, i);
	while (cmd[i])
	{
		var_already_fill = 0;
		if (cmd[i] == '$')
		{
			var = ft_fill_to_replace_var(all, cmd, &i, &var_already_fill);
			printf("\nVAR BEFORE: %s\n", var);
			if (var_already_fill == 0)
				var = ft_fill_replace_var(all->listenv, var);
			printf("VAR AFTER: %s\n", var);
		}
		i++;
	}
	return (cmdfinal);
}
