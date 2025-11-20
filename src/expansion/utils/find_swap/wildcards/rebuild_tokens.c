/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:43:47 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/20 20:37:23 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../../inc/minishell.h"

void	adjust_id(t_token *tokens, int n_tokens)
{
	int	j;

	j = 0;
	while (j < n_tokens)
	{
		tokens[j].id = j;
		j++;
	}
}

void	rebuild_tokens(t_shell *data, t_token *token, char **dirs, int n_dirs)
{
	int	result;

	result = reorder_tokens(data, token, n_dirs, dirs);
	if (result == ERROR)
	{
		ft_free_str_array(&dirs);
		exit_error(data, ERR_MALLOC, EXIT_FAILURE);
	}
	adjust_id(data->prompt.tokens, data->prompt.n_tokens);
}
