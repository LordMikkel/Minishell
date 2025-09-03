/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 01:17:17 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/03 01:21:28 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void shell_pwd(t_shell *data)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		exit_error(data, ERR_MALLOC, EXIT_FAILURE);
	printf("%s\n", pwd);
	free(pwd);
}
