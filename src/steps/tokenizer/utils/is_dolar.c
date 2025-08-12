/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dolar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:58:46 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/12 16:20:15 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Si el carácter es '$', añade un token de tipo EXPANSION.
	Luego procesa el resto como palabra con is_word.
*/

void	is_dolar(t_shell *data, t_token *tokens, const char *str, int *i)
{
	if (str[0] == '$')
		add_token(tokens, "$", EXPANSION);
	is_word(data, tokens, str, i);
}
