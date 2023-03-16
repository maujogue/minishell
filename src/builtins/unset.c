/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:16 by maujogue          #+#    #+#             */
/*   Updated: 2023/03/16 13:41:56 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char    *ft_arg_unset(char *cmd)
{
    char    *str;
    int     i;
    int     j;

    i = 0;
	j = 0;
    while (cmd[i] != ' ')
    {
        i++;
    }
	i++;
    str = malloc(sizeof(char) * (ft_strlen(cmd) - i));
    while (cmd[i])
    {
        str[j] = cmd[i];
		i++;
		j++;
    }
	return (str);
}

t_listenv   ft_unset(t_listenv *listenv, char *cmd)
{
    char    *str;

	if	(cmd[5] != ' ')
	{
		printf("%s\n", "unset: not enough arguments");
		return (*listenv);
	}
	str = ft_arg_unset(cmd);
    while (listenv->key)
    {
        if (ft_strncmp(str, listenv->key, ft_strlen(str)) == 0)
        {
            printf("%s\n","Key unset find");
        }
        listenv = listenv->next;
    }
    return (*listenv);
}