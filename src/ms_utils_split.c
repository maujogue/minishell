/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:08:55 by avaganay          #+#    #+#             */
/*   Updated: 2023/05/29 11:41:03 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	get_nb_word(char *str, char delimiter)
{
	int	count;
	int	in_quotes;
	int	i;

	i = 0;
	count = 0;
	in_quotes = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
			in_quotes = !in_quotes;
		if (!in_quotes && str[i] == delimiter)
			count++;
		i++;
	}
	return (count + 1);
}

char	*get_next_word(int *index, char *str, char delimiter, int *in_quotes)
{
	char	*word;
	int		start;
	int		end;
	int		i;
	int		word_length;

	i = 0;
	start = *index;
	end = start;
	while (str[end] != '\0')
	{
		if (str[end] == '\"')
			*in_quotes = !(*in_quotes);
		if (!(*in_quotes) && str[end] == delimiter)
			break ;
		end++;
	}
	word_length = end - start;
	word = (char *)malloc((word_length + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (i < word_length)
	{
		word[i] = str[start + i];
		i++;
	}
	word[i] = '\0';
	*index = end + 1;
	return (word);
}

char	**ft_split_with_quote(char *str, char c)
{
	char	**res;
	int		nb_word;
	int		i;
	int		j;
	int		in_quotes;

	in_quotes = 0;
	i = 0;
	j = 0;
	if (!str)
		return (0);
	nb_word = get_nb_word(str, c);
	res = ft_calloc(nb_word + 1, sizeof(char *));
	if (!res)
		return (NULL);
	while (i < nb_word)
	{
		res[i] = get_next_word(&j, str, c, &in_quotes);
		if (!res[i++])
		{
			free_array(res);
			return (NULL);
		}
	}
	return (res[i] = 0, res);
}
