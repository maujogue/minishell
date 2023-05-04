/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsvar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:47:34 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/04 16:55:54 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*ft_fill_replace_var(t_listenv *listexport, char *var)
{
	// printf("AAAAAAAAAAAAAAAAAAAAAAAA");
	while (listexport)
	{
		printf("ENTRE DANS LISTEXPORT ");
		printf("%s\n", listexport->key);
		if (ft_strcmp(var, listexport->key) == 0)
			return (listexport->content);
		listexport = listexport->next;
	}
	return (NULL);
}

char	*ft_fill_to_replace_var(char *cmd, int *i)
{
	char	*var;
	int		start;

	start = *i + 1;
	while (cmd[*i] != ' ' && cmd[*i])
		*i += 1;
	var = ft_substr(cmd, start, *i - start);
	return (var);
}

char	*ft_replace_var(t_all *all, char *cmd)
{
	char	*cmdfinal;
	int		i;
	char	*var;

	(void)all;
	i = 0;
	while (cmd[i] && cmd[i] != '$')
		i++;
	cmdfinal = ft_substr(cmd, 0, i);
	while (cmd[i])
	{
        if (cmd[i] == '$')
        {
			var = ft_fill_to_replace_var(cmd, &i);
			printf("\nVAR BEFORE: %s\n", var);
			var = ft_fill_replace_var(all->listexport, var);
			printf("VAR AFTER: %s\n", var);
		}
        i++;
	}
	return (cmdfinal);
}