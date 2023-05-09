/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:13 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/09 15:50:33 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_pwd(char **cmd)
{
	char	*path;

	if (ft_strlen_array(cmd) > 1)
	{
		write_error("", "", "pwd: too many arguments\n");
		g_status = 1;
	}
	else
	{
		path = getcwd(NULL, 0);
		ft_putstr_fd(path, 1);
		printf("\n");
		free(path);
	}
}
