/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:32:24 by cmateos-          #+#    #+#             */
/*   Updated: 2024/10/13 20:09:52 by settes           ###   ########.fr       */
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
	m[y][x] = '3';
	return (valid);
}

bool check_valid_map(char **map)
{
    int     row;
    long unsigned int     i;
    char    **m;

    row = -1;
    i = -1;
    m = ft_arraydup(map);
	if (!m)
		return (false);
    while (++row != ft_arraylen(m))
    { 
        while (++i != (ft_strlen(m[row])))
        {
            if (m[row][i] == '0')
            {
                if (!map_closed(m, i, row))
                    return (ft_freearray(m), false);
            }
            // m = map;
        }
        i = 0;
    }
	// return true;

    return (ft_freearray(m), true);
}