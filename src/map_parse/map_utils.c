/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:01:29 by cmateos-          #+#    #+#             */
/*   Updated: 2024/10/14 20:37:27 by settes           ###   ########.fr       */
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

char **ft_arraydup(char **arr)
{
	char	**new;
	int		row;
	int		len;

	len = ft_arraylen(arr) + 1;
	row = -1;
	new = ft_calloc(len, sizeof(char *));
	while (arr[++row])
	{
		new[row] = ft_strdup(arr[row]);
		if (!new[row])
			return (ft_free_error_arr(new, row), NULL);
	}
	new[row] = NULL;
	return (new);
}

int	**map_to_int(char **map, int h, int w)
{
	int	**grid;
	int	i;
	int	j;

	i = 0;
	j = 0;
	grid = malloc(sizeof(int *) * (w));
	if (!grid)
		return (NULL);
	while (i < h)
	{
		grid[i] = malloc(sizeof(int) * w);
		if (!grid[i])
		{
			while (i >= 0)
				free(grid[i--]);
			free(grid);
			return (NULL);
		}
		j = 0;
		while (j < w)
		{
			if (map[i][j] == '1')
				grid[i][j] = 1;
			else if (map[i][j] == '0' || map[i][j] == '.')
				grid[i][j] = 0;
			else 
				grid[i][j] = -1;
			j++;
		}
		i++;
	}
	return (grid);
}
