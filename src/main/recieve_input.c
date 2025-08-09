/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recieve_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 21:42:00 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/09 22:46:36 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *recieve_input(char **input, t_shell *data)
{
	*input = readline("Minishell>>  "); //Si falla o no falla, retorna y eso se intercepta en el main.
	if (*input == NULL) //si fallo readline hay que revisar si errno esta definido por el sistema. Si fue CTR + D, errno no estara establecido, por lo que entrara y no pasara nada.
		clean_data(data); //Sempre libera memoria!
	return (*input);
}
