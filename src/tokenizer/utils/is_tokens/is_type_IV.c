/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type_IV.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 14:34:32 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/15 14:34:35 by davdiaz-         ###   ########.fr       */
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
