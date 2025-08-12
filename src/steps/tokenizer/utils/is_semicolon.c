/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_semicolon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:48:30 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/12 16:23:04 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Detecta punto y coma ';' y añade un token de tipo SEMICOLON.
*/

void	is_semicolon(t_token *tokens, char c)
{
	if (c == ';')
		add_token(tokens, ";", SEMICOLON);
}
