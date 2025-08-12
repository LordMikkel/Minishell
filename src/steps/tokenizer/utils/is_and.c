/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:44:05 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/12 18:37:01 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Detecta el operador lógico '&&' y añade un token de tipo AND.
	Avanza el índice para no volver a procesar el token.
*/

void	is_and(t_token *tokens, const char *str, int *i)
{
	if (!ft_strncmp(str + *i, "&&", 2))
	{
		add_token(tokens, "&&", AND);
		(*i)++;
		(*i)++;
	}
}
