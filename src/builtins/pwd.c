/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathisaujogue <mathisaujogue@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:13 by maujogue          #+#    #+#             */
/*   Updated: 2023/06/04 16:05:16 by mathisaujog      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_pwd(t_all *all, t_pip *pip)
{
	char	*path;

	path = get_env_content(all, pip, all->listenv, "PWD");
	ft_putstr_fd(path, 1);
	printf("\n");
	free(path);
}
