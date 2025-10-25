/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 21:27:37 by migarrid          #+#    #+#             */
/*   Updated: 2025/10/25 21:37:34 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

void	init_exec(t_exec *exec, t_env *env)
{
	exec->original_stdin = dup(STDIN_FILENO);
	exec->original_stdout = dup (STDOUT_FILENO);
	exec->env = env;
}
