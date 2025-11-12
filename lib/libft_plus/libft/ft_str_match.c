/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_match.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:30:13 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/12 22:09:25 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_plus.h"

char	*ft_str_match(char *str, char *word_to_find)
{
	int	i;
	int	j;

	i = 0;
	if (!*word_to_find)
		return (NULL);
	while (str[i] != '\0')
	{
		j = 0;
		while (word_to_find[j] && str[i + j] == word_to_find[j])
			j++;
		if (word_to_find[j] == '\0')
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}
