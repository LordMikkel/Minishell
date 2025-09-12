/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:56:06 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/09/12 13:38:03 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void aux_delete(t_var **node)
{
	if ((*node)->key)
	{
		free((*node)->key);
		(*node)->key = NULL;
	}
	if ((*node)->value)
	{
		free((*node)->value);
		(*node)->value = NULL;
	}
	free(*node);
	*node = NULL;
}

/*
 * my_unset - Elimina variables de entorno según los tokens proporcionados.
 *
 * @data: Puntero a la estructura principal del shell.
 * @env: Puntero a la estructura que contiene las variables de entorno.
 * @tokens: Array de tokens que pueden representar claves a eliminar.
 *
 * Esta función recorre los tokens recibidos en el prompt y, por cada uno que
 * sea de tipo WORD o ASIGNATION, busca en la lista doblemente enlazada de
 * variables de entorno. Si encuentra una coincidencia con la clave del token,
 * elimina el nodo correspondiente, actualizando los punteros prev y next
 * para mantener la integridad de la lista.
 *
 * Si el nodo a eliminar es el primero, actualiza env->vars.
 * Si es el único nodo, también actualiza env->vars y termina la función.
 * La memoria del nodo se libera mediante aux_delete().
*/

void my_unset(t_shell *data, t_env *env, t_token *tokens)
{
	t_var	*node_to_delete;
	t_var	*next;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->prompt.n_alloc_tokens)
	{
		if (tokens[i].type != WORD && tokens[i].type != ASIGNATION)
		{
			i++;
			continue ;
		}
		node_to_delete = env->vars;
		while (node_to_delete)
		{
			if (ft_strcmp(node_to_delete->key, tokens[i].value) == 0)
			{
				if (!node_to_delete->prev)
				{
					env->vars = node_to_delete->next;
					aux_delete(&node_to_delete);
					return ;
				}
				else
					node_to_delete->prev->next = node_to_delete->next;
				if (node_to_delete->next)
					node_to_delete->next->prev = node_to_delete->prev;
					next = node_to_delete->next;
					aux_delete(&node_to_delete);
					node_to_delete = next;
					continue ;
			}
			node_to_delete = node_to_delete->next;
		}
		i++;
	}
}
