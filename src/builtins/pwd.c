/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:13 by maujogue          #+#    #+#             */
/*   Updated: 2023/03/21 15:16:15 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void    ft_pwd(void)
{
    char *path;

    path = getcwd(NULL, 0);
    ft_putstr_fd(path, 1);
    printf("\n");
    free(path);
}