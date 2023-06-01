/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsfillpars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:55:56 by avaganay          #+#    #+#             */
/*   Updated: 2023/06/01 13:56:23 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	**ft_if_fillpars_heredoc_outfileappend(t_all *all, char *cmd, int i)
{
	char	*file;
	char	**res;

	file = ft_fillnamefile(cmd, i + 1);
	res = malloc(sizeof(char *) * 2);
	if (!res)
		free_all(all);
	res[0] = file;
	res[1] = NULL;
	return (res);
}

char	**ft_if_fillpars_infile_outfile(t_all *all, char *cmd, int i)
{
	char	*file;
	char	**res;

	file = ft_fillnamefile(cmd, i);
	res = malloc(sizeof(char *) * 2);
	if (!res)
		free_all(all);
	res[0] = file;
	res[1] = NULL;
	return (res);
}
