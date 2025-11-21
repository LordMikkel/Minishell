/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconect_nodes_tokens.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:40:47 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/21 15:08:35 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	reconect_nodes_tokens(t_shell *data, t_node *node, t_token *tokens)
{
	int	i;

	if (!node)
		return ;
	i = 0;
	while (i < data->prompt.n_tokens)
	{
		if (tokens[i].hash == node->token_hash)
		{
			node->token = &tokens[i];
			node->token->id = i;
			break ;
		}
		i++;
	}
	reconect_nodes_tokens(data, node->left, tokens);
	reconect_nodes_tokens(data, node->right, tokens);
}
