/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:46:57 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/08 13:53:28 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	**ft_dup_env(char **envp)
{
	char	**dup;
	int		count;

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
	free_array(dup);
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
