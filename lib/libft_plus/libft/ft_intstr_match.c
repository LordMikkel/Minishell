/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intstr_match.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 10:57:44 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/19 16:40:21 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_plus.h"

int		ft_intstr_match(char *str, char *word_to_find, int start)
{
	int	j;

	if (!str || !word_to_find || !*word_to_find || start < 0)
		return (-1);
	while (str[start] != '\0')
	{
		j = 0;
		while (word_to_find[j] && str[start + j] != '\0'
				&& str[start + j] == word_to_find[j])
			j++;
		if (word_to_find[j] == '\0')
			return (start);
		start++;
	}
	return (-1);
}
