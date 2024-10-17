/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:32:24 by cmateos-          #+#    #+#             */
/*   Updated: 2024/10/18 00:40:27 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	cover_char(char c)
{
	return (c == '1' || c == '0' || c == '.');
}

size_t	double_pointer_len(char **double_pointer)
{
	size_t	len;

	if (!double_pointer)
		return (0);
	len = 0;
	while (double_pointer[len])
		len++;
	return (len);
}

bool	map_closed(char **m, size_t x, size_t y)
{
	bool	valid;

	valid = true;
	if (x == 0 || y == 0 || y == double_pointer_len(m) - 1
		|| x == ft_strlen(m[0]) - 1 || !cover_char(m[y - 1][x])
		|| !cover_char(m[y + 1][x]) || !cover_char(m[y][x - 1])
		|| !cover_char(m[y][x + 1]))
		valid = false;
	if (valid && (m[y - 1][x] == '0' || m[y + 1][x] == '0' || m[y][x - 1] == '0'
		|| m[y][x + 1] == '0'))
		m[y][x] = '.';
	if (valid && m[y - 1][x] == '0')
		valid = map_closed(m, x, y - 1);
	if (valid && m[y + 1][x] == '0')
		valid = map_closed(m, x, y + 1);
	if (valid && m[y][x - 1] == '0')
		valid = map_closed(m, x - 1, y);
	if (valid && m[y][x + 1] == '0')
		valid = map_closed(m, x + 1, y);
	m[y][x] = '.';
	return (valid);
}

bool check_valid_map(char **map)
{
    int     row;
    long unsigned int     i;
    char    **m;

    row = -1;
    i = -1;
    m = map;
    while (++row != ft_arraylen(m))
    { 
        while (++i != (ft_strlen(m[row])))
        {
            if (m[row][i] == '0')
            {
                if (!map_closed(map, i, row))
                    return false;
            }
            m = map;
        }
        i = 0;
    }
    return (true);
}

int	**map_to_int(char **map, int h, int w)
{
	int	**grid;
	int	i;
	int	j;
	int	k;

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
