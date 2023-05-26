/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsvar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:47:34 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/26 14:07:22 by avaganay         ###   ########.fr       */
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
			return (free(var), *i -= 1, all->listenv = tmp, ft_strdup(tmp_res->content));
		all->listenv = all->listenv->next;
	}
	all->listenv = tmp;
	tmp = all->listexport;
	while (all->listexport)
	{
		tmp_res = all->listexport;
		if (ft_strcmp(var, all->listexport->key) == 0)
			return (free(var), *i -= 1, all->listexport = tmp, ft_strdup(tmp_res->content));
		all->listexport = all->listexport->next;
	}
	all->listexport = tmp;
	return (free(var), *i -= 1, NULL);
}

char	*ft_fill_to_replace_dollar(t_all *all, char *cmd,
	int *i, int *var_already_fill)
{
	char	*var;
	int		start;

	if (cmd[*i + 1] == '?')
		return (*i += 1, *var_already_fill = 1, ft_itoa(g_status));
	// printf("DEBUT QUOTE: %s\n", cmd);
	var = ft_wherequote(all, cmd, i);
	// printf("SANS QUOTE: %s\n", var);
	if (var != NULL)
		return (*var_already_fill = 1, var);
	*i += 1;
	start = *i;
	while (cmd[*i] != ' ' && cmd[*i] && cmd[*i] != '\''
		&& cmd[*i] != '\"' && !(cmd[*i] >= 91 && cmd[*i] <= 94)
		&& cmd[*i] != 33 && !(cmd[*i] >= 40 && cmd[*i] <= 47)
		&& !(cmd[*i] >= 58 && cmd[*i] <= 64)
		&& !(cmd[*i] >= 123 && cmd[*i] <= 125)
		&& !(cmd[*i] >= 35 && cmd[*i] <= 38))
		*i += 1;
	var = ft_substr(cmd, start, *i - start);
	return (var);
}

char	*ft_fill_replace_var(t_all *all, char *cmd,
	int *i, int *var_already_fill)
{
	char	*var;

	if (cmd[*i] == '\'')
	{
		all->pos_simplequote++;
		if (all->pos_simplequote % 2 != 0)
			return (ft_double_quote_in_simple(cmd, i));
		// printf("':%d\n", all->pos_simplequote);
		return (NULL);
	}
	if (cmd[*i] == '\"')
	{
		all->pos_doublequote++;
		// printf("\":%d\n", all->pos_doublequote);
		return (NULL);
	}
	if (cmd[*i] == '$' && cmd[*i + 1] != '\0' && cmd[*i + 1] != ' ')
	{
		var = ft_fill_to_replace_dollar(all, cmd, i, var_already_fill);
		// printf("\nVAR BEFORE: %s\n", var);
		if (*var_already_fill == 0)
			var = ft_fill_replace_dollar(all, var, i);
		// printf("VAR AFTER: %s\n", var);
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
	char	*cmdcaret;

	i = 0;
	cmdcaret = ft_fill_caret_when_space(cmd);
	// printf("TEST AVEC CARET: %s\n", cmdcaret);
	all->pos_simplequote = 0;
	all->pos_doublequote = 0;
	while (cmdcaret[i] && cmdcaret[i] != '$' && ft_is_charspe(cmdcaret[i]) == 0)
		i++;
	cmdfinal = ft_substr(cmdcaret, 0, i);
	while (cmdcaret[i])
	{
		var_already_fill = 0;
		var = ft_fill_replace_var(all, cmdcaret, &i, &var_already_fill);
		if (var != NULL)
		{
			cmdfinal = ft_strjoin_gnl(cmdfinal, var);
		}
		free(var);
		i++;
	}
	all->pos_simplequote = 0;
	all->pos_doublequote = 0;
	free(cmdcaret);
	return (cmdfinal);
}
