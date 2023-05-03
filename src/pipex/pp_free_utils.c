/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maujogue <maujogue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:31:57 by maujogue          #+#    #+#             */
/*   Updated: 2023/05/03 14:41:42 by maujogue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	write_error(char *bash, char *str, char *message)
{
	write(2, bash, ft_strlen(bash));
	write(2, str, ft_strlen(str));
	write(2, message, ft_strlen(message));
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
		tab = NULL;
	}
}

void	free_triple_array(char ***tab)
{
	int	i;

	i = -1;
	if (tab != NULL)
	{
		while (tab[++i])
			free_array(tab[i]);
		free(tab);
		tab = NULL;
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
		free_array(all->parspipex[i]->opt2);
		free(all->parspipex[i]->cmd);
		all->parspipex[i]->tabfinal = NULL;
		all->parspipex[i]->arg = NULL;
		all->parspipex[i]->opt2 = NULL;
		all->parspipex[i]->cmd = NULL;
		i++;
	}
	free(all->parspipex);
	all->parspipex = NULL;
}

void	free_exit_all_pipex(t_all *all)
{
	// free_array(all->infile2);
	// free(all->infile_position);
	// free(all->outfile);
	// free_array(all->heredoc_delim);
	// all->infile_position = NULL;
	// all->infile2 = NULL;
	// all->outfile = NULL;
	// all->heredoc_delim = NULL;
	free_listenv(all->listenv);
	free_listenv(all->listexport);
	free_parse_tab(all);
}

void	free_exit(t_all *all, t_pip *pip, int i, char *message)
{
	free_array(pip->cmd); //crashes when input file doesn't exist
	free(pip->path_cmd);
	free_array(pip->envp);
	free_triple_array(pip->tab_cmd);
	free(pip->path);
	free_exit_all_pipex(all);
	free(pip->fds);
	pip->cmd = NULL;
	pip->path_cmd = NULL;
	pip->envp = NULL;
	pip->tab_cmd = NULL;
	pip->path = NULL;
	pip->fds = NULL;
	if (i != 0)
		write(1, message, ft_strlen(message));
}
