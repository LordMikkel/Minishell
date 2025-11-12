/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:40:33 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/09 20:05:55 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Valida un pipe '|' en la línea de comandos.

	- Comprueba que haya un token válido antes y después del pipe.
	  Tokens válidos antes: COMMAND, WORD, BUILT_IN, PAREN_CLOSE, DOUBLE_QUOTE,
	  SINGLE_QUOTE, EXPANSION.
	  Tokens válidos después: COMMAND, WORD, BUILT_IN, PAREN_OPEN, DOUBLE_QUOTE,
	  SINGLE_QUOTE, EXPANSION.
	- Si ambos lados son válidos, incrementa el contador y devuelve SUCCESS.
	- Si no, lanza error de sintaxis.
*/

int	check_pipe(t_shell *data, t_prompt *prompt, t_token *ts, int i)
{
	if (ts[i].type == PIPE)
	{
		if ((i > 0 && i < prompt->n_tokens) && ts[i + 1].type
			&& ts[i - 1].type && ((ts[i + 1].type == COMMAND
					|| ts[i + 1].type == WORD || ts[i + 1].type == BUILT_IN
					|| ts[i + 1].type == WILDCARD
					|| ts[i + 1].type == PAREN_OPEN
					|| ts[i + 1].type == EXPANSION
					|| is_quote_type(ts[i + 1].type)
					|| is_redir_type(ts[i + 1].type)))
				&& (ts[i - 1].type == COMMAND
					|| ts[i - 1].type == BUILT_IN
					|| ts[i - 1].type == WORD
					|| ts[i - 1].type == PAREN_CLOSE
					|| ts[i - 1].type == EXPANSION
					|| ts[i - 1].type == WILDCARD
					|| is_quote_type(ts[i - 1].type)))
		{
			prompt->n_pipes++;
			return (SUCCESS);
		}
		syntax_error(data, ERR_SYNTAX, EXIT_USE, ts[i].value);
		return (SYNTAX_ERROR);
	}
	return (SUCCESS);
}
