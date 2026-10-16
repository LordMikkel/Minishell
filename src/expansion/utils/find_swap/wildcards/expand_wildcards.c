/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:24:58 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/21 19:43:14 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../../inc/minishell.h"

static void	reconect_tokens_and_nodes(t_shell *data, int phase)
{
	if (phase == FINAL_PHASE)
		reconect_nodes_tokens(data, data->ast_root, data->prompt.tokens);
}

int	expand_wildcards(t_shell *data, t_prompt *p, t_token *tokens, int phase)
{
	int	i;
	int	n;

	i = 0;
	while (i < p->n_tokens)
	{
		n = 0;
		if (tokens[i].type == WILDCARD
			&& !((i + 1) < p->n_tokens && tokens[i + 1].type == NO_SPACE))
			n = process_wildcard(data, &tokens[i]);
		if (n)
		{
			tokens = data->prompt.tokens;
			reconect_tokens_and_nodes(data, phase);
			i += n;
		}
		else
			i++;
	}
	return (SUCCESS);
}
