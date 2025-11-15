/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intstr_match.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 10:57:44 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/15 20:58:19 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_plus.h"

int		ft_intstr_match(char *str, char *word_to_find, int start)
{
	int	j;

	if (!*word_to_find)
		return (-1);
	while (str[start] != '\0')
	{
		j = 0;
		while (word_to_find[j] && str[start + j] == word_to_find[j])
			j++;
		if (word_to_find[j] == '\0')
			return (start);
		start++;
	}
	return (-1);
}
