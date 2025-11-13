/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:24:58 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/13 17:53:36 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../../inc/minishell.h"

static void	reconect_tokens_and_nodes(t_shell *data, t_token *tokens, int phase)
{
	if (phase == FINAL_PHASE)
		reconect_nodes_tokens(data, data->ast_root, data->prompt.tokens);
}

int	expand_wildcards(t_shell *dat, t_prompt *prompt, t_token *tokens, int phase)
{
	int	i;

	i = 0;
	while (i < prompt->n_tokens)
	{
		if (tokens[i].type == WILDCARD)
		{
			if (phase == FINAL_PHASE && is_delimiter_type(tokens[i].type))
				return (SUCCESS);
			if (((i + 1) < prompt->n_tokens) && (tokens[i + 1].type == NO_SPACE)) //hay una expansion que no se proceso porque aun no existe su valor
			{
				i++;
				continue ;
			}
			if (!process_wildcard(dat, &tokens[i]))
			{
				i++;
				continue ;
			}
			tokens = dat->prompt.tokens;
			reconect_tokens_and_nodes(dat, tokens, phase);
		}
		i++;
	}
	return (SUCCESS);
}
