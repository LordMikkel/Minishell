/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minishell_title.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:44:03 by migarrid          #+#    #+#             */
/*   Updated: 2025/11/21 15:44:22 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

void	print_minishell_title(void)
{
	ft_printf_fd(STDOUT, TITLE_COLOR "\n\n");
	ft_printf_fd(STDOUT, T1 "\n");
	ft_printf_fd(STDOUT, T2 "\n");
	ft_printf_fd(STDOUT, T3 "\n");
	ft_printf_fd(STDOUT, T4 "\n");
	ft_printf_fd(STDOUT, T5 "\n");
	ft_printf_fd(STDOUT, "\n\n" RESET_COLOR);
}
