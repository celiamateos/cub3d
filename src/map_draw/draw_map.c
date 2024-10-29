/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:11:22 by iostancu          #+#    #+#             */
/*   Updated: 2024/10/29 21:22:13 by iostancu         ###   ########.fr       */
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
// void	draw_border_map(t_map *map)
// {
// 	int x;
// 	int y;
// 	int height;
// 	int width;

// 	y = 0;
// 	height = map->height * (MINIMAP_SIZE);
// 	width = map->width * (MINIMAP_SIZE);
// 	while (y <= MINIMAP_SIZE)
// 	{
// 		x = 0;
// 		while (x <= width + (MINIMAP_SIZE * 2))
// 		{
// 			mlx_put_pixel(map->game->screen, x, y, 6771586);
// 			x++;
// 		}
// 		y++;
// 	}
// 	y = MINIMAP_SIZE;
// 	while (y <= (height + (MINIMAP_SIZE * 2)))
// 	{
// 		x = 0;
// 		while (x <= MINIMAP_SIZE)
// 		{
// 			mlx_put_pixel(map->game->screen, x, y, 6771586);
// 			x++;
// 		}
// 		y++;
// 	}
// 	x = width + MINIMAP_SIZE + 1;
// 	y = MINIMAP_SIZE;
// 	while (y <= (height + (MINIMAP_SIZE * 2)))
// 	{
// 		x = width + MINIMAP_SIZE + 1;
// 		while (x <= (width + (MINIMAP_SIZE * 2)))
// 		{
// 			mlx_put_pixel(map->game->screen, x, y, 6771586);
// 			x++;
// 		}
// 		y++;
// 	}
// 	x = 0;
// 	y = height + 1;
// 	while (y <= (height + (MINIMAP_SIZE * 2)))
// 	{
// 		x = 0;
// 		while (x <= (width + (MINIMAP_SIZE * 2)))
// 		{
// 			mlx_put_pixel(map->game->screen, x, y, 6771586);
// 			x++;
// 		}
// 		y++;
// 	}
// }

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
 * @brief 
 * 
 * @param s screen
 * @param size box size
 * @param start start position
 */
void	draw_menu_box(mlx_image_t *s, t_vec2 size, t_vec2 start)
{
	int	x;
	int	y;
	int	size_y;
	int	size_x;

	y = start.y;
	size_y = start.y + size.y;
	size_x = start.x + size.x;
	while (y < size_y)
	{
		x = start.x;
		while (x < size_x)
		{
			mlx_put_pixel(s, x, y, 0x99002200);
			x++;
		}
		y++;
	}
}

void	print_img(mlx_image_t *screen)
{
	int	x;
	int	y;

	y = 0;
	while (y < screen->height)
	{
		x = 0;
		while (x < screen->width)
		{
			mlx_put_pixel(screen, x, y, get_rgba(55, 55, 55, 255));
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
	//print_img(map->game->screen);
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

void draw_background(mlx_image_t *screen)
{
    int	x;
	int	y;
	int	h;

	y = -1;
	h = HEIGHT_WIN / 2;
   while (++y < h)
    {
		x = -1;
       while (++x < WIDTH_WIN)
            mlx_put_pixel(screen, x, y, 0x87CEEBFF);
    }
   y = h - 1;
   while (++y < HEIGHT_WIN)
    {
		x = -1;
		while (++x < WIDTH_WIN)
            mlx_put_pixel(screen, x, y, 0x8B4513FF);
    }
}

uint32_t	get_distance_color(float distance)
{
    int shade;
	
	shade = (int)(255 / (1 + distance * distance * 0.1));
    return (shade << 16) | (shade << 8) | shade;
}
