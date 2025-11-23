/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_is_double_quote_I.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:34:54 by migarrid          #+#    #+#             */
/*   Updated: 2025/11/23 00:50:16 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

void	clean_quote_until_slash_d(char *word, char *clean_word, char quote)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (word[j])
	{
		if (word[j] == '\\' && word[j + 1] == quote)
		{
			clean_word[k++] = word[j + 1];
			j += 2;
		}
		else if (word[j] != quote)
		{
			clean_word[k++] = word[j];
			j++;
		}
		else
			j++;
	}
	clean_word[k] = '\0';
}

char	*clean_slash_expan_d(t_shell *data, char *word, int len, char slash)
{
	int		j;
	int		k;
	char	*clean_word;

	j = 0;
	k = 0;
	if (ft_strchr(word, slash))
	{
		clean_word = ft_calloc(len + 1, sizeof(char));
		if (!clean_word)
			return (free(word), exit_error(data, ERR_MALLOC, EXIT_FAIL), NULL);
		while (word[j])
		{
			if (word[j] == '\\' && word[j + 1] == '$')
			{
				clean_word[k++] = word[j + 1];
				j += 2;
			}
			else
				clean_word[k++] = word[j++];
		}
		clean_word[k] = '\0';
		return (free(word), clean_word);
	}
	return (word);
}

void	process_slash_char_quotes_d(char *word, char *clean_word, int *flag)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (word[j])
	{
		if (word[j] == '\\')
		{
			if (word[j + 1] == '$')
			{
				clean_word[k++] = word[j + 1];
				*flag = TRUE;
				j += 2;
			}
			else if (is_escapable_char(word[j + 1]))
			{
				clean_word[k++] = word[j + 1];
				j += 2;
			}
			else
				clean_word[k++] = word[j++];
		}
		else
			clean_word[k++] = word[j++];
	}
	clean_word[k] = '\0';
}

char	*cleanner_slash_quotes_d(t_shell *data, char *word, int len, int *flag)
{
	char	*clean_word;

	if (ft_strchr(word, '\\'))
	{
		clean_word = ft_calloc(len + 1, sizeof(char));
		if (!clean_word)
		{
			free(word);
			exit_error(data, ERR_MALLOC, EXIT_FAILURE);
		}
		process_slash_char_quotes_d(word, clean_word, flag);
		free(word);
		return (clean_word);
	}
	return (word);
}
