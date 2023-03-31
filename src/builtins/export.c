/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:11 by maujogue          #+#    #+#             */
/*   Updated: 2023/03/31 15:29:17 by avaganay         ###   ########.fr       */
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
    // ft_print_export(dup);
	ft_freetab(dup);
}

int	ft_is_arg_export(char	*cmd)
{
	int	i;

	i = 0;
	if (ft_strncmp(cmd, "export\0", 7) == 0)
        return (0);
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
	i--;
	while (cmd[i])
	{
		if (cmd[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	ft_nb_var(char *cmd)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
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
	return (nb);
}

// char	**ft_tabvar(char *cmd)
// {
// 	char	**var;
// 	int		nb;

// 	nb = ft_nb_var(cmd);
// 	var = ft_split(cmd, ' ');
// 	if (!var)
// 		return (NULL);
// 	return (var);
// }

t_listenv	*ft_lstexport_new(char *var)
{
	t_listenv	*new;

	new = malloc(sizeof(t_listenv));
	if (!new)
		return (NULL);
	new->content = var;
	new->next = NULL;
	return (new);
}

t_listenv	*ft_lstexportlast(t_listenv *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstexportadd_back(t_listenv **lst, t_listenv *new)
{
	t_listenv	*back;

	if (!(*lst) || lst == NULL)
	{
		*lst = new;
		return ;
	}
	back = ft_lstexportlast(*lst);
	back->next = new;
}

int	ft_lstexportsize(t_listenv *lst)
{
	t_listenv	*curr;
	int		i;

	curr = lst;
	i = 0;
	while (curr != NULL)
	{
		curr = curr->next;
		i++;
	}
	return (i);
}

void	ft_export_fillkeycontentvar(t_listenv *new, char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
		{
			new->key = ft_substr(var, 0, i);
			new->content = ft_substr(var, i + 1, ft_strlen(var));
			return ;
		}
		if (var[i + 1] == '\0')
		{
			new->key = ft_substr(var, 0, i + 1);
			new->content = NULL;
			return ;
		}
		i++;
	}
}

int	ft_check_name_var(char *var)
{
	int	i;

	i = 0;
	if (var[0] >= '0' && var[0] <= '9')
		return (printf("minishell: export: \'%s\': not a valid identifier\n", var), 1);
	while (var[i] && var[i] != '=')
	{
		if (var[i] >= 33 && var[i] <= 47)
			return (printf("minishell: export: \'%s\': not a valid identifier\n", var), 1);
		i++;		
	}
	return (0);
}

void	ft_export_fill_lstvar(t_listenv **listexport, char **var)
{
	int			i;
	int			n;
	t_listenv	*new;

	i = 1;
	n = 0;
	while (var[n])
		n++;
	n--;
	while(i <= n)
	{
		if (ft_check_name_var(var[i]) == 0)
		{
			new = malloc(sizeof(t_listenv));
			ft_export_fillkeycontentvar(new, var[i]);
			new->next = NULL;
		// printf("-------------\n");
		// printf("%s\n", var[i]);
		// printf("-------------\n");
			ft_lstexportadd_back(listexport, new);
		}
		i++;
	}
}

t_listenv	*ft_fill_var_export(t_listenv *listexport, t_all *all, char *cmd)
{
	char		**var;

	if (ft_is_arg_export(cmd))
	{
		var = ft_split(cmd, ' ');
		if (!var)
			return (NULL);
		// if (all->listexport == NULL)
		// {
		// ft_print_listexport(listexport);
		ft_export_fill_lstvar(&listexport, var);
		// ft_print_listexport(listexport);
		//ft_print_listexport(listexport);
		// }
		// else
		// {
		// 	printf("LISTE REMPLI");
		// 	ft_export_lstempty(&listexport, var);
		// }
		// ft_freetab(var);
	}
	else
		ft_print_listexport(listexport, all);
	return (listexport);
}

// void	ft_print_var_export(t_all *all)
// {
	
// }

void	ft_export(char **envp, t_all *all, char *cmd)
{
    ft_sort_env(envp);
	all->listexport = ft_fill_var_export(all->listexport, all, cmd);
	// ft_print_var_export(all);
}