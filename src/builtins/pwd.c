/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathisaujogue <mathisaujogue@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:13 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/16 18:44:37 by mathisaujog      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_pwd()
{
	char	*path;

	path = getcwd(NULL, 0);
	ft_putstr_fd(path, 1);
	printf("\n");
	free(path);
}
