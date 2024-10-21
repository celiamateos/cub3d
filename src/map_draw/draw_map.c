/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:11:22 by iostancu          #+#    #+#             */
/*   Updated: 2024/10/18 05:36:08 by settes           ###   ########.fr       */
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
	while (y < SIZE)
	{
		x = 0;
		while (x < width)
		{
			mlx_put_pixel(map->game->screen, x, y, 0x000000);
			x++;
		}
		y++;
	}
	y = SIZE;
	while (y < (height - SIZE))
	{
		x = 0;
		while (x < SIZE)
		{
			mlx_put_pixel(map->game->screen, x, y, 0x000000);
			x++;
		}
		y++;
	}
	x = width - SIZE;
	y = SIZE;
	while (y < (height - SIZE))
	{
		while (x < width)
		{
			mlx_put_pixel(map->game->screen, x, y, 0x000000);
			x++;
		}
		y++;
	}
	x = 0;
	y = height - SIZE;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			mlx_put_pixel(map->game->screen, x, y, 0x000000);
			x++;
		}
		y++;
	}
}



/**
 * @brief Minimap. First draw a border, then draw the map.
 * border size is 64 of weight and (64 * map->widht or height) of height
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
	while (map->grid[i])
	{
		j = 0;
		x = 1;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == 1)
				draw_cube(map->game->screen, (t_vec2){x * SIZE, y * SIZE}, 0x00FF00);
			else if (map->grid[i][j] == 0)
				draw_cube(map->game->screen, (t_vec2){x * SIZE, y * SIZE}, 0xFFFFFF);
			else if (map->grid[i][j] == -1)
				draw_cube( map->game->screen, (t_vec2){x * SIZE, y * SIZE}, 0xFF0000);
			j++;
			x++;
		}
		y++;
		i++;
	}
}
