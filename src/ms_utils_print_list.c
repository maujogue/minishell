/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_print_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:10:04 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/30 11:10:36 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_print_listenv(t_all *all)
{
	t_listenv	*tmp;

	tmp = all->listenv;
	while (all->listenv != NULL)
	{
		printf("%s", all->listenv->key);
		printf("%c", '=');
		printf("%s\n", all->listenv->content);
		all->listenv = all->listenv->next;
	}
	all->listenv = tmp;
}

void	ft_print_listexport(t_listenv *lst)
{
	while (lst != NULL)
	{
		if (lst->content)
			printf("declare -x %s=\"%s\"\n", lst->key, lst->content);
		else
			printf("declare -x %s\n", lst->key);
		lst = lst->next;
	}
}
