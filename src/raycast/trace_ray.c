/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:54:08 by iostancu          #+#    #+#             */
/*   Updated: 2024/11/23 04:24:18 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_vec2	get_ray_direction(double angle);
t_vec2	get_scaled_pos(t_vec2 pos);

/**
 * @brief Makes the ray tracing from the player to the given distance.
 * 
 * @param pos 
 * @param angle 
 * @param map 
 * @param p 
 * @return int 
 */
int trace_ray(t_vec2 pos, double angle, t_map *map, t_player *p)
{
	t_vec2	ray_dir;
	t_vec2	ray_pos;
	double	step_size;
	int		max_len;	// max length for each ray
	int		i;
	int		map_x;
	int		map_y;
	t_vec2	start;
	t_vec2	end;

	ray_dir = get_ray_direction(angle);
	ray_pos = pos;
	step_size = p->ray_angle;
	i = -1;
	max_len = 300;
	while (++i < max_len)
	{
		// ray_pos.x += ray_dir.x * PROJECTION_DISTANCE;
		// ray_pos.y += ray_dir.y * PROJECTION_DISTANCE;
		ray_pos.x += ray_dir.x * step_size;
		ray_pos.y += ray_dir.y * step_size;
		map_x = (int)ray_pos.x;
		map_y = (int)ray_pos.y;
		if (map_x < 0 || map_y < 0 || map_x >= map->width || map_y >= map->height)
			return (-1);
		if (map->grid[map_y][map_x] != 0)
		{
			// minimap visualized raycasting, when finish it will be removed
			start = get_scaled_pos(pos);
			end = get_scaled_pos(ray_pos);
			draw_line(start, end, map->game->screen, get_rgba(10, 10, 10, 150));
			// printf("player pos[%f, %f] ray pos[%f, %f]: dist: %f\n", pos.x, pos.y, ray_pos.x, ray_pos.y, sqrt((ray_pos.x - pos.x) * (ray_pos.x - pos.x) + (ray_pos.y - pos.y) * (ray_pos.y - pos.y)));
			return (sqrt((ray_pos.x - pos.x) * (ray_pos.x - pos.x) + (ray_pos.y - pos.y) * (ray_pos.y - pos.y)));
			//return(map_x - pos.x + (1 - ));
			//return (1);
		}
	}
	start = get_scaled_pos(pos);
	end = get_scaled_pos(ray_pos);
	draw_line(start, end, map->game->screen, get_rgba(200, 10, 10, 150)); // rays in different color when they didnt hit any wall
	return (-1);
}

/**
 * @brief Same as set_rotation. Delete one of them
 * 
 * @param angle 
 * @return t_vec2 
 */
t_vec2 get_ray_direction(double angle)
{
	t_vec2  direction;

	direction.x = cos(angle * PI_ / 180.0);
	direction.y = -sin(angle * PI_ / 180.0);
	return (direction);
}

/**
 * @brief Obtains the magnitude(distance) between player and wall using the
 * pythagorean rule (distance formula), and draws it.
 * 
 * @param start player position
 * @param end wall position
 * @param img 
 * @param color 
 */
void draw_line(t_vec2 start, t_vec2 end, mlx_image_t *img, uint32_t color)
{
	t_vec2	delta;
	t_vec2	px;
	int		pixels;
	int		i;

	i = -1;
	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	px.x = start.x;
	px.y = start.y;
	pixels = sqrt((delta.x * delta.x) + (delta.y * delta.y));
	while (++i < pixels)
	{
		mlx_put_pixel(img, px.x, px.y, color);
		px.x += delta.x / pixels;
		px.y += delta.y / pixels;
	}
}

/**
 * @brief Scales given coord to the minimap size.
 * (Adds + MINIMAP_SIZE because border of minimap)
 * 
 * @param pos position
 * @return t_vec2 scaled position
 */
t_vec2	get_scaled_pos(t_vec2 pos)
{
	t_vec2	scaled;

	scaled.x = pos.x * MINIMAP_SIZE + MINIMAP_SIZE;
	scaled.y = pos.y * MINIMAP_SIZE + MINIMAP_SIZE;
	return (scaled);
}
