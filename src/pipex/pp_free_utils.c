/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathisaujogue <mathisaujogue@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:31:57 by maujogue          #+#    #+#             */
/*   Updated: 2023/04/14 09:11:31 by mathisaujog      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	write_error(char *str)
{
	write(2, str, ft_strlen(str));
}

void	free_array(char **tab)
{
	int	i;

	i = -1;
	if (tab != NULL)
	{
		while (tab[++i])
			free(tab[i]);
		free(tab);
	}
}

void	free_fd(void)
{
	int	fd;

	fd = 0;
	while (close(fd) != -1)
		fd++;
	fd = 5;
	while (close(fd) != -1)
		fd++;
}

void	free_triple_array(char ***tab)
{
	int	i;

	i = -1;
	if (tab != NULL)
	{
		while (tab[++i])
			free_array(tab[i]);
	}
}

void	ft_lstclear_env(t_listenv *lst)
{
	t_listenv	*temp;

	if (!lst)
		return ;
	while (lst != NULL)
	{
		temp = (lst)->next;
		free(lst->key);
		free(lst->content);
		free(lst->next);
		lst = temp;
	}
	lst = NULL;
}



void	free_parse_tab(t_all *all)
{
	int	i;

	i = 0;
	while (all->parspipex[i])
	{
		free_array(all->parspipex[i]->tabfinal);
		free_array(all->parspipex[i]->arg);
		free(all->parspipex[i]->opt);
		free(all->parspipex[i]->cmd);
		i++;
	}
}

void	free_exit_all_pipex(t_all *all)
{
	free(all->infile);
	free(all->outfile);
	all->infile = NULL;
	all->outfile = NULL;
	// free_parse_tab(all);
}

void	free_exit(t_all *all, t_pip *pip, int i, char *message)
{
	// free_array(pip->cmd1); crashes when input file doesn't exist
	// free(pip->path_cmd1);
	// pip->cmd1 = NULL;
	// pip->path_cmd1 = NULL;
	free_array(pip->envp);
	free_triple_array(pip->tab_cmd);
	free(pip->path);
	free_exit_all_pipex(all);
	free(pip->fds);
	if (i != 0)
		write(1, message, ft_strlen(message));
}
