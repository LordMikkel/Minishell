/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_or_and.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:39:47 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/14 23:15:03 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Comprueba que los operadores '||' y '&&' tengan un comando válido a ambos
	lados. Si no se cumple, lanza un error de sintaxis.
*/

int	check_or_and(t_shell *data, t_prompt *prompt, t_token *tokens, int i)
{
	if (tokens[i].type == OR || tokens[i].type == AND)
	{
		if ((i > 0 && i < prompt->n_tokens)
			&& (tokens[i + 1].type && tokens[i - 1].type))
		{
			if (tokens[i].type == AND)
				prompt->n_and++;
			else if (tokens[i].type == OR)
				prompt->n_or++;
			return (SUCCESS);
		}
		syntax_error(data, ERR_SYNTAX, EXIT_USE, tokens[i].value);
		return (SYNTAX_ERROR);
	}
	return (SUCCESS);
}
