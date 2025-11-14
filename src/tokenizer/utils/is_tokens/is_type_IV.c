/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type_IV.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:03:34 by migarrid          #+#    #+#             */
/*   Updated: 2025/11/14 16:23:11 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
 * Determina si el token requiere simplificación cuando está junto
 * a un token NO_SPACE, lo que indica que deben unirse
 * para poder procesarse correctamente.
 */

int	is_needed_to_simplify(int type)
{
	if (is_primitive_cmd_type(type)
		|| type == WILDCARD || type == DELIMITER)
		return (1);
	return (0);
}
