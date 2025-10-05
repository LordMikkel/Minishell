/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 20:21:21 by migarrid          #+#    #+#             */
/*   Updated: 2025/10/05 02:11:02 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_node	*parse_pipes(t_token *tokens, int *i, int n_tokens)
{
	t_node	*central;
	t_node	*left;
	t_node	*right;

	right = NULL;
	left = parse_redir(tokens, i, n_tokens);
	if (!left)
		return (NULL);
	if (*i < n_tokens && tokens[*i].type == PIPE)
	{
		right = parse_redir(tokens, i, n_tokens);
		central = create_node(&tokens[*i], PIPE);
		central->left = left;
		central->right = right;
		(*i)++;
		return (central);
	}
	return (left);
}
