/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 21:46:24 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/12 16:15:55 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
	Gestiona las funciones/pasos clave del programa.
	Primero tokenizamos, luego hacemos la expansión,
	después creamos el árbol de sintaxis (AST),
	y por último usamos `execute_recursive` para recorrer
	todos los nodos mediante recursión y ejecutar los comandos.
*/

int	steps_manager(t_shell *data, char *input)
{
	if (!tokenizer(data, &data->prompt, input))
		return (exit_error(data, NULL, EXIT_FAILURE));
	// if (!expanstion(data->prompt.tokens, data->env))
	// if (!ast(data, data->prompt.tokens))
	// 	return (error(data));
	// if (!execute_recursive(data, data->ast_root))
	// 	return (error(data));
	clean_prompt(&data->prompt);
	return (SUCCESS);
}
