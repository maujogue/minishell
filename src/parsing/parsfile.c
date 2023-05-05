/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:38:59 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/05 14:46:56 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_charspe(char c)
{
	if (c >= 33 && c <= 47)
		return (1);
	if (c >= 58 && c <= 64)
		return (1);
	if (c >= 91 && c <= 94)
		return (1);
	if (c >= 123 && c <= 125)
		return (1);
	return (0);
}

char	*ft_fillnamefile(char *cmd, int i)
{
	char	*infile;
	int		start;
	int		len;

	len = 0;
	i++;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	// if (cmd[i] == '\0' || ft_charspe(cmd[i]))
	// {
	// 	printf("minishell: syntax error near unexpected token '%c'\n", cmd[i]);
	// 	return (NULL);
	// }
	start = i;
	while (cmd[i] && cmd[i] != ' ')
	{
		i++;
		len++;
	}
	infile = ft_substr(cmd, start, len);
	return (infile);
}

int	ft_lentab(char **tab)
{
	int len;

	len = 0;
	while (tab[len])
	{
		len++;
	}
	// printf("len:%d\n", len);
	return (len);
}

char	**ft_filetodouble(char **tab, char *file)
{
	char	**res;
	int		len;
	int		i;

	i = 0;
	len = ft_lentab(tab);
	res = malloc(sizeof(char *) * (len + 2));
	while (tab[i] != NULL)
	{
		res[i] = ft_strdup(tab[i]);
		i++;
	}
	// printf("i:%d\n", i);
	res[i] = ft_strdup(file);
	res[i + 1] = NULL;
	// printf("*****************************************\n");
	// ft_print_tab(res);
	// printf("*****************************************\n");
	return (res);
}

int	ft__sizeinfile_position(char *cmd, char c)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (cmd[i])
	{
		while (cmd[i] != '|' && cmd[i])
		{
			if (cmd[i] == c)
			{
				size++;
				break ;
			}
			i++;
		}
		i++;
	}
	return (size);
}

// void	ft_fillallfile(t_all *all, char *cmd)
// {
// 	int		i;
// 	char	*infile;
// 	char	**res;
// 	int		sizeinfile_position;

// 	i = 0;
// 	sizeinfile_position = ft__sizeinfile_position(cmd, '<');
// 	printf("sizeinfile_position: %d\n", sizeinfile_position);
// 	while (cmd[i])
// 	{
// 		if (cmd[i - 1] != '<' && cmd[i] == '<' && cmd[i + 1] != '<')
// 		{
// 			if (all->infile2 == NULL)
// 			{
// 				all->infile2 = NULL;
// 				infile = ft_fillnamefile(cmd, i);
// 				res = malloc(sizeof(char *) * 2);
// 				res[0] = infile;
// 				res[1] = NULL;
// 				all->infile2 = res;
// 			}
// 			else
// 			{
// 				infile = ft_fillnamefile(cmd, i);
// 				all->infile2 = ft_filetodouble(all->infile2, infile);
// 			}
// 		}
// 		i++;
// 	}
// }

// void	ft_fillfile(t_all *all, char *cmd)
// {
// 	int	i;
// 	int	is_infile;
// 	int	is_outfile;

// 	i = 0;
// 	is_infile = 0;
// 	is_outfile = 0;
// 	ft_fillallfile(all, cmd);
// 	while (cmd[i])
// 	{
// 		if (cmd[i - 1] != '<' && cmd[i] == '<' && cmd[i + 1] != '<')
// 		{
// 			is_infile = 1;
// 			all->infile = ft_fillnamefile(cmd, i);
// 		}
// 		if (cmd[i - 1] != '>' && cmd[i] == '>' && cmd[i + 1] != '>')
// 		{
// 			is_outfile = 1;
// 			all->outfile = ft_fillnamefile(cmd, i);
// 		}
// 		i++;
// 	}
// 	if (is_infile == 0)
// 		all->infile = NULL;
// 	if (is_outfile == 0)
// 		all->outfile = NULL;
// }

// void	ft_fillfile_heredoc(t_all *all, char *cmd)
// {
// 	ft_fillfile(all, cmd);
// 	ft_fillheredoc(all, cmd);
// 	if (all->infile == NULL)
// 		printf("infile: NULL\n");
// 	else
// 		printf("infile: %s\n", all->infile);
// 	if (all->infile2 == NULL)
// 		printf("infile: NULL\n");
// 	else
// 	{
// 		int i;

//     	i = 0;
// 		while (all->infile2[i] != NULL)
// 		{
// 			printf("%s\n",all->infile2[i]);
// 			i++;
// 		}
// 	}
// 	if (all->outfile == NULL)
// 		printf("outfile: NULL\n");
// 	else
// 		printf("outfile: %s\n", all->outfile);
// 	if (all->heredoc_delim == NULL)
// 		printf("heredoc_delim: NULL\n");
// 	else
// 	{
// 		printf("heredoc_delim: ");
// 		ft_print_tab(all->heredoc_delim);
// 	}	
// 	printf("outfile_append = %d\n", all->outfile_append);
// }
