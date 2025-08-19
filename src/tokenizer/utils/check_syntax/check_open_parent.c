/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_open_parent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:40:41 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/08/19 22:40:44 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Comprueba que un paréntesis de apertura tenga un comando antes de cerrarse.
	Si no encuentra un cierre válido, lanza un error de sintaxis.
*/

int	check_open_parent(t_shell *data, t_prompt *prompt, t_token *tokens, int i)
{
	int	content_flag;

	content_flag = 0;
	if (tokens[i].type == PAREN_OPEN)
	{
		if (i > 0 && tokens[i - 1].type && (tokens[i - 1].type == PAREN_CLOSE || tokens[i - 1].type == COMMAND || tokens[i - 1].type == WORD || tokens[i - 1].type == BUILT_IN))
		{
			syntax_error(data, ERR_SYNTAX, EXIT_USE, "(");
			return (SYNTAX_ERROR);
		}
		while (i < prompt->n_tokens)
		{
			if (tokens[i].type != PAREN_OPEN && tokens[i].type != PAREN_CLOSE)
				content_flag++;
			if (tokens[i].type == PAREN_CLOSE && i > 1 && content_flag >= 1)
			{
				prompt->n_parentesis++;
				return (SUCCESS);
			}
			i++;
		}
		syntax_error(data, ERR_SYNTAX, EXIT_USE, "(");
		return (SYNTAX_ERROR);
	}
	return (SUCCESS);
}
