/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:53:24 by iostancu          #+#    #+#             */
/*   Updated: 2024/11/06 22:50:46 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	rotate_vision(t_player *p, int key);
void	player_controller(mlx_t *mlx, t_player *p);
/**
 * @brief Player control and ray casting. For every ray, distance where the ray
 * hit is saved and used to draw a wall line, after obteining its height.
 * 
 * wall_height = (size * height) / ray_lenght
 * RAY_ANGLE -> where the first ray starts (looking_angle - (FOV/2))
 * 
 * @param param 
 */
void do_raycast(void* param)
{
	t_player	*p;
	double		ray_angle;
	float		dist;
	int			i;
	int			j;
	int			wall_start;
	int			wall_end;
	int			wall_line_height;
	uint32_t	color;
	// char		*str;
	// char		*str2;

	p = (t_player *)param;
	i = -1;
	player_controller(p->map->game->mlx, p);
	draw_background(p->map->game->screen);
	draw_2d_map(p->map);
	color = get_rgba(1, 1, 1, 255);
	ray_angle = p->looking_angle - (p->fov / 2);	// first ray angle
	while (++i < p->width_win)
	{
		dist = trace_ray(p->position, ray_angle, p->map, p);	// trace ray, save distance
		if (dist > 0)	// if ray hit something (wall)
		{
			wall_line_height = (int)(p->height_win / dist);	// get wall height at current point
			wall_start = (p->height_win / 2) - (wall_line_height / 2);
			if (wall_start < 0)
				wall_start = 0;
			wall_end = (p->height_win / 2) + (wall_line_height / 2);
			if (wall_end >= p->height_win)
				wall_end = p->height_win - 1;
			color = get_distance_color(dist);
			j = wall_start;
			while (j < wall_end)
			{
				mlx_put_pixel(p->map->game->screen, i, j, color);	//draw wall line
				j++;
			}
		}
		ray_angle += p->ray_angle;	// next angle
	}
	// str2 = ft_itoa(abs(p->looking_angle));
	// str = ft_strjoin("Looking angle: ", str2);
	// draw_menu_box(p->map->game->screen, (t_vec2){200, 50}, (t_vec2){WIDTH_WIN - 320, p->height_win - 210});
	// mlx_put_string(p->map->game->mlx, str, WIDTH_WIN - 300, p->height_win - 200);
	// draw_menu_box(p->map->game->screen, (t_vec2){200, 50}, (t_vec2){WIDTH_WIN - 320, p->height_win - 210});	
	// free(str);
	// free(str2);
	draw_player(p);
}

void do_v_raycast(void* param)
{
	t_player	*p;
	t_vec2	ray_dir;
	double		ray_angle;
	float		dist;
	int			i;
	int			j;
	int			wall_start;
	int			wall_end;
	int			wall_line_height;
	uint32_t	color;
	// char		*str;
	// char		*str2;
	float cameraX;
	int		mapX;
	int		mapY;
	float	side_distX;
	float	side_distY;
	float	delta_distX;
	float	delta_distY;
	float	wall_dist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		line_height;
	int		start;
	int		end;

	p = (t_player *)param;
	i = -1;
	player_controller(p->map->game->mlx, p);
	draw_background(p->map->game->screen);
	draw_2d_map(p->map);
	color = get_rgba(1, 1, 1, 255);
	ray_angle = p->looking_angle - (p->fov / 2);	// first ray angle
	while (++i < p->height_win)
	{
		cameraX = 2 * i / (float)p->height_win - 1;
		ray_dir.x = p->rotation.x + p->rotation.y * cameraX;
		ray_dir.y = p->rotation.y + p->rotation.x * cameraX; // -

		mapX = (int)p->position.x;
		mapY = (int)p->position.y;

		delta_distX = fabs(1 / ray_dir.x);
		delta_distY = fabs(1 / ray_dir.y);
		
		if (ray_dir.x < 0)
		{
			stepX = -1;
			side_distX = (p->position.x - mapX) * delta_distX;
		}
		else
		{
			stepX = 1;
			side_distX = (mapX + 1.0 - p->position.x) * delta_distX;
		}
		if (ray_dir.y < 0)
		{
			stepY = -1;
			side_distY = (p->position.y - mapY) * delta_distY;
		}
		else
		{
			stepY = 1;
			side_distY = (mapY + 1.0 - p->position.y) * delta_distY;
		}
		while (hit == 0)
		{
			if (side_distX < side_distY)
			{
				side_distX += delta_distX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				side_distY += delta_distY;
				mapY += stepY;
				side = 1;
			}
			if (p->map->grid[mapY][mapX] > 0)
			{
				hit = 1;
			}
		}
		if (side == 0)
			wall_dist = (mapX - p->position.x + (1 - stepX) / 2) / ray_dir.x;
		else
			wall_dist = (mapY - p->position.y + (1 - stepY) / 2) / ray_dir.y;
		line_height = (int)(p->height_win / wall_dist);
		start = -line_height / 2 + p->height_win / 2;
		if (start < 0)
			start = 0;
		end = line_height / 2 + p->height_win / 2;
		if (end >= p->height_win)
			end = p->height_win - 1;
		printf("dist: %f\n", wall_dist);
		color = get_distance_color(wall_dist);
		j = start;
		while (j < end)
		{
			mlx_put_pixel(p->map->game->screen, i, j, color);	//draw wall line
			j++;
		}
	}
	// str2 = ft_itoa(abs(p->looking_angle));
	// str = ft_strjoin("Looking angle: ", str2);
	// draw_menu_box(p->map->game->screen, (t_vec2){200, 50}, (t_vec2){WIDTH_WIN - 320, p->height_win - 210});
	// mlx_put_string(p->map->game->mlx, str, WIDTH_WIN - 300, p->height_win - 200);
	// draw_menu_box(p->map->game->screen, (t_vec2){200, 50}, (t_vec2){WIDTH_WIN - 320, p->height_win - 210});	
	// free(str);
	// free(str2);
	draw_player(p);
}


