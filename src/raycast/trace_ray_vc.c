/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray_vc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:56:54 by iostancu          #+#    #+#             */
/*   Updated: 2024/11/06 19:57:01 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// /**
//  * @brief 
//  * 
//  * @param pos 
//  * @param look_angle 
//  * @param r_angle 
//  * @param r 
//  * @param map 
//  * @return Distance to the first wall
//  */
// float trace_ray(t_vec2 pos, double angle, t_map *map, t_player *p)
// {
// 	t_vec2	ray_dir;
// 	t_vec2	ray_pos;
// 	t_vec2	delta_dist;
// 	t_vec2	side_dist;
// 	t_vec2	step;
// 	int		map_x;
// 	int		map_y;
// 	int		hit;
// 	int		side;
// 	t_vec2	start;
// 	t_vec2	end;

// 	ray_dir = get_ray_direction(angle);
// 	ray_pos = pos;
// 	map_x = (int)pos.x;
// 	map_y = (int)pos.y;
// 	delta_dist.x = fabs(1 / ray_dir.x);
// 	delta_dist.y = fabs(1 / ray_dir.y);
// 	hit = 0;
// 	if (ray_dir.x < 0)
// 	{
// 		step.x = -1;
// 		side_dist.x = (pos.x - map_x) * delta_dist.x;
// 	}
// 	else
// 	{
// 		step.x = 1;
// 		side_dist.x = (map_x + 1.0 - pos.x) * delta_dist.x;
// 	}
// 	if (ray_dir.y < 0)
// 	{
// 		step.y = -1;
// 		side_dist.y = (pos.y - map_y) * delta_dist.y;
// 	}
// 	else
// 	{
// 		step.y = 1;
// 		side_dist.y = (map_y + 1.0 - pos.y) * delta_dist.y;
// 	}
// 	while (hit == 0)
// 	{
// 		// next cell
// 		if (side_dist.x < side_dist.y)
// 		{
// 			side_dist.x += delta_dist.x;
// 			map_x += step.x;
// 			side = 0;
// 		}
// 		else
// 		{
// 			side_dist.y += delta_dist.y;
// 			map_y += step.y; side = 1;
// 		}
// 		if (map->grid[map_y][map_x] > 0)
// 		{
// 			hit = 1;
// 			start = get_scaled_pos(pos);
// 			end = get_scaled_pos(ray_pos);
// 			draw_line(start, end, map->game->screen, 0x999988);
// 			//printf("is wall! [%d][%d]\n", map_x, map_y);
// 		}
// 	}
// 	if (side == 0)
// 		return (side_dist.x - delta_dist.x);
// 	else
// 		return (side_dist.y - delta_dist.y);
// }
