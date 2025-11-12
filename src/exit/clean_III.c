/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_III.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 21:43:11 by migarrid          #+#    #+#             */
/*   Updated: 2025/11/05 11:59:11 by davdiaz-         ###   ########.fr       */
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

void	clean_builtins_selection(t_shell *data)
{
	ft_free_str_array(data->builtins->builtins_selection);
	free (data->builtins);
	data->builtins = NULL;
}
