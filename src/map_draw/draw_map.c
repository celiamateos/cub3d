/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:11:22 by iostancu          #+#    #+#             */
/*   Updated: 2024/10/21 22:09:33 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_cube(mlx_image_t *screen, t_vec2 pos, int color)
{
	int x;
	int y;

	y = 0;
	while (y < SIZE)
	{
		x = 0;
		while (x < SIZE)
		{
			mlx_put_pixel(screen, pos.x + x, pos.y + y, color);
			x++;
		}
		y++;
	}
}
void	draw_border_map(t_map *map)
{
	int x;
	int y;
	int height;
	int width;

	y = 0;
	height = map->height * (SIZE);
	width = map->width * (SIZE);
	while (y <= SIZE)
	{
		x = 0;
		while (x <= width + (SIZE * 2))
		{
			mlx_put_pixel(map->game->screen, x, y, 6771586);
			x++;
		}
		y++;
	}
	y = SIZE;
	while (y <= (height + (SIZE * 2)))
	{
		x = 0;
		while (x <= SIZE)
		{
			mlx_put_pixel(map->game->screen, x, y, 6771586);
			x++;
		}
		y++;
	}
	x = width + SIZE;
	y = SIZE;
	while (y <= (height + (SIZE * 2)))
	{
		while (x <= (width + (SIZE * 2)))
		{
			mlx_put_pixel(map->game->screen, x, y, 6771586);
			x++;
		}
		y++;
	}
	x = 0;
	y = height + 1;
	while (y <= (height + (SIZE * 2)))
	{
		x = 0;
		while (x <= (width + (SIZE * 2)))
		{
			mlx_put_pixel(map->game->screen, x, y, 6771586);
			x++;
		}
		y++;
	}
}



/**
 * @brief Minimap. First draw a border, then draw the map.
 * border size is 64 of weight and (64 * map->widht or height) of height
 * 
 * first cube starts at 65, 65
 * 
 * @param map 
 * @param screen 
 */
void	draw_2d_map(void *param)
{
	t_map *map;
	int x;
	int y;
	int i;
	int j;

	map = (t_map *)param;
	draw_border_map(map);
	y = SIZE + 1;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		x = SIZE + 1;
		while (j < map->width)
		{
			if (map->grid[i][j] == 1)
				draw_cube(map->game->screen, (t_vec2){x , y}, 6347644);
			else if (map->grid[i][j] == 0)
				draw_cube(map->game->screen, (t_vec2){x , y}, 2700596);
			else if (map->grid[i][j] == -1)
				draw_cube(map->game->screen, (t_vec2){x , y}, 0);
			j++;
			x = x + SIZE;
		}
		y = y + SIZE;
		i++;
	}
}
