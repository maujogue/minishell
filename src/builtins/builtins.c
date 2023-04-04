/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:15:34 by avaganay          #+#    #+#             */
/*   Updated: 2023/04/04 16:07:50 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_strncmpecho(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	// if (ft_strcmp(s1, "echo \0") == 0)
	// 	return(printf("\n"), 1);
	if (n == 0)
		return (n);
	while (s1[i] == '\'' || s1[i] == '\"')
	{
		n++;
		i++;
	}
	while ((s1[i] == s2[j]) && s1[i] && (i < n - 1) && s1[i] != ' ')
	{
		i++;
		j++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}

int	ft_strncmpexport(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	// if (ft_strcmp(s1, "echo \0") == 0)
	// 	return(printf("\n"), 1);
	if (n == 0)
		return (n);
	while (s1[i] == '\'' || s1[i] == '\"')
	{
		n++;
		i++;
	}
	while ((s1[i] == s2[j]) && s1[i] && (i < n - 1) && s1[i] != ' ')
	{
		i++;
		j++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}

char	*ft_clean_cmd(char *cmd)
{
	char	*res;
	int		i;
	int		len;
	int		j;
	
	i = 0;
	j = 0;
	len = 0;
	while (cmd[i])
	{
		if (cmd[i] != '"' && cmd[i] != '\'')
			len++;
		i++;	
	}
	res = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != '"' && cmd[i] != '\'')
		{
			res[j] = cmd[i];
			j++;
		}
		i++;	
	}
	res[j] = '\0';
	return (res);
}


void    ft_builtins(char *cmd, t_all *all, char **envp)
{
	char	**tabcmd;

	if (cmd == NULL || cmd[0] == '\0')
		return ;
	tabcmd = ft_split(cmd, ' ');
	tabcmd[0] = ft_clean_cmd(tabcmd[0]);
	// printf("tabcmd[0]%s",tabcmd[0]);
    if (ft_strncmp(cmd, "exit", 4) == 0)
        ft_exit(0);
    else if (ft_strncmp(cmd, "clear", 5) == 0)
		clear_history();
	else if (ft_strncmpecho(tabcmd[0], "echo\0", 5) == 0)
		ft_echo(all, cmd);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		ft_print_listenv(all, cmd);
	// else if (ft_strncmp(cmd, "export", 6) == 0)
	// 	ft_export(envp, all, cmd);
	else if (ft_strncmpexport(tabcmd[0], "export\0", 7) == 0)
		ft_export(envp, all, cmd);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		ft_unset(all->listenv, cmd);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		ft_cd(tabcmd[1]);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		ft_pwd();
	else
		printf("%s: command not found\n", tabcmd[0]);
	//ft_freetab(tabcmd);
}