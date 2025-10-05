/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 20:22:00 by migarrid          #+#    #+#             */
/*   Updated: 2025/10/05 02:11:05 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_node	*parse_redir(t_token *tokens, int *i, int n_tokens)
{
	t_node	*central;
	t_node	*left;
	t_node	*right;

	right = NULL;
	left = parse_subshell(tokens, i, n_tokens);
	if (!left)
		return (NULL);
	if (*i < n_tokens && is_redir_type(tokens[*i].type))
	{
		right = parse_subshell(tokens, i, n_tokens);
		central = create_node(&tokens[*i], tokens[*i].type);
		central->left = left;
		central->right = right;
		(*i)++;
		return (central);
	}
	return (left);
}
