/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:07:11 by maujogue          #+#    #+#             */
/*   Updated: 2023/04/14 15:10:54 by avaganay         ###   ########.fr       */
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
	int		i;
	int		j;

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
	dup[i - 1] = NULL;
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

char	*ft_substrexportkey(char const *s, unsigned int start, size_t len)
{
	char			*src;
	char			*str;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = start;
	src = (char *)s;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			start--;
		i++;
	}
	i = 0;
	if (len > (ft_strlen(s) - start))
		len = (ft_strlen(s) - start);
	if (len > ft_strlen(s) || start >= ft_strlen(src) || s == 0 || len <= 0)
		len = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (!(str))
		return (0);
	while (j < start + len && src[i] && src[j] != '=')
	{
		if (src[j] != '\"' && src[j] != '\'' && src[j] != '=')
		{
			str[i] = src[j];
			i++;
		}
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substrexportcontent(char const *s, unsigned int start, size_t len)
{
	char			*src;
	char			*str;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = start;
	src = (char *)s;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '"')
			start--;
		i++;
	}
	i = 0;
	if (len > (ft_strlen(s) - start))
		len = (ft_strlen(s) - start);
	if (len > ft_strlen(s) || start >= ft_strlen(src) || s == 0 || len <= 0)
		len = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (!(str))
		return (0);
	while (j < start + len && src[i])
	{
		if (src[j] != '\"')
		{
			str[i] = src[j];
			i++;
		}
		j++;
	}
	str[i] = '\0';
	return (str);
}

void	ft_export_fillkeycontentvar(t_listenv *new, char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
		{
			new->key = ft_substrexportkey(var, 0, i);
			new->content = ft_substrexportcontent(var, i + 1, ft_strlen(var));
			return ;
		}
		if (var[i + 1] == '\0')
		{
			new->key = ft_substrexportkey(var, 0, i + 1);
			new->content = NULL;
			return ;
		}
		i++;
	}
}

int	ft_check_name_var(char *var)
{
	int	i;
	int len;

	len = ft_strlen(var);
	i = 0;
	if (var[0] >= '0' && var[0] <= '9')
		return (printf("minishell: export: \'%s\': not a valid identifier\n", var), 1);
	while (var[i] && var[i] != '=' && i <= len)
	{
		if (var[i] >= 33 && var[i] <= 47 && var[i] != 34 && var[i] != 39)
			return (printf("minishell: export: \'%s\': not a valid identifier\n", var), 1);
		i++;		
	}
	return (0);
}
char	*ft_fillkeyvar(char	*var)
{
	int		i;
	char	*res;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
		{
			res = ft_substr(var, 0 , i);
			return (res);
		}
		i++;
	}
	return (var);
}

int	ft_check_double_var(char *var, t_listenv *listexport, t_all **all)
{
	t_listenv	*tmp;
	char		*keyvar;
	
	tmp = listexport;
	keyvar = ft_fillkeyvar(var);
	while (listexport)
	{
		if (ft_strcmp(keyvar, listexport->key) == 0)
			return (1);
		listexport = listexport->next;
	}
	listexport = tmp;
	tmp = (*all)->listenv;
	while ((*all)->listenv)
	{
		if (ft_strcmp(keyvar, (*all)->listenv->key) == 0)
			return (1);
		(*all)->listenv = (*all)->listenv->next;
	}
	(*all)->listenv = tmp;
	return (0);
}

void	ft_replace_double(char *var, t_listenv *listexport, t_all **all)
{
	t_listenv	*tmp;
	int			i;
	
	(void)all;
	i = 0;
	tmp = listexport;
	while (listexport)
	{
		if (ft_strcmp(var, listexport->key) == 0)
		{
			while (var[i] != '=' && var[i])
				i++;
			if (var[i])
			{
				printf("REPLACE NO =\n");
				listexport->content = ft_substrexportcontent(var, i, ft_strlen(var));
				listexport = tmp;
			}
			return ;
		}
		listexport = listexport->next;
	}
	listexport = tmp;
}

void	ft_export_fill_lstvar(t_listenv **listexport, char **var, t_all **all)
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
			if (ft_check_double_var(var[i], *listexport, all) == 1)
			{
				printf("DOUBLE FIND\n");
				ft_replace_double(var[i], *listexport, all);
			}
			else
			{
				new = malloc(sizeof(t_listenv));
				ft_export_fillkeycontentvar(new, var[i]);
				new->next = NULL;
				ft_lstexportadd_back(listexport, new);
			}
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
		ft_export_fill_lstvar(&listexport, var, &all);
	}
	else
		ft_print_listexport(listexport, all);
	return (listexport);
}

void	ft_export(char **envp, t_all *all, char *cmd)
{
	ft_sort_env(envp);
	all->listexport = ft_fill_var_export(all->listexport, all, cmd);
}