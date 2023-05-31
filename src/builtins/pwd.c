/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:13 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/31 15:15:42 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_pwd(t_all *all)
{
	char	*path;

	path = get_env_content(all->listenv, "PWD");
	ft_putstr_fd(path, 1);
	printf("\n");
	free(path);
}

/*
mkdir a
mkdir a/b
cd a/b
rm -rf ../../a
cd ..
pwd

ls > > 0
ls | | 0
*/