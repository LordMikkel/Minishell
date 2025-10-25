/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:18:26 by migarrid          #+#    #+#             */
/*   Updated: 2025/10/25 21:13:47 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

int	extract_key(t_shell *data, t_token *token, char **key_to_find, int phase)
{
	int	found;
	int	match;
	int	result;

	found = FALSE;
	match = copy_key(token->value, key_to_find);
	// printf("MATCH: %d\n\n", match);
	if (!match)
		return (FAILURE);
	found = find_key_in_lst(data, token, key_to_find);
	if (found == ERROR)
		return (ERROR);
	if (found)
		token->type = WORD;
	if (!found && phase == FINAL_PHASE)
	{
		result = expand_empty_str(data, token, key_to_find);
		if (result == REPLACED)
			token->type = WORD;
	}
	return (SUCCESS);
}
