/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:54:08 by iostancu          #+#    #+#             */
/*   Updated: 2024/11/06 02:55:27 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_vec2	get_ray_direction(double angle);
t_vec2	get_scaled_pos(t_vec2 pos);

int	get_rgba(int r, int g, int b, int a);

/**
 * @brief 
 * 
 * @param pos 
 * @param look_angle 
 * @param r_angle 
 * @param r 
 * @param map 
 * @return Distance to the first wall
 */
float trace_ray(t_vec2 pos, double angle, t_map *map, t_player *p)
{
	t_vec2	ray_dir;
	t_vec2	ray_pos;
	t_vec2	delta_dist;
	t_vec2	side_dist;
	t_vec2	step;
	int		map_x;
	int		map_y;
	int		hit;
	int		side;
	t_vec2	start;
	t_vec2	end;

	ray_dir = get_ray_direction(angle);
	ray_pos = pos;
	map_x = (int)pos.x;
	map_y = (int)pos.y;
	delta_dist.x = fabs(1 / ray_dir.x);
	delta_dist.y = fabs(1 / ray_dir.y);
	hit = 0;
	if (ray_dir.x < 0)
	{
		step.x = -1;
		side_dist.x = (pos.x - map_x) * delta_dist.x;
	}
	else
	{
		step.x = 1;
		side_dist.x = (map_x + 1.0 - pos.x) * delta_dist.x;
	}
	if (ray_dir.y < 0)
	{
		step.y = -1;
		side_dist.y = (pos.y - map_y) * delta_dist.y;
	}
	else
	{
		step.y = 1;
		side_dist.y = (map_y + 1.0 - pos.y) * delta_dist.y;
	}
	while (hit == 0)
	{
		// next cell
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			map_x += step.x;
			side = 0;
		}
		else
		{
			side_dist.y += delta_dist.y;
			map_y += step.y; side = 1;
		}
		if (map->grid[map_y][map_x] > 0)
		{
			hit = 1;
			start = get_scaled_pos(pos);
			end = get_scaled_pos(ray_pos);
			draw_line(start, end, map->game->screen, 0x999988);
			//printf("is wall! [%d][%d]\n", map_x, map_y);
		}
	}
	if (side == 0)
		return (side_dist.x - delta_dist.x);
	else
		return (side_dist.y - delta_dist.y);
}
// int trace_ray(t_vec2 pos, double angle, t_map *map, t_player *p)
// {
//     t_vec2  ray_dir = get_ray_direction(angle);
//     t_vec2  ray_pos = pos;
//     float   step_size = (float)p->raycast_angle;
//     int     max_steps = 200;
//     int     i;
//     int map_x;
//     int map_y;
//     t_vec2  start;
//     t_vec2  end;

//     i = -1;
//     while (++i < max_steps)
//     {
//         // ray_pos.x += ray_dir.x * PROJECTION_DISTANCE;
//         // ray_pos.y += ray_dir.y * PROJECTION_DISTANCE;

//         ray_pos.x += ray_dir.x * step_size;
//         ray_pos.y += ray_dir.y * step_size;

//         map_x = (int)ray_pos.x;
//         map_y = (int)ray_pos.y;

//         if (map_x < 0 || map_y < 0 || map_x >= map->width || map_y >= map->height)
//             return (-1);
//         if (map->grid[map_y][map_x] != 0)
//         {
//             // printf("Ray hit wall [%d][%d]\n", map_x, map_y);
//             // minimap
//             start = get_scaled_pos(pos);
//             end = get_scaled_pos(ray_pos);
//             draw_line(start, end, map->game->screen, get_rgba(255, 25, 190, 180));
//             return (sqrt((ray_pos.x - pos.x) * (ray_pos.x - pos.x) + (ray_pos.y - pos.y) * (ray_pos.y - pos.y)));
            
//             //return (1);
//         }
//     }
//     start = get_scaled_pos(pos);
//     end = get_scaled_pos(ray_pos);
//     draw_line(start, end, map->game->screen, 0xFFFF88);
//     return (-1);
// }

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
	t_vec2  delta;
	t_vec2  px;
	int  pixels;
	int  i;

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
 * @brief Scales player position to the minimap size. 
 * (Adds + MINIMAP_SIZE because border of minimap)
 * 
 * @param pos player position
 * @return t_vec2 scaled position
 */
t_vec2 get_scaled_pos(t_vec2 pos)
{
	t_vec2  scaled;

	scaled.x = pos.x * MINIMAP_SIZE + MINIMAP_SIZE;
	scaled.y = pos.y * MINIMAP_SIZE + MINIMAP_SIZE;
	return (scaled);
}
