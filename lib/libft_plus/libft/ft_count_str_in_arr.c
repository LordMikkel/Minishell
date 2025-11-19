/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_str_in_arr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 10:35:02 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/19 16:38:20 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_plus.h"

int ft_count_str_in_arr(char **arr)
{
	int count;

	if (!arr)
		return (0);
	count = 0;
	while (arr[count] != NULL)
		count++;
	return (count);
}
