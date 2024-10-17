/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:11:22 by iostancu          #+#    #+#             */
/*   Updated: 2024/10/18 00:42:39 by iostancu         ###   ########.fr       */
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

void	draw_border_map(t_map *map, mlx_image_t *screen)
{
	int x;
	int y;
	int height;
	int width;

	y = 0;
	height = map->height + (SIZE * 2);
	width = map->width + (SIZE * 2);
	while (y < SIZE)
	{
		x = 0;
		while (x < width)
		{
			mlx_put_pixel(screen, x, y, 0x000000);
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
			mlx_put_pixel(screen, x, y, 0x000000);
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
			mlx_put_pixel(screen, x, y, 0x000000);
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
			mlx_put_pixel(screen, x, y, 0x000000);
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
void	draw_2d_map(t_map *map, mlx_image_t *screen)
{
	int x;
	int y;

	draw_border_map(map, screen);
	y = SIZE + 1;
	printf("hellooooooo\n");
	printf("map->height: %d\n", map->height);
	printf("map->width: %d\n", map->width);
	while (y < map->height)
	{
		x = SIZE + 1;
		printf("y: %d\n", y);
		while (x < map->width)
		{
			printf("x: %d\n", x);
			if (map->grid[y][x] == 1)
				draw_cube(screen, (t_vec2){x * SIZE, y * SIZE}, 0x00FF00);
			else if (map->grid[y][x] == 0)
				draw_cube(screen, (t_vec2){x * SIZE, y * SIZE}, 0xFFFFFF);
			else if (map->grid[y][x] == -1)
				draw_cube(screen, (t_vec2){x * SIZE, y * SIZE}, 0xFF0000);
			x++;
		}
		y++;
	}
}
