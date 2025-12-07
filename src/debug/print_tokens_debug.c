/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens_debug.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: king <king@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:50:14 by migarrid          #+#    #+#             */
/*   Updated: 2025/12/07 21:19:08 by king             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

const char	*g_type_names[] = {
	"START",
	"WORD",
	"GROUP",
	"PIPE",
	"REDIR_INPUT",
	"REDIR_OUTPUT",
	"REDIR_APPEND",
	"REDIR_HEREDOC",
	"COMMAND",
	"SCAPE",
	"BUILT_IN",
	"SEMICOLON",
	"SINGLE_QUOTE",
	"DOUBLE_QUOTE",
	"CMD_SUBSTITUTION",
	"PAREN_OPEN",
	"PAREN_CLOSE",
	"WILDCARD",
	"EXPANSION",
	"ASIGNATION",
	"BACKGROUND",
	"AND",
	"OR",
	"EXPAN_VALUE",
	"EXPAN_CMD",
	"NO_SPACE",
	"LOCAL",
	"ENV",
	"DELETE",
	"EXP",
	"INDIFERENT",
	"PLUS_ASIGNATION",
	"TEMP_ASIGNATION",
	"FILENAME",
	"DELIMITER",
	"SUBSHELL",
	"SHELL",
	"TEMP_PLUS_ASIGNATION",
	"DONT_ELIMINATE",
	"SCRIPT_ARG",
};

void	print_tokens_debug(t_prompt *prompt)
{
	int	i;

	i = 0;
	printf("------------------------------------------------\n");
	printf("n_tokens: %d\n\n", prompt->n_tokens);
	while (i < prompt->n_tokens)
	{
		if (prompt->tokens[i].value)
			printf("Token [%d]: '%s' (type: %s) - token id: %d - hash: %d\n",
				i, prompt->tokens[i].value,
				g_type_names[prompt->tokens[i].type],
				prompt->tokens[i].id, prompt->tokens[i].hash);
		i++;
	}
}
