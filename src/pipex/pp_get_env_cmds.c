/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_get_env_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:07:51 by maujogue          #+#    #+#             */
/*   Updated: 2023/04/27 11:25:20 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_lstsize_env(t_listenv *lst)
{
	t_listenv	*curr;
	int			i;

	curr = lst;
	i = 0;
	while (curr != NULL)
	{
		curr = curr->next;
		i++;
	}
	return (i);
}

char	**lst_to_tab(t_listenv	*listenv)
{
	char	**envp;
	char	*temp1;
	char	*temp2;
	int		i;

	i = 0;
	envp = malloc(sizeof(char *) * (ft_lstsize_env(listenv) + 1));
	while (listenv)
	{
		temp1 = ft_strjoin_gnl(ft_strdup(listenv->key), "=");
		temp2 = ft_strdup(listenv->content);
		envp[i++] = ft_strjoin(temp1, temp2);
		free(temp1);
		free(temp2);
		listenv = listenv->next;
		if (!listenv)
			break ;
	}
	envp[i] = NULL;
	return (envp);
}

char	**parse_cmds(t_pars *parspipex)
{
	int		len;
	int		j;
	int		k;
	char	**tab_final;

	j = 0;
	k = 0;
	len = 0;
	if (parspipex->arg)
	{
		while (parspipex->arg[len])
			len++;
	}
	if (parspipex->opt)
		len++;
	len++;
	tab_final = malloc(sizeof(char *) * (len + 1));
	tab_final[j++] = ft_strdup(parspipex->cmd);
	if (parspipex->opt)
		tab_final[j++] = ft_strdup(parspipex->opt);
	while (j < len)
		tab_final[j++] = ft_strdup(parspipex->arg[k++]);
	tab_final[j] = NULL;
	return (tab_final);
}

void	join_cmds(t_pars **parspipex)
{
	int	i;

	i = 0;
	while (parspipex[i] != NULL)
	{
		parspipex[i]->tabfinal = parse_cmds(parspipex[i]);
		i++;
	}
}
