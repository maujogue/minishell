/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_array_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:21:59 by maujogue          #+#    #+#             */
/*   Updated: 2023/04/12 13:25:54 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_lstsize_env(t_listenv *lst)
{
	t_listenv	*curr;
	int		i;

	curr = lst;
	i = 0;
	while (curr != NULL)
	{
		curr = curr->next;
		i++;
	}
	return (i);
}

char **lst_to_tab(t_listenv	*listenv)
{
	char **envp;
	char *temp1;
	char *temp2;

	envp = malloc(sizeof(char*) * ft_lstsize_env(listenv));
	while (listenv)
	{
		temp1 = ft_strjoin_gnl(ft_strdup(listenv->key),"=");
		temp2 = ft_strdup(listenv->content);
		*envp++ = ft_strjoin(temp1, temp2);
		free(temp1);
		free(temp2);
		listenv = listenv->next;
	}
	return (envp);
}

int	ft_strlen_array(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);	
}

char	**ft_strdup_array(char **s1)
{
	char		**s2;
	
	s2 = malloc(sizeof(char*) * ft_strlen_array(s1) + 1);
	while (*s1 != NULL)
		*s2++ = ft_strdup(*s1++);
	*s2 = NULL;
	return (s2);
}

int	ft_strlen_parse(t_pars **parspipex)
{
	int	i;
	
	i = 0;
	while (parspipex[i] != NULL)
		i++;
	return (i);
}

char ***struct_lst_to_tab(t_pars **parspipex)
{
	char ***tab_cmd;
	int	i;
	
	i = ft_strlen_parse(parspipex);
	tab_cmd = malloc(sizeof(char**) * i);
	i = -1;
	while (parspipex[++i])
		*tab_cmd++ = ft_strdup_array(parspipex[i]->tabfinal);
	parspipex[i] = NULL;
	return (tab_cmd);
}
