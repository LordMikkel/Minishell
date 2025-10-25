/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_III.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 21:43:11 by migarrid          #+#    #+#             */
/*   Updated: 2025/10/25 21:52:36 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
	Elimina las variables `TEMP_ASIGNATION` del ciclo. Elimina solo los que se
	ejecuten/afecten en el shell padre/global, ya que los que se ejecuten
	en child procesess se borraran solos.
*/

void	clean_temp_variables(t_shell *d, t_env *e, t_token *t, t_node *node)
{
	my_clean_unset(d, e, t, node->arg_types);
}

void	clean_fd(t_exec *exec)
{
	close(exec->original_stdin);
	close(exec->original_stdout);
}
