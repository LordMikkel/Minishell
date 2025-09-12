/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_tokens_logic.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 21:33:14 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/12 21:34:58 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

void	transform_tokens_logic(t_shell *data, t_prompt *prompt, t_token *tokens)
{
	transform_cmd_to_word(data, tokens);
	transform_word_to_asignation(data, tokens, 1);
	transform_invalid_asig_to_word(prompt, tokens);
	transform_word_to_asignation(data, tokens, 2);
}
