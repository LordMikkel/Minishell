/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 21:46:24 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/09 22:49:27 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*Here we simply manage all the key functions/steps of the program.
We first tokenize, then we'll do the expantionthe we create
the tree, in this particular case, will use the ast (syntaxis tree).
To conlcude we use execute_recursive to go through all the
nodes by suing recursion and execute the commands*/

int steps_manager(t_shell *data, char *input)
{
	if (!tokenizer(data, input))
		return (error(data));
	if (!expanstion(data->prompt.tokens, data->env))
		return (error(data));
	if (!ast(data, data->prompt.tokens))
		return (error(data));
	if (!execute_recursive(data, data->ast_root))
		return (error(data));
	clean_data(data);
}
