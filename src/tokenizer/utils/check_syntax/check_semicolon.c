/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_semicolon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 03:53:16 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/03 00:44:51 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

int	check_semicolon(t_shell *data, t_prompt *prompt, t_token *tokens, int i)
{
	if (tokens[i].type == SEMICOLON)
	{
		if (i == 0)
		{
			syntax_error(data, ERR_SYNTAX, EXIT_USE, ";");
			return (SYNTAX_ERROR);
		}
		if (!(tokens[i - 1].type == COMMAND
				|| tokens[i - 1].type == WORD
				|| tokens[i - 1].type == BUILT_IN
				|| tokens[i + 1].type == EXPANSION
				|| tokens[i - 1].type == WILDCAR
				|| tokens[i - 1].type == DOUBLE_QUOTE))
		{
			syntax_error(data, ERR_SYNTAX, EXIT_USE, tokens[i - 1].value);
			return (SYNTAX_ERROR);
		}
	}
	return (SUCCESS);
}
