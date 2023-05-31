/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:19:50 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/31 10:50:26 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ft_freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_parse(t_pars *parspipex)
{
	if (!parspipex)
		return ;
	free_array(parspipex->tabfinal);
	free_array(parspipex->arg);
	free_array(parspipex->opt2);
	free(parspipex->cmd);
	parspipex->tabfinal = NULL;
	parspipex->arg = NULL;
	parspipex->opt2 = NULL;
	parspipex->cmd = NULL;
	free(parspipex);
	parspipex = NULL;
}
