/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganize_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 22:44:45 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/06 23:38:38 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

static void	void_tokens_at_the_end(t_token *tokens, int n_alloc, int n_tokens)
{
	int	i;

	i = n_tokens;
	while(i < n_alloc)
	{
		tokens[i] = (t_token){0};
		i++;
	}
}

static void	free_tokens_in_range(t_token *tokens, int *range)
{
	int	i;

	i = range[0];
	while( i <= range[1])
	{
		if (is_alloc_type(tokens[i].type))
		{
			if (tokens[i].value)
				free(tokens[i].value);
		}
		i++;
	}
}

void	reorganize_tokens(t_prompt *p, t_token *tokens, int *range, char *res)
{
	int tokens_to_move;
	int tokens_to_remove;

	tokens_to_remove = range[1] - range[0];
	tokens_to_move = p->n_alloc_tokens - range[1] - 1;
	free_tokens_in_range(tokens, range);
	tokens[range[0]].value = res;
	tokens[range[0]].type = WORD;
	ft_memmove(&tokens[range[0] + 1],
			&tokens[range[1] + 1],
			(tokens_to_move * sizeof(t_token)));
	p->n_tokens = p->n_tokens - tokens_to_remove;
	void_tokens_at_the_end(tokens, p->n_alloc_tokens, p->n_tokens);
}
