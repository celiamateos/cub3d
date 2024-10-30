/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:53:53 by iostancu          #+#    #+#             */
/*   Updated: 2024/10/30 23:53:55 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int is_wall(t_map *map, t_vec2 pos)
{
    int x;
    int y;

    x = (int)pos.x;
    y = (int)pos.y;
    if (x < 0 || x >= map->width || y < 0 || y >= map->height)
        return (1);
    if (map->grid[y][x] != 0)
    {
        printf("A WALL !!\n");
        return (1);
    }
    return (0);
}