/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_word_to_wildcard.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:49:40 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/09 21:12:57 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Función para trnasformar tokens WORD en WILDCARDS en el caso específico
	en el que el valor del token tenga '*' al final.

	Ejemplo:

	-"hola*" ->Se cataloga como WORD pero esta mal. Debería de ser WILDCARD.

	Por esto se revisa el char final de su value.
*/

void	transform_word_to_wildcard(t_shell *d, t_prompt *promp, t_token *tokens)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (i < promp->n_tokens)
	{
		if (tokens[i].type == WORD)
		{
			len = ft_strlen(tokens[i].value);
			if (tokens[i].value[len - 1] == '*')
				tokens[i].type = WILDCARD;
		}
		i++;
	}
}
