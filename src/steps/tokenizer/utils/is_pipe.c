/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:43:50 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/12 16:22:02 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Detecta el operador pipe '|' y añade un token de tipo PIPE.
*/

void	is_pipe(t_token *tokens, char c)
{
	if (c == '|')
		add_token(tokens, "|", PIPE);
}
