/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 11:19:36 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/19 16:58:33 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../../inc/minishell.h"

/*
	Compara el nombre de un archivo con el patron del wildcard.
	Cada '*' puede representar cualquier cantidad de caracteres (incluso
	ninguno) y el resto de caracteres tienen que coincidir tal cual.
	Eg. minishe*l -> minishell, minishelxxxl | *.c -> main.c
*/

int	match_wildcard(char *pattern, char *name)
{
	if (*pattern == '\0')
		return (*name == '\0');
	if (*pattern == '*')
	{
		while (*pattern == '*')
			pattern++;
		if (*pattern == '\0')
			return (TRUE);
		while (*name)
		{
			if (match_wildcard(pattern, name))
				return (TRUE);
			name++;
		}
		return (FALSE);
	}
	if (*pattern != *name)
		return (FALSE);
	return (match_wildcard(pattern + 1, name + 1));
}
