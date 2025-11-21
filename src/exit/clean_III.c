/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_III.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 21:43:11 by migarrid          #+#    #+#             */
/*   Updated: 2025/11/21 19:45:20 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
	Elimina las variables `TEMP_ASIGNATION` del ciclo. Elimina solo los que se
	ejecuten/afecten en el shell padre/global, ya que los que se ejecuten
	en child procesess se borraran solos.
*/

void	clean_temp_variables(t_shell *data, t_token *tokens, t_node *node)
{
	my_clean_unset(data, tokens, node->arg_types);
}

/*
	Restea toda la memoria de `t_extras` y la deja apuntando
	a NULL para evitar accesos inválidos.
*/

void	clean_extras(t_extras *extras)
{
	if (extras->user_name)
	{
		free(extras->user_name);
		extras->user_name = NULL;
	}
	*extras = (t_extras){0};
}

/*
	Cierra los fd originales al finalizar el programa
	asi cumplimos con la limpieza para el sistema.
*/

void	clean_fd(t_exec *exec, int history_fd)
{
	if (exec->original_stdin)
		close(exec->original_stdin);
	if (exec->original_stdout)
		close(exec->original_stdout);
	if (history_fd)
		close(history_fd);
}

/*
	Restea y libera toda la memoria de `t_builtin` y la deja apuntando
	a NULL para evitar accesos inválidos.
*/

void	clean_builtins_selection(t_builtin *builtins)
{
	if (builtins->builtins_selection)
		ft_free_str_array(&builtins->builtins_selection);
	*builtins = (t_builtin){0};
}
