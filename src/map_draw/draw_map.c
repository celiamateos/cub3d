/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:11:22 by iostancu          #+#    #+#             */
/*   Updated: 2024/10/22 21:25:54 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_rgba(int r, int g, int b, int a);

void	draw_cube(mlx_image_t *screen, t_vec2 pos, int color)
{
	int x;
	int y;

	y = 0;
	while (y < MINIMAP_SIZE)
	{
		x = 0;
		while (x < MINIMAP_SIZE)
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
	height = map->height * (MINIMAP_SIZE);
	width = map->width * (MINIMAP_SIZE);
	while (y <= MINIMAP_SIZE)
	{
		x = 0;
		while (x <= width + (MINIMAP_SIZE * 2))
		{
			mlx_put_pixel(map->game->screen, x, y, 6771586);
			x++;
		}
		y++;
	}
	y = MINIMAP_SIZE;
	while (y <= (height + (MINIMAP_SIZE * 2)))
	{
		x = 0;
		while (x <= MINIMAP_SIZE)
		{
			mlx_put_pixel(map->game->screen, x, y, 6771586);
			x++;
		}
		y++;
	}
	x = width + MINIMAP_SIZE + 1;
	y = MINIMAP_SIZE;
	while (y <= (height + (MINIMAP_SIZE * 2)))
	{
		x = width + MINIMAP_SIZE + 1;
		while (x <= (width + (MINIMAP_SIZE * 2)))
		{
			mlx_put_pixel(map->game->screen, x, y, 6771586);
			x++;
		}
		y++;
	}
	x = 0;
	y = height + 1;
	while (y <= (height + (MINIMAP_SIZE * 2)))
	{
		x = 0;
		while (x <= (width + (MINIMAP_SIZE * 2)))
		{
			mlx_put_pixel(map->game->screen, x, y, 6771586);
			x++;
		}
		y++;
	}
}



/**
 * @brief Minimap. First draw a border, then draw the map.
 * border MINIMAP_SIZE is 64 of weight and (64 * map->widht or height) of height
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
	y = MINIMAP_SIZE + 1;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		x = MINIMAP_SIZE + 1;
		while (j < map->width)
		{
			if (map->grid[i][j] == 1)
				draw_cube(map->game->screen, (t_vec2){x , y}, get_rgba(120, 80, 120, 255));
			else if (map->grid[i][j] == 0)
				draw_cube(map->game->screen, (t_vec2){x , y}, get_rgba(55, 55, 55, 255));
			else if (map->grid[i][j] == -1)
				draw_cube(map->game->screen, (t_vec2){x , y}, get_rgba(20, 20, 20, 150));
			j++;
			x = x + MINIMAP_SIZE;
		}
		y = y + MINIMAP_SIZE;
		i++;
	}
}
