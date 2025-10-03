/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eliminate_temp_asig.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 02:23:37 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/10/03 20:19:17 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*
 * En Bash, cuando se usan múltiples asignaciones temporales como:
 *     var+=1 var=2 echo $var
 * el shell construye el entorno del proceso hijo antes de ejecutar el comando.
 *
 * - `var+=1` intenta concatenar "1" a `var`, pero si `var` no existe aún,
 *   Bash lo interpreta como `var="1"`.
 * - Luego `var=2` sobrescribe ese valor, por lo que el entorno final del hijo
 *   contiene `var="2"`.
 *
 * Importante: la expansión de `$var` ocurre en el shell padre antes del fork,
 * y como `var` no existe en el padre, `$var` se expande a vacío.
 * Por eso, el comando `echo` no recibe argumentos y no imprime nada.
 *
 * En resumen:
 * - El hijo recibe solo la última asignación efectiva (`var=2`).
 * - La expansión en el padre determina lo que `echo` recibe.
 * - Para que el hijo expanda `$var`, debe usarse algo como:
 *   var+=1 var=2 bash -c 'echo $var'
*/

void	eliminate_temp_asig(t_prompt *prompt, t_token *tokens)
{
	int	i;

	i = 0;
	while (i < prompt->n_tokens)
	{
		if (tokens[i].type == TEMP_ASIGNATION)
		{
			eliminate_token(prompt, tokens, i);
			if (i < prompt->n_tokens && tokens[i].type == PLUS_ASIGNATION)
				eliminate_token(prompt, tokens, i);
			continue ;
		}
		i++;
	}
}
