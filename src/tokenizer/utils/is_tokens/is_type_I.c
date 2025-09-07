/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:48:00 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/06 22:41:02 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

int	is_cmd_type(int type)
{
	if (type == COMMAND || type == BUILT_IN || type == WORD)
		return (1);
	return (0);
}

int	is_quote_type(int type)
{
	if (type == DOUBLE_QUOTE || type == SINGLE_QUOTE)
		return (1);
	return (0);
}

int	is_redir_type(int type)
{
	if (type == REDIR_APPEND || type == REDIR_OUTPUT)
		return (1);
	return (0);
}

int	is_delimiter_type(int type)
{
	if (type == PIPE || type == SEMICOLON || type == AND || type == OR)
		return (1);
	return (0);
}

int is_alloc_type(int type)
{
	if (type == WORD || type == BUILT_IN || type == COMMAND || type == WILDCAR
			|| type == REDIR_APPEND || type == REDIR_HEREDOC
			|| type == REDIR_INPUT || type == REDIR_OUTPUT
			|| type == EXPANSION)
		return (1);
	return(0);
}
