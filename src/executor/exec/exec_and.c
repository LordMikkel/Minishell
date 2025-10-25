/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:23:06 by migarrid          #+#    #+#             */
/*   Updated: 2025/10/25 21:56:32 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	exec_and(t_shell *data, t_node *node, t_exec *exec, int mode)
{
	executor_recursive(data, node->left, exec, mode);
	if (data->exit_code == 0 && node->right)
		executor_recursive(data, node->right, exec, mode);
}
