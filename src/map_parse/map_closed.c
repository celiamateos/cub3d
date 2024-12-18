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

int	cover_char(char c)
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

int	map_closed(char **m, size_t x, size_t y)
{
	int	valid;

	valid = 1;
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
	m[y][x] = '3';
	return (valid);
}

int check_valid_map(char **map)
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
                    return (0);
            }
            m = map;
        }
        i = 0;
    }

    return (true);
}
