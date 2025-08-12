/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wildcar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:43:41 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/12 18:18:22 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Detecta comodines '*' o '?' y añade un token de tipo WILDCAR.
*/

void	is_wildcar(t_token *tokens, const char *str, int *i)
{
	char	c;

	c = str[*i];
	if (c == '*')
	{
		add_token(tokens, "*", WILDCAR);
		(*i)++;
	}
	else if (c == '?')
	{
		add_token(tokens, "?", WILDCAR);
		(*i)++;
	}
}
