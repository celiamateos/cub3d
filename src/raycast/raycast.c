/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:53:24 by iostancu          #+#    #+#             */
/*   Updated: 2024/11/06 18:56:47 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	rotate_vision(t_player *p, int key);

/**
 * @brief Player control and ray casting. For every ray, distance where the ray hit is saved
 * and used to draw 
 * 
 * wall_height = (size * height) / ray_lenght
 * RAY_ANGLE -> where the first ray starts (looking_angle - (FOV/2))
 * 
 * @param param 
 */
void do_raycast(void* param)
{
	t_player	*p;
	double		angle_dist;
    double        ray_angle;
	float		dist;
	int			i;
	int			j;
	int		wall_start;
	int		wall_end;
	int		wall_line_height;
	uint32_t	color;
	t_vec2		nxt_pos;
	// char		*str;
	// char		*str2;

	p = (t_player *)param;
	i = -1;
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(p->map->game->mlx);
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_UP) || mlx_is_key_down(p->map->game->mlx, MLX_KEY_W))
	{
		nxt_pos.x = p->position.x + (p->rotation.x * p->speed);
        nxt_pos.y = p->position.y + (p->rotation.y * p->speed);
		if (!is_wall(p->map, nxt_pos))
			p->position = nxt_pos;
	}
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_D)) // move to right
	{
		nxt_pos.x = p->position.x - (p->rotation.y * p->speed);
		nxt_pos.y = p->position.y + (p->rotation.x * p->speed);
		if (!is_wall(p->map, nxt_pos))
			p->position = nxt_pos;
	}
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_DOWN) || mlx_is_key_down(p->map->game->mlx, MLX_KEY_S))
	{
		nxt_pos.x = p->position.x - (p->rotation.x * p->speed);
        nxt_pos.y = p->position.y - (p->rotation.y * p->speed);
		if (!is_wall(p->map, nxt_pos))
			p->position = nxt_pos;
	}
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_A)) // move to left
	{
		nxt_pos.x = p->position.x + (p->rotation.y * p->speed);
		nxt_pos.y = p->position.y - (p->rotation.x * p->speed);
		if (!is_wall(p->map, nxt_pos))
			p->position = nxt_pos;
	}
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_LEFT))
		rotate_vision(p, MLX_KEY_LEFT);
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_RIGHT))
		rotate_vision(p, MLX_KEY_RIGHT);
	draw_background(p->map->game->screen);
	draw_2d_map(p->map);
	int k = 0;
	color = get_rgba(1, 1, 1, 255);
    ray_angle = p->looking_angle - (p->fov / 2);
	printf("raycast_angle: %f\n", p->ray_angle);
	while (++i < p->width_win)
	{
		dist = trace_ray(p->position, ray_angle, p->map, p);
		if (dist > 0)
		{
			wall_line_height = (int)(p->height_win / dist);
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
				mlx_put_pixel(p->map->game->screen, i, j, color);
				j++;
			}
		}
		
		ray_angle += p->ray_angle;
	}
 	
	// str2 = ft_itoa(abs(p->looking_angle));
	// str = ft_strjoin("Looking angle: ", str2);
	// draw_menu_box(p->map->game->screen, (t_vec2){200, 50}, (t_vec2){WIDTH_WIN - 320, p->height_win - 210});
	// mlx_put_string(p->map->game->mlx, str, WIDTH_WIN - 300, p->height_win - 200);
	// draw_menu_box(p->map->game->screen, (t_vec2){200, 50}, (t_vec2){WIDTH_WIN - 320, p->height_win - 210});	
	// free(str);
	// free(str2);
	//trace_ray(p->position, p->looking_angle, p->raycast, p->map);
	
	draw_player(p);
}

