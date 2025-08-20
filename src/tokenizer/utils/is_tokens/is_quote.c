/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:43:47 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/20 22:23:03 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Detecta comillas simples o dobles y añade el token correspondiente.
	El último caso sería para sustitución de comandos (pendiente).
*/

int	ft_is_dead_space(const char *str, int i)
{
	if (str[i] == ' ' && str[i + 1] != '\'')
		return (0);
	else if (str[i] == ' ' && str[i +1] != '\"')
		return (0);
	return (1);
}

void	is_special_word(t_shell *data, t_token *tokens, const char *str, int *i)
{
	int		len;
	int		start;
	char	*word;

	if (ft_strchr(str + *i + 1, str[*i]))
	{
		start = *i;
		while (str[*i] != '\0' && !ft_is_dead_space(str, *i))
			(*i)++;
		len = *i - start;
		if (len > 0)
		{
			word = ft_substr(str, start, len);
			if (!word)
				exit_error(data, ERR_MALLOC, EXIT_FAILURE);
			add_token(tokens, word, WORD);
		}
	}
	syntax_error(data, ERR_SYNTAX, EXIT_USE, str[*i]);
}

void	is_quote(t_shell *data, t_token *tokens, const char *str, int *i)
{
	char	c;

	c = str[*i];
	if (c == '\'')
	{
		add_token(tokens, "\'", SINGLE_QUOTE);
		is_special_word(data, tokens, str, i);
	}
	else if (c == '\"')
	{
		add_token(tokens, "\"", DOUBLE_QUOTE);
		(*i)++;
	}
	else if (c == '`')
	{
		add_token(tokens, "`", CMD_SUBSTITUTION);
		(*i)++;
	}
}
