/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:16 by maujogue          #+#    #+#             */
/*   Updated: 2023/04/04 16:49:57 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/*char	*ft_arg_unset(char *cmd)
{
	char	*str;
	int		i;
	int		j;

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

t_listenv   ft_unsetlast(t_listenv *listenv, char *cmd)
{
	char	*str;

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
}*/

int	ft_find_unset(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i + 6] == s2[i]) && s1[i + 6] && (i < n - 1))
    {
        if (s2[i + 1] == '\0')
            return (1);
		i++;
    }
    return (0);
}

void	ft_arg_not_valid(char *cmd)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	tab = ft_split(cmd, ' ');
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if ((tab[i][j] >= 33 && tab[i][j] <= 47) || tab[i][j] == 91 || tab[i][j] == 93 || tab[i][j] == 123 || tab[i][j] == 125)
			{
				printf("minishell: unset: '%s': not a valid identifier\n", tab[i]);
				break ;
			}
			j++;
		}
		i++;
	}
	ft_freetab(tab);
}

void    ft_unset(t_listenv *listenv, char *cmd)
{
    t_listenv   *prev;
    t_listenv   *tmp;
    int len;
    
    len = ft_strlen(cmd);
    tmp = listenv;
    prev = NULL;
    ft_arg_not_valid(cmd);
    while (tmp)
    {
        if  (ft_find_unset(cmd, tmp->key, len) == 1)
        {
            prev->next = tmp->next;
            free(tmp->key);
            free(tmp->content);
            free(tmp);
            return ;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}