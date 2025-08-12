/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dolar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:58:46 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/12 18:21:10 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Si el carácter es '$', añade un token de tipo EXPANSION.
	Luego procesa el resto como palabra con is_word.
*/

void	is_dolar(t_shell *data, t_token *tokens, const char *str, int *i)
{
	if (str[*i] == '$')
	{
		add_token(tokens, "$", EXPANSION);
		(*i)++;
		is_word(data, tokens, str, i);
	}
}
