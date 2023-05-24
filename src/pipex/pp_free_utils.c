/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:31:57 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/24 15:13:30 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	write_error(char *bash, char *str, char *message)
{
	write(2, bash, ft_strlen(bash));
	write(2, str, ft_strlen(str));
	write(2, message, ft_strlen(message));
}

void	free_array(char **tab)
{
	int	i;

	i = -1;
	if (tab != NULL)
	{
		while (tab[++i])
			free(tab[i]);
		free(tab);
		tab = NULL;
	}
}

void	free_triple_array(char ***tab)
{
	int	i;

	i = -1;
	if (tab != NULL)
	{
		while (tab[++i])
			free_array(tab[i]);
		free(tab);
		tab = NULL;
	}
}

void	ft_lstclear_env(t_listenv *lst)
{
	t_listenv	*temp;

	if (!lst)
		return ;
	while (lst != NULL)
	{
		temp = (lst)->next;
		free(lst->key);
		free(lst->content);
		free(lst->next);
		lst = temp;
	}
	lst = NULL;
}

void	free_listenv(t_listenv *lst)
{
	t_listenv	*temp;

	while (lst)
	{
		temp = lst->next;
		free(lst->content);
		free(lst->key);
		free(lst);
		lst = temp;
	}
}
