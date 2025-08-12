/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_scape.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:43:43 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/12 16:22:55 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Detecta carácter de escape '\' y añade un token de tipo SCAPE.
*/

void	is_scape(t_token *tokens, char c)
{
	if (c == '\\')
		add_token(tokens, "\\", SCAPE);
}
