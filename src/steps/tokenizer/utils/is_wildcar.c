/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wildcar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:43:41 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/12 16:23:11 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Detecta comodines '*' o '?' y añade un token de tipo WILDCAR.
*/

void	is_wildcar(t_token *tokens, char c)
{
	if (c == '*')
		add_token(tokens, "*", WILDCAR);
	else if (c == '?')
		add_token(tokens, "?", WILDCAR);
}
