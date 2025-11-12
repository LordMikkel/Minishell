/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:17:43 by migarrid          #+#    #+#             */
/*   Updated: 2025/11/12 10:24:22 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
	Función principal `main` de Minishell. Inicializa la estructura `data`
	con `init_minishell` y entra en el bucle principal. Lee la entrada del
	usuario, tokeniza, construye el AST y ejecuta los comandos. Limpia la
	memoria tras cada ciclo y termina con `exit_succes` al salir.
*/

int	main(int argc, char **argv, char **envp)
{
	t_shell	data;
	char	*input;

	init_minishell(&data, argc, argv, envp);
	while (receive_input(&input, &data) != NULL)
	{
		if (!tokenizer(&data, &data.prompt, input))
			continue ;
		/*t_var *current;
		current = data.env.vars;
		printf("BEFORE THE AST\n\n");
		while (current)
		{
			printf("Key: %s, Value: %s, Type: %d\n\n",
				current->key,
				current->value,
				current->type);
			current = current->next;
		}*/
		ast_builder(&data, data.prompt.tokens, data.prompt.n_tokens);
		executor_recursive(&data, data.ast_root, &data.exec, FATHER);
		print_tokens_debug(&data.prompt);
		clean_cycle(&data, &data.prompt, &data.ast_root);
		//printf("AFTER CLEAN_CYCLE\n\n");
		/*while (current)
		{
			printf("Key: %s, Value: %s, Type: %d\n\n",
				current->key,
				current->value,
				current->type);
			current = current->next;
		}*/
	}
	exit_succes(&data, MSG_GOODBYE, data.exit_code);
	return (data.exit_code);
}
