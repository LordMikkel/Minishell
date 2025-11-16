/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_temp_asig.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:05:58 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/16 00:08:54 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*
	Identifica si el token es un COMMAND o un BUILT_IN para saber
	que contextp/naturalez/subtipo darle a las asignaciones temporales.

	Si son de un BUILT_IN entonces se deberian de asignar de manera LOCAL.
	si son de un COMMAND deberian de asignarse de manera ENV.

	Al final del programa ambas son eliminadas para que no afecten
	al shell padre/global.

	Se uitlia asignation(); en lugar de export(); para no sobrecargarla con
	difeentes responsabilidades y que se vuelva mas compleja de lo que tiene
	que hacer.

	Es importante recordar que se utilza un int *arg_types para dar contexto
	a los argumentos (concretamente export) y a las temporal asignations,
	de modo que en casos como: "var=1 export a=1", tanto "var" como "a" viven
	en un mismo arr, con lo cual es muy importante verificar en donde terminan
	las TEMP_ASIGNATIOS para no ejecutar args de export (que serán ejecutadas
	en export obviamnete). SU indice también es -1 para poder diferenciarlo de
	cualquier otro numero, qu es valido.
*/

static void apply_to_built_in_loop(t_shell *data, t_token *tokens, t_node *node)
{
	int	i;

	i = 0;
	while (node->arg_types[i] != -1)
	{
		if (is_real_assignation_type(tokens[node->arg_types[i]].type))
			return ;
		if (tokens[node->arg_types[i]].type == TEMP_ASIGNATION)
			asignation(data, &tokens[node->arg_types[i]], LOCAL);
		else if (tokens[node->arg_types[i]].type == TEMP_PLUS_ASIGNATION)
			asignation(data, &tokens[node->arg_types[i]], PLUS_ASIGNATION);
		i++;
	}
}

static void apply_to_commnad_loop(t_shell *data, t_token *tokens, t_node *node)
{
	int	i;

	i = 0;
	while (node->arg_types[i] != -1)
	{
		if (is_real_assignation_type(tokens[node->arg_types[i]].type))
			return ;
		if (tokens[node->arg_types[i]].type == TEMP_ASIGNATION)
			asignation(data, &tokens[node->arg_types[i]], ENV);
		else if (tokens[node->arg_types[i]].type == TEMP_PLUS_ASIGNATION)
			asignation(data, &tokens[node->arg_types[i]], PLUS_ASIGNATION);
		i++;
	}
}

void	apply_temp_asig(t_shell *data, t_token *tokens, t_node *node)
{
	if (node->type == BUILT_IN)
		apply_to_built_in_loop(data, tokens, node);
	else if (node->type == COMMAND)
		apply_to_commnad_loop(data, tokens, node);
}
