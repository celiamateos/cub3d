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


void ft_print_grid(int **grid, int height, int width)
{
	int h;
	int w;

	h = 0;
	w = -1;
	while (h != height)
	{
		while (++w != width)
			printf("%d", grid[h][w]);
		w = -1;
		h++;
		printf("\n");
	}
}