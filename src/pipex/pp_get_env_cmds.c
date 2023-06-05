/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_get_env_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:07:51 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/05 15:35:11 by maujogue         ###   ########.fr       */
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

char	**lst_to_tab(t_listenv	*listenv, char **envp)
{
	char	*temp1;
	char	*temp2;
	int		i;

	i = 0;
	while (listenv)
	{
		temp1 = ft_strjoin_gnl(ft_strdup(listenv->key), "=");
		if (!temp1)
			return (free(envp), NULL);
		temp2 = ft_strdup(listenv->content);
		if (!temp2)
			return (free(envp), free(temp1), NULL);
		envp[i++] = ft_strjoin(temp1, temp2);
		if (!envp[i - 1])
			return (free_array(envp), free(temp1), free(temp2), NULL);
		free(temp1);
		free(temp2);
		listenv = listenv->next;
		if (!listenv)
			break ;
	}
	envp[i] = NULL;
	return (envp);
}

void	init_parse_cmds(t_pars *parspipex, int *len_arg, int *len_opt)
{
	*len_arg = 0;
	*len_opt = 0;
	if (parspipex->opt2)
		*len_opt = ft_strlen_array(parspipex->opt2);
	if (parspipex->arg)
		*len_arg = ft_strlen_array(parspipex->arg);
}

char	**parse_cmds(t_pars *parspipex, int j, int k)
{
	int		len_arg;
	int		len_opt;
	char	**tab_final;

	init_parse_cmds(parspipex, &len_arg, &len_opt);
	tab_final = malloc(sizeof(char *) * (len_arg + len_opt + 2));
	if (!tab_final)
		return (NULL);
	tab_final[j++] = ft_strdup(parspipex->cmd);
	while (j < len_opt + 1)
	{	
		tab_final[j] = ft_strdup(parspipex->opt2[j - 1]);
		if (!tab_final[j])
			return (free_array(tab_final), NULL);
		j++;
	}
	while (j < len_opt + len_arg + 1)
	{
		tab_final[j] = ft_strdup(parspipex->arg[k++]);
		if (!tab_final[j])
			return (free_array(tab_final), NULL);
		j++;
	}
	tab_final[j] = NULL;
	return (tab_final);
}

void	join_cmds(t_all *all, t_pip *pip, t_pars **parspipex)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (parspipex[i] != NULL)
	{
		parspipex[i]->tabfinal = parse_cmds(parspipex[i], j, k);
		if (!parspipex[i]->tabfinal)
			free_exit(all, pip, 0, "Error\nMalloc failed");
		i++;
	}
}
