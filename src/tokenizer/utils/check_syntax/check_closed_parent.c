/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_closed_parent.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:40:47 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/04 13:36:07 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Comprueba que un paréntesis de cierre tenga un comando antes de la apertura.
	Si no encuentra un paréntesis abierto válido, lanza error de sintaxis.
*/

int	check_close_parent(t_shell *data, t_prompt *prompt, t_token *tokens, int i)
{
	int	content_flag;
	int	j;

	content_flag = 0;
	j = i;
	if (tokens[i].type != PAREN_CLOSE)
		return (SUCCESS);
	prompt->n_parentesis++;
	while (i >= 0 && tokens[i].type != PAREN_OPEN)
	{
		if (tokens[i].type != PAREN_CLOSE)
			content_flag++;
		if (tokens[i].type == PIPE || tokens[i].type == OR
			|| tokens[i].type == AND)
		{
			if (content_flag == 1)
				return (syntax_error(data, ERR_SYNTAX, EXIT_USE, ")"),
					SYNTAX_ERROR);
		}
		i--;
	}
	if (i < 0 || content_flag == 0)
		return (syntax_error(data, ERR_SYNTAX, EXIT_USE, ")"), SYNTAX_ERROR);
	return (SUCCESS);
}
