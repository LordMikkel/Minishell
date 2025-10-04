/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pase_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 20:24:05 by migarrid          #+#    #+#             */
/*   Updated: 2025/10/04 21:40:02 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_node	*parse_subshell(t_token *tokens, int *i, int n_tokens)
{
	t_node *central;
	t_node *left;

	if (i < n_tokens && tokens[*i].type == PAREN_OPEN)
	{
		central = create_node(&tokens[*i], SUBSHELL);
		if (i < n_tokens)
			(*i)++;
		left = parse_sequence(tokens, i, n_tokens);
		if (i < n_tokens)
			(*i)++;
		central->left = left;
		return (central);
	}
	central = parse_cmd(tokens, i, n_tokens);
	return (central);
}
