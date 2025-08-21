/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   is_dolar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:58:46 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/16 15:52:48 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Si el carácter es '$', añade un token de tipo EXPANSION.
	Luego procesa el resto como palabra con is_word.
*/

char	*cleanner_exp(t_shell *data, char *expansion, int len, char trash)
{
	int		j;
	int		k;
	char	*clean_expansion;

	j = 0;
	k = 0;
	if (ft_strchr(expansion, trash))
	{
		clean_expansion = ft_calloc(len + 1, sizeof(char *));
		if (!clean_expansion)
		{
			free(expansion);
			exit_error(data, ERR_MALLOC, EXIT_FAILURE);
		}
		while(expansion[j])
		{
			if (expansion[j] != trash)
				clean_expansion[k++] = expansion[j];
			j++;
		}
		clean_expansion[k] = '\0';
		free(expansion);
		return (clean_expansion);
	}
	return (expansion);
}

static int	isn_exp(int c, int *i)
{
	if (c == '|' || c == '<' || c == '>' || c == '&' || c == '(' || c == ')'
		|| c == '\'' || c == '\"' || c ==  '.')
		return (1);
	else if (c == ';')
	{
		(*i)++;
		return (1);
	}
	return (0);
}

void	is_dolar(t_shell *data, t_token *tokens, const char *str, int *i)
{
	int		len;
	int		start;
	char	*expansion;

	if (str[*i] == '$')
	{
		start = *i;
		(*i)++;
		if (ft_isdigit(str[*i]))
		{
			(*i)++;
			return ;
		}
		while (str[*i] != '\0' && !ft_isspace(str[*i]) && !isn_exp(str[*i], i))
			(*i)++;
		len = *i - start;
		if (len > 0)
		{
			expansion = ft_substr(str, start, len);
			if (!expansion)
				exit_error(data, ERR_MALLOC, EXIT_FAILURE);
			expansion = cleanner_exp(data, expansion, len, ';');
			add_token(tokens, expansion, EXPANSION);
		}
	}
}
