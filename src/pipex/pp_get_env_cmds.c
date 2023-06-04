/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_get_env_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathisaujogue <mathisaujogue@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:07:51 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/04 17:52:40 by mathisaujog      ###   ########.fr       */
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
	if (!envp)
		return (NULL);
	while (listenv)
	{
		if (!(temp1 = ft_strjoin_gnl(ft_strdup(listenv->key), "=")))
			return (free(envp), NULL);
		if (!(temp2 = ft_strdup(listenv->content)))
			return (free(envp), free(temp1), NULL);
		if (!(envp[i++] = ft_strjoin(temp1, temp2)))
			return (free(envp), free(temp1), free(temp2),NULL);
		free(temp1);
		free(temp2);
		listenv = listenv->next;
		if (!listenv)
			break ;
	}
	envp[i] = NULL;
	return (envp);
}

char	**parse_cmds(t_pars *parspipex, int j, int k)
{
	int		len_arg;
	int		len_opt;

	char	**tab_final;

	len_arg = 0;
	len_opt = 0;
	if (parspipex->opt2)
		len_opt = ft_strlen_array(parspipex->opt2);
	if (parspipex->arg)
		len_arg = ft_strlen_array(parspipex->arg);
	if (!(tab_final = malloc(sizeof(char *) * (len_arg + len_opt + 2))))
		return (NULL);
	tab_final[j++] = ft_strdup(parspipex->cmd);
	while (j < len_opt + 1)
		if (!(tab_final[j++] = ft_strdup(parspipex->opt2[k++])))
			return (free_array(tab_final), NULL);
	k = 0;
	while (j < len_opt + len_arg + 1)
		if (!(tab_final[j++] = ft_strdup(parspipex->arg[k++])))
			return (free_array(tab_final), NULL);
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
		if (!(parspipex[i]->tabfinal = parse_cmds(parspipex[i], j, k)))
			free_exit(all, pip, 0, "Error\nMalloc failed");
		i++;
	}
}
