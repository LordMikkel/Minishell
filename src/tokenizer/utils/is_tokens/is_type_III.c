/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type_III.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 17:23:51 by migarrid          #+#    #+#             */
/*   Updated: 2025/10/05 16:46:07 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

int	is_asignation_type(int type)
{
	if (type == ASIGNATION || type == PLUS_ASIGNATION
		|| type == TEMP_ASIGNATION)
		return (1);
	return (0);
}

int	is_symbol(int c)
{
	if (c == '?' || c == '!' || c == '$' || c == '_')
		return (1);
	return (0);
}

int	is_arg_type(int type)
{
	if (type == ASIGNATION || type == WORD)
		return (1);
	return (0);
}
