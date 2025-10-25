/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_semicolon.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:23:22 by migarrid          #+#    #+#             */
/*   Updated: 2025/10/25 21:26:48 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	exec_semicolon(t_shell *data, t_node *node, t_exec *exec, int mode)
{
	if (node->left)
		executor_recursive(data, node->left, exec, mode);
	if (node->right)
		executor_recursive(data, node->right, exec, mode);
}
