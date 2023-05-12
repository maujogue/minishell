/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsvar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:47:34 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/12 15:29:36 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*ft_fill_replace_dollar(t_all *all, char *var, int *i)
{
	t_listenv	*tmp;
	t_listenv	*tmp_res;

	tmp = all->listenv;
	while (all->listenv)
	{
		tmp_res = all->listenv;
		if (ft_strcmp(var, all->listenv->key) == 0)
		{
			*i -= 1;
			all->listenv = tmp;
			return (tmp_res->content);
		}
		all->listenv = all->listenv->next;
	}
	all->listenv = tmp;
	tmp = all->listexport;
	while (all->listexport)
	{
		tmp_res = all->listexport;
		if (ft_strcmp(var, all->listexport->key) == 0)
		{
			*i -= 1;
			all->listexport = tmp;
			return (tmp_res->content);
		}
		all->listexport = all->listexport->next;
	}
	all->listexport = tmp;
	return (NULL);
}

char	*ft_fill_to_replace_dollar(t_all *all, char *cmd,
	int *i, int *var_already_fill)
{
	char	*var;
	int		start;

	if (cmd[*i + 1] == '?')
		return (*i += 1, *var_already_fill = 1, ft_itoa(all->exit_code));
	start = *i + 1;
	while (cmd[*i] != ' ' && cmd[*i])// && ft_is_charspe(cmd[*i]) == 0)
		*i += 1;
	// printf("%d\n", *i);
	var = ft_substr(cmd, start, *i - start);
	return (var);
}

char	*ft_fill_replace_var(t_all *all, char *cmd,
	int *i, int *var_already_fill)
{
	char	*var;

	if (cmd[*i] == '\'')
		var = ft_fill_piece_simplequote(cmd, i);
	else if (cmd[*i] == '$' && cmd[*i + 1] != '\0' && cmd[*i + 1] != ' ')
	{
		var = ft_fill_to_replace_dollar(all, cmd, i, var_already_fill);
		printf("\nVAR BEFORE: %s\n", var);
		if (*var_already_fill == 0)
			var = ft_fill_replace_dollar(all, var, i);
		printf("VAR AFTER: %s\n", var);
	}
	else
		var = ft_substr(cmd, *i, 1);
	return (var);
}

char	*ft_replace_var(t_all *all, char *cmd)
{
	char	*cmdfinal;
	int		i;
	char	*var;
	int		var_already_fill;

	i = 0;
	while (cmd[i] && cmd[i] != '$' && cmd[i] != '\'')
		i++;
	cmdfinal = ft_substr(cmd, 0, i);
	while (cmd[i])
	{
		var_already_fill = 0;
		var = ft_fill_replace_var(all, cmd, &i, &var_already_fill);
		if (var != NULL)
			cmdfinal = ft_strjoin(cmdfinal, var);
		i++;
	}
	return (cmdfinal);
}
