/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 01:07:14 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/03 01:07:39 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*
	Añade un nuevo token al array `tokens` con el valor y tipo dados.
	Si es de tipo EXPANSION, marca su flag `expand` como TRUE.
	Usa un índice estático para añadir en la posición correcta.
*/

int	add_token(t_token *tokens, char *value, int type)
{
	static int	i = 0;

	if (type == RESET)
	{
		i = 0;
		return (0);
	}
	tokens[i].id = i;
	tokens[i].value = value;
	tokens[i].type = type;
	if (tokens[i].type == EXPANSION)
		tokens[i].expand = TRUE;
	if (i > 0 && tokens[i - 1].type == DOUBLE_QUOTE)
		tokens[i].double_quoted = TRUE;
	if (i > 0 && tokens[i - 1].type == SINGLE_QUOTE)
		tokens[i].single_quoted = TRUE;
	i++;
	return (tokens[tokens[i - 1].id].id);
}
