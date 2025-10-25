/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_word_to_asignation.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:15:55 by migarrid          #+#    #+#             */
/*   Updated: 2025/10/25 20:16:48 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
 * Recorre todos los tokens y transforma aquellos que cumplen con la sintaxis
 * de asignación.
 *
 * Lógica por fases:
 * - En INITIAL_PHASE:
 *     - Si el token tiene tipo WORD, COMMAND o ASIGNATION y pasa el filtro
 *       de sintaxis (`check_asignation_syntax`), se marca como tipo ASIGNATION.
 *
 * - En FINAL_PHASE:
 *     - Solo se evalúan los tokens que ya fueron marcados como ASIGNATION.
 *     - Si el token falla el filtro externo (`check_externs_syntax`),
 *       se revierte su tipo a WORD.
 *
 * Resultado:
 * - Un token solo se considera definitivamente como ASIGNATION si pasa
 *    ambos filtros.
 * - Si no pasa el segundo filtro, se considera implícitamente que
 *   el primero fue incorrecto o insuficiente.
*/

void	transform_word_to_asignation(t_shell *data, t_token *tokens, int phase)
{
	int	i;

	i = 0;
	while (i < data->prompt.n_tokens)
	{
		if (tokens[i].type != WORD && tokens[i].type != ASIGNATION
			&& tokens[i].type != COMMAND)
		{
			i++;
			continue ;
		}
		if (phase == INITIAL_PHASE)
		{
			if (check_asignation_syntax(&tokens[i], INDIFERENT))
			{
				// printf("Recongnize as ASIG\n\n");
				tokens[i].type = ASIGNATION;
			}
		}
		else if (phase == FINAL_PHASE && tokens[i].type == ASIGNATION)
		{
			if (!check_externs_syntax(data, tokens, &tokens[i], INDIFERENT))
				tokens[i].type = WORD;
		}
		i++;
	}
}
