/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:40:29 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/08/21 21:13:32 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Verifica que paréntesis, comillas y caracteres de escape estén en número
	par y correctamente emparejados.
*/

int	check_quotes(t_shell *data, t_prompt *prompt, t_token *tokens, int i)
{
	if (tokens[i].type == DOUBLE_QUOTE)
	{
		prompt->n_double_quotes++;
		while (i < prompt->n_tokens)
		{
			if (tokens[i].type == DOUBLE_QUOTE)
				return (SUCCESS);
			i++;
		}
		syntax_error(data, ERR_SYNTAX, EXIT_USE, "\"");
		return (SYNTAX_ERROR);
	}
	else if (tokens[i].type == SINGLE_QUOTE)
	{
		prompt->n_single_quotes++;
		while (i < prompt->n_tokens)
		{
			if (tokens[i].type == SINGLE_QUOTE)
				return (SUCCESS);
			i++;
		}
		syntax_error(data, ERR_SYNTAX, EXIT_USE, "\'");//HEARDOC
		return (SYNTAX_ERROR);
	}
	return (SUCCESS);
}
