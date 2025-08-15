/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dolar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:58:46 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/15 23:53:52 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Si el carácter es '$', añade un token de tipo EXPANSION.
	Luego procesa el resto como palabra con is_word.
*/

// void	is_dolar(t_shell *data, t_token *tokens, const char *str, int *i)
// {
// 	if (str[*i] == '$')
// 	{
// 		add_token(tokens, "$", EXPANSION);
// 		(*i)++;
// 		is_word(data, tokens, str, i);
// 	}
// }

void	is_dolar(t_shell *data, t_token *tokens, const char *str, int *i)
{
	int		len;
	int		start;
	char	*expansion;

	if (str[*i] == '$')
	{
		start = *i;
		while (str[*i] != '\0' && !ft_isspace(str[*i]))
			(*i)++;
		len = *i - start;
		if (len > 0)
		{
			expansion = ft_substr(str, start, len);
			if (!expansion)
				exit_error(data, ERR_MALLOC, EXIT_FAILURE);
			add_token(tokens, expansion, EXPANSION);
		}
	}
}
