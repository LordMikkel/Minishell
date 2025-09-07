/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type_II.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:48:00 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/07 05:58:42 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

int	is_between_quotes_type(int type)
{
	if (type == WORD)
		return (1);
	return (0);
}

int	is_simplify_type(int type)
{
	if (type == WORD || type == NO_SPACE
		|| type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
		return (1);
	return (0);
}
