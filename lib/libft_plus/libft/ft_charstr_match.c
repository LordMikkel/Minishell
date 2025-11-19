/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charstr_match.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:30:13 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/19 16:37:57 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_plus.h"

char	*ft_charstr_match(char *str, char *word_to_find)
{
	int	i;
	int	j;

	i = 0;
	if (!word_to_find || !*word_to_find)
		return ((char *)str);
	if (str == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] == word_to_find[j] && word_to_find[j] != '\0')
			j++;
		if (word_to_find[j] == '\0')
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}
