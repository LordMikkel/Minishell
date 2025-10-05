/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:36:48 by migarrid          #+#    #+#             */
/*   Updated: 2025/10/05 16:38:44 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ast_builder(t_shell *data, t_token *tokens, int n_tokens)
{
	int	i;

	i = 0;
	if (n_tokens == 0)
		return ;
	data->ast_root = parse_sequence(data, tokens, &i, n_tokens);
}
