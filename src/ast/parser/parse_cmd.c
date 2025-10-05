/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 20:29:52 by migarrid          #+#    #+#             */
/*   Updated: 2025/10/05 02:16:04 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_node	*parse_cmd(t_token *tokens, int *i, int n_tokens)
{
	t_node	*left;

	left = NULL;
	if (*i < n_tokens && tokens[*i].type
		&& (tokens[*i].type == COMMAND || tokens[*i].type == BUILT_IN))
	{
		left = create_node(&tokens[*i], tokens[*i].type);
		(*i)++;
		// left->args = get_args_for_binary(NULL, &tokens[*i], n_tokens);
		return (left);
	}
	return (left);
}
