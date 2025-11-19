/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_properties.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:02:23 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/16 00:05:23 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	apply_properties(t_shell *data, t_node *node, int mode)
{
	if (node->assig_tmp)
		apply_temp_asig(data, data->prompt.tokens, node);
	if (node->redir)
	{
		if (!apply_redirs(data, node, mode))
		{
			data->exit_code = FAIL;
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
