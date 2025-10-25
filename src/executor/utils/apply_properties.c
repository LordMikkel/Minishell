/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_properties.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:02:23 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/10/15 19:37:16 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	apply_properties(t_shell *data, t_node *node, t_env *env, int mode)
{
	if (node->assig_tmp)
	{
		printf("IT HAS ASSIG_TEMP\n\n");
		apply_temp_asig(data, data->prompt.tokens, node, env);
	}
	//if (node->redir);
	//	if (!apply_redirs(data, node, mode))
	//		return (FAILURE);
	return (SUCCESS);
}
