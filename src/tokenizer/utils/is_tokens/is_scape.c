/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_scape.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:43:43 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/21 20:44:49 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Detecta carácter de escape '\' y añade un token de tipo SCAPE.
*/

void	is_scape(t_shell *data, t_token *tokens, const char *str, int *i)
{
	if (str[*i] == '\\' && str[*i + 1] == '\0')
	{
		add_token(tokens, "\\", SCAPE);
		(*i)++;
	}
	else if (str[*i] == '\\' && str[*i + 1])
		is_word(data, tokens, str, i);
}
