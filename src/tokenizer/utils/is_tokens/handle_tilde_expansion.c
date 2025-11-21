/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tilde_expansion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:58:59 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/21 19:04:24 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Crea un token de tipo EXPANSION desde la str.
	Limpia '{' y '}' dentro de la expansión.
	Finalmente añade el token al prompt.
*/

static void	make_expan_token(t_shell *data, const char *str, int start, int *i)
{
	int		len;
	char	*expansion;

	len = *i - start;
	if (len > 0)
	{
		expansion = ft_substr(str, start, len);
		if (!expansion)
			exit_error(data, ERR_MALLOC, EXIT_FAILURE);
		expansion = cleanner_exp(data, expansion, len, '{');
		expansion = cleanner_exp(data, expansion, len, '}');
		if (ft_strcmp(expansion, "$") == 0)
			add_token(data, &data->prompt, expansion, WORD);
		else
			add_token(data, &data->prompt, expansion, EXPANSION);
	}
}

static void	aux_check(t_shell *data, const char *str, int *i, int *found)
{
	if (str[*i] == '\'' || str[*i] == '\"')
	{
		add_token(data, &data->prompt, "", NO_SPACE);
		add_token(data, &data->prompt, "\'", SINGLE_QUOTE);
		*found = TRUE;
	}
}

static void	aux_check_2(t_shell *data, const char *str, int len, int start)
{
	char	*word;

	word = NULL;
	word = ft_substr(str, start, len);
	if (!word)
		exit_error(data, ERR_MALLOC, EXIT_FAILURE);
	add_token(data, &data->prompt, word, WORD);
}

void	handle_tilde_expansion(t_shell *d, t_prompt *p, const char *str, int *i)
{
	int		start;
	int		len;
	int		found;

	start = *i;
	found = FALSE;
	(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
		(*i)++;
	make_expan_token(d, str, start, i);
	if (str[*i] != '\0' && !ft_isspace(str[*i]))
	{
		start = *i;
		aux_check(d, str, i, &found);
		while (str[*i] != '\0' && !ft_isspace(str[*i]))
			(*i)++;
		if (*i > start)
		{
			len = *i - start;
			if (!found)
				add_token(d, p, "", NO_SPACE);
			aux_check_2(d, str, len, start);
		}
	}
}
