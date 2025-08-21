/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wildcar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:43:41 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/21 17:50:41 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Detecta comodines '*' o '?' y añade un token de tipo WILDCAR.
*/
char	*cleanner_wildcar(t_shell *data, char *wildcar, int len, char trash)
{
	int		j;
	int		k;
	char	*clean_wildcar;

	j = 0;
	k = 0;
	if (ft_strchr(wildcar, trash))
	{
		clean_wildcar = ft_calloc(len + 1, sizeof(char *));
		if (!clean_wildcar)
		{
			free(wildcar);
			exit_error(data, ERR_MALLOC, EXIT_FAILURE);
		}
		while(wildcar[j])
		{
			if (wildcar[j] != trash)
				clean_wildcar[k++] = wildcar[j];
			j++;
		}
		clean_wildcar[k] = '\0';
		free(wildcar);
		return (clean_wildcar);
	}
	return (wildcar);
}

static int	isn_wild(int c, int *i)
{
	if (c == '|' || c == '<' || c == '>' || c == '&' || c == '(' || c == ')'
		|| c == '\'' || c == '\"' )
		return (1);
	else if (c == ';')
	{
		(*i)++;
		return (1);
	}
	return (0);
}

void	is_wildcar(t_shell *data, t_token *tokens, const char *str, int *i)
{
	int		len;
	int		start;
	char	*wildcar;

	if (str[*i] == '*')
	{
		start = *i;
		(*i)++;
		while (str[*i] != '\0' && !ft_isspace(str[*i]) && !isn_wild(str[*i], i))
			(*i)++;
		len = *i - start;
		if (len > 0)
		{
			wildcar = ft_substr(str, start, len);
			if (!wildcar)
				exit_error(data, ERR_MALLOC, EXIT_FAILURE);
			wildcar = cleanner_wildcar(data, wildcar, len, ';');
			wildcar = cleanner_wildcar(data, wildcar, len, '?');
			add_token(tokens, wildcar, WILDCAR);
		}
	}
}
