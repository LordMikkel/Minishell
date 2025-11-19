/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_complex_case.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 11:19:36 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/19 16:58:33 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../../inc/minishell.h"

/*
	Función para manjear casos complejos de WILDCARDS.
	La logica es sencilla:

	wildcard es: *estas*como
	file es: "hola como estas"

	Se hace un split del wildcard, ya que los * no nose sirven de nada ya que
	solamente expresan que puede o no puede haber algo en esa posición.
	Es decir, en estas * como, en la posicion del WILDCARD puede haber un perro
	hola, adios, gato, a, b c, lo que sea o simplemente no haber nada.

	De este modo ya tenemos los str que necesitamos buscar en file.
	Iteramos sobre ese arr de str y en cada iteración hacemos un ft_str_match,
	que basicamente busca el str completo en el file y si tiene éxito entonces
	retirna un ptr a la primera posición del match que hubo en file.

	Luego se guarda ese ptr del match en otro arr de str llamado result.
	Al iterar sobre los str del wildcard, el mismo orden queda grabado en cada
	resultado que se almacena en el arr result.

	Cuando se acabe de iterar, simplemente se verifica que el orden de los ptrs
	en el arr result este en orden ascendiente para confirmarnos de que no
	solo hubo matchs sino que también esos matches estan en el orden correcto.

	en file, el indice 10 corresponde a "como"
	en el file el indice  5 corresponde a "estas"

	result = [10, 5] -> Hay matches pero no en el orden correcto.
*/

static void	aux_alloc(t_shell *data, char ***ptr, int **result, char *key)
{
	*ptr = ft_split(key, '*');
	if (!*ptr)
		exit_error(data, ERR_MALLOC, EXIT_FAILURE);
	*result = ft_calloc(ft_count_str_in_arr(*ptr) + 1, sizeof(int));
	if (!*result)
	{
		ft_free_str_array(ptr);
		exit_error(data, ERR_MALLOC, EXIT_FAILURE);
	}
}

static int	compare_match_order(int *result, int len)
{
	int	i;

	i = 0;
	if (len == 1)
		return (SUCCESS);
	while (i < len - 1)
	{
		if (result[i] >= result[i + 1])
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static int	build_match_array(char *file, char **ptr, int *out_len, int *result)
{
	int	i;
	int	j;
	int	search_start_index;

	i = 0;
	j = 0;
	search_start_index = 0;
	while (ptr[i] != NULL)
	{
		if (ptr[i][0] == '\0')
		{
			i++;
			continue ;
		}
		result[j] = ft_intstr_match(file, ptr[i], search_start_index);
		if (result[j] == ERROR)
			return (FAILURE);
		search_start_index = result[j] + ft_strlen(ptr[i]);
		j++;
		i++;
	}
	*out_len = j;
	return (SUCCESS);
}

int	handle_complex_case(t_shell *data, char *file, char *key, int wildcard_type)
{
	char	**ptr;
	int		*result;
	int		len;

	if (wildcard_type != COMPLEX)
		return (FALSE);
	aux_alloc(data, &ptr, &result, key);
	if (build_match_array(file, ptr, &len, result) == FAILURE)
	{
		ft_free_str_array(&ptr);
		free(result);
		return (FALSE);
	}
	if (compare_match_order(result, len))
	{
		ft_free_str_array(&ptr);
		free(result);
		return (TRUE);
	}
	ft_free_str_array(&ptr);
	free(result);
	return (FALSE);
}
