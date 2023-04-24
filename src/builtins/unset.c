/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:16 by maujogue          #+#    #+#             */
/*   Updated: 2023/04/24 15:16:38 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

// int	ft_find_unset(const char *s1, const char *s2, int n)
// {
// 	int	i;
// 	int	jump;

// 	i = 0;
// 	jump = 0;
// 	if (n == 0)
// 		return (0);
// 	while (s1[jump] != ' ')
// 		jump++;
// 	while (s1[jump] == ' ')
// 		jump++;
// 	while ((s1[i + jump] == s2[i]) && s1[i + jump] && (i < n - 1))
// 	{
// 		if (s2[i + 1] == '\0')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

void	ft_arg_not_valid(char **tab)
{
	int		i;
	int		j;

	i = 1;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if ((tab[i][j] >= 33 && tab[i][j] <= 47) || tab[i][j] == 91
				|| tab[i][j] == 93 || tab[i][j] == 123 || tab[i][j] == 125)
			{
				printf("minishell: unset: '%s': not a valid identifier\n", tab[i]);
				break ;
			}
			j++;
		}
		i++;
	}
	ft_freetab(tab);
}

void	ft_unset(t_all *all, t_pip *pip)
{
	t_listenv	*tmp;
	int	i;

	i = 1;

	// ft_arg_not_valid(pip->cmd);
	if (ft_strlen_array(pip->cmd) <= 1)
		return ;
	while (pip->cmd[i])
	{
		tmp = all->listenv;
		unset_env_var(pip->cmd[i], tmp);
		all->listenv = tmp;
		
		tmp = all->listexport;
		unset_env_var(pip->cmd[i], tmp);
		all->listexport = tmp;
		i++;
	}
}
