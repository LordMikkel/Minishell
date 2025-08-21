/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfilterc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:05:03 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/21 17:09:30 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_plus.h"

char	*ft_strfilter_c(const char *str, char c)
{
	char	*result;
	size_t	i;
	size_t	j;
	size_t	count;

	if (!str)
		return (NULL);
	count = 0;
	i = 0;
	while (str[i])
		if (str[i++] != c)
			count++;
	result = ft_calloc(count + 1, sizeof (char *));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
