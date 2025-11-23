/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:18:26 by migarrid          #+#    #+#             */
/*   Updated: 2025/11/23 17:55:13 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

int	extract_key(t_shell *data, t_token *token, char **key_to_find, int phase)
{
	int	found;
	int	match;
	int	result;
	int	type;

	type = INDIFERENT;
	found = FALSE;
	match = copy_key(token->value, key_to_find, &type);
	if (!match)
		return (FAILURE);
	if (type == DOLLAR)
		found = find_key_in_lst(data, token, key_to_find, phase);
	else
		found = is_it_tilde(data, token, key_to_find);
	if (found == ERROR)
		return (ERROR);
	if (found)
		token->type = WORD;
	if (!found && phase == FINAL_PHASE)
	{
		result = expand_empty_str(data, token, key_to_find, type);
		if (result == REPLACED)
			token->type = WORD;
	}
	return (SUCCESS);
}
