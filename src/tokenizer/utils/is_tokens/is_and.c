/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:44:05 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/03 17:01:16 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Detecta el operador lógico '&&' y añade un token de tipo AND.
	Avanza el índice para no volver a procesar el token.
*/

void	is_and(t_shell *data, t_prompt *prompt, const char *str, int *i)
{
	char	*dup_fd;

	if (str[*i] == '&')
	{
		if (str[*i + 1] == '&')
		{
			add_token(data, prompt, "&&", AND);
			(*i) += 2;
		}
		else if (ft_isdigit(str[*i + 1]))
		{
			dup_fd = ft_substr(str, *i, 2);
			if (!dup_fd)
				exit_error(data, ERR_MALLOC, EXIT_FAILURE);
			add_token(data, prompt, dup_fd, WORD);
			(*i) += 2;
		}
		else
		{
			add_token(data, prompt, "&", BACKGROUND);
			(*i)++;
		}
	}
}
