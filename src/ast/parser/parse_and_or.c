/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_or.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 20:20:29 by migarrid          #+#    #+#             */
/*   Updated: 2025/10/05 16:34:09 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_node	*parse_and_or(t_shell *data, t_token *tokens, int *i, int n_tokens)
{
	t_node	*central;
	t_node	*left;
	t_node	*right;

	right = NULL;
	left = parse_pipes(data, tokens, i, n_tokens);
	if (!left)
		return (NULL);
	if (*i < n_tokens && (tokens[*i].type == AND || tokens[*i].type == OR))
	{
		right = parse_pipes(data, tokens, i, n_tokens);
		central = create_node(data, &tokens[*i], tokens[*i].type);
		central->left = left;
		central->right = right;
		(*i)++;
		return (central);
	}
	return (left);
}
