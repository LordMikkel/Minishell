/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:37:27 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/12 21:21:11 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*
	Añade un nuevo token al array `tokens` con el valor y tipo dados.
	Si es de tipo EXPANSION, marca su flag `expand` como TRUE.
	Usa un índice estático para añadir en la posición correcta.
*/

void	add_token(t_token *tokens, char *value, int type)
{
	static int	i = 0;

	if (type == RESET)
	{
		i = 0;
		return ;
	}
	tokens[i].value = value;
	tokens[i].type = type;
	if (tokens[i].type == EXPANSION)
		tokens[i].expand = TRUE;
	i++;
}

/*
	Recorre el string `input` y llama a las funciones `is_*` para
	detectar cada tipo de token. Avanza el índice según lo detectado.
*/

void	get_tokens(t_shell *data, t_token *tokens, char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		is_not_token(input, &i);
		is_heredoc(tokens, input, &i);
		is_and(tokens, input, &i);
		is_or(tokens, input, &i);
		is_redir(tokens, input, &i);
		is_pipe(tokens, input, &i);
		is_parenten(tokens, input, &i);
		is_quote(tokens, input, &i);
		is_semicolon(tokens, input, &i);
		is_wildcar(tokens, input, &i);
		is_scape(tokens, input, &i);
		is_dolar(data, tokens, input, &i);
		is_word(data, tokens, input, &i);
	}
}

int	tokenizer(t_shell *data, t_prompt *prompt, char *input)
{
	allocate_tokens(data, prompt, input);
	get_tokens(data, prompt->tokens, input);
	// valid_tokens(prompt->tokens);
	return (SUCCESS);
}
