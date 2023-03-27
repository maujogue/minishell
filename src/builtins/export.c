/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:11 by maujogue          #+#    #+#             */
/*   Updated: 2023/03/27 16:03:22 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	**ft_dup_env(char **envp)
{
	char	**dup;
	int	count;

    count = 0;
    while (envp[count])
    {
        count++;
    }
	dup = (char **)malloc(sizeof(char *) * (count + 1));
	if (!dup)
		return (NULL);
	dup[count] = 0;
	count--;
	while (count != -1)
	{
		dup[count] = ft_strdup(envp[count]);
		count--;
	}
	return (dup);
}

void	ft_sort_env(char **envp)
{
	char	**dup;
	char	*tmp;
	int	i;
	int	j;

	dup = ft_dup_env(envp);
	i = 0;
	while (dup[i])
	{
		j = i + 1;
		while (dup[j])
		{
			if (ft_strncmp(dup[i], dup[j], ft_strlen(dup[i])) > 0)
			{
				tmp = dup[i];
				dup[i] = dup[j];
				dup[j] = tmp;
			}
			j++;
		}
		i++;
	}
	dup[i - 1] = '\0';
    ft_print_export(dup);
	ft_freetab(dup);
}

int	ft_is_arg_export(char	*cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
	{
		i++;
		if (cmd[i] == ' ')
		{
			i++;
			if (cmd[i] != ' ' && cmd[i] != '\0')
			{
				return (1);
			}
		}
	}
	return (0);
}

// char	**ft_tabvar(char *cmd)
// {
// 	char	**var;
// 	int		nb;
// 	int		i;

// 	i = 0;
// 	nb = -1;
// 	while (cmd[i])
// 	{
// 		while (cmd[i] == ' ')
// 		{
// 			if (cmd[i + 1] != '\0' && cmd[i + 1] != ' ')
// 				nb++;
// 			i++;
// 		}
// 		i++;
// 	}
// 	printf("%d\n", nb);
// 	return (var);
// }

void	ft_fill_var_export(t_all *all, char *cmd)
{
	t_listenv	*listexport;
	char		**var;

	(void)listexport;
	(void)var;
	if (ft_is_arg_export(cmd))
	{
		// var = ft_tabvar(cmd);
		int		nb;
		int		i;

		i = 0;
		nb = -1;
		while (cmd[i])
		{
			while (cmd[i] == ' ')
			{
				if (cmd[i + 1] != '\0' && cmd[i + 1] != ' ')
					nb++;
				i++;
			}
			i++;
		}
		printf("%d\n", nb);
		if (all->listexport == NULL)
		{
			printf("OUI");
		}
	}
}

// void	ft_print_var_export(t_all *all)
// {
	
// }

void	ft_export(char **envp, t_all *all, char *cmd)
{
    ft_sort_env(envp);
	ft_fill_var_export(all, cmd);
	// ft_print_var_export(all);
}