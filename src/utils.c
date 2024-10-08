/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmateos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:01:29 by cmateos-          #+#    #+#             */
/*   Updated: 2024/10/03 12:01:30 by cmateos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

int ft_arraylen(char **array)
{
	int i;

	i = 0;
	if (!array || !*array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

void ft_printarray(char **arr)
{
	int i;

	i = 0;
	if (!arr || !arr[i])
		return err(RED"error: dont exit array\n"RESET);
	while(arr[i])
		printf(PURPLE"%s"RESET, arr[i++]);
}

void ft_printintarray(int *nb, int size)
{
	int i;
	char *num;

	i = 0;
	while (i < size)
	{
		num = ft_itoa(nb[i]);
		printf("%s ", num);
		free (num);
		i++;
	}
	printf("\n");
}

//@brief Free previous allocated if error
//@param mem array to free
//@param i line where it was error
int	ft_free_error_arr(char **mem, long row)
{
	int	i;

	i = 0;
	if (mem[row] == NULL)
	{
		while (i < row)
		{
			free(mem[i]);
			i++;
		}
		free(mem);
		return (1);
	}
	return (0);
}

void	save_map(t_data *data, char *str)
{
	int i;
	int len;
	char **aux;

	i = 0;

	if (data->map->map)
		len = ft_arraylen(data->map->map);
	else
		len = 0;
	aux = ft_calloc(len + 2, sizeof(char *));
	if (!aux)
		exit(1); //Free
	while (i != len)
	{
		aux[i] = ft_strdup(data->map->map[i]);
		if (!aux[i])
			ft_free_error_arr(aux, i), exit(1); //Free
		i++;
	}
	aux[i] = ft_strdup(str);
	if (!aux[i])
		ft_free_error_arr(aux, i), exit(1); //Free
	aux[++i] = NULL;
	if (data->map->map)
		ft_freearray(data->map->map);
	data->map->map = aux;
}