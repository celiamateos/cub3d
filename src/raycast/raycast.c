/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:53:24 by iostancu          #+#    #+#             */
/*   Updated: 2024/11/06 02:56:30 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	rotate_vision(t_player *p, int key);

/**
 * @brief wall_height = (size * height) / ray_lenght
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
	int		w_start;
	int		w_end;
	int		w_line_height;
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
		nxt_pos.x = p->position.x + (p->rotation.x * 0.05f);
        nxt_pos.y = p->position.y + (p->rotation.y * 0.05f);
		if (!is_wall(p->map, nxt_pos))
			p->position = nxt_pos;
	}
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_D)) // move to right
	{
		nxt_pos.x = p->position.x - (p->rotation.y * 0.05f);
		nxt_pos.y = p->position.y + (p->rotation.x * 0.05f);
		if (!is_wall(p->map, nxt_pos))
			p->position = nxt_pos;
	}
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_DOWN) || mlx_is_key_down(p->map->game->mlx, MLX_KEY_S))
	{
		nxt_pos.x = p->position.x - (p->rotation.x * 0.05f);
        nxt_pos.y = p->position.y - (p->rotation.y * 0.05f);
		if (!is_wall(p->map, nxt_pos))
			p->position = nxt_pos;
	}
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_A)) // move to left
	{
		nxt_pos.x = p->position.x + (p->rotation.y * 0.05f);
		nxt_pos.y = p->position.y - (p->rotation.x * 0.05f);
		if (!is_wall(p->map, nxt_pos))
			p->position = nxt_pos;
	}
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_LEFT))
		rotate_vision(p, MLX_KEY_LEFT);
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_RIGHT))
		rotate_vision(p, MLX_KEY_RIGHT);
	draw_background(p->map->game->screen);
	draw_2d_map(p->map);
	// check --> wall_height = (size * height) / ray_lenght
	int k = 0;
	color = get_rgba(1, 1, 1, 255);
    ray_angle = p->looking_angle - (FOV / 2);
	printf("raycast_angle: %f\n", p->raycast_angle);
	while (++i < WIDTH_WIN)
	{
		dist = trace_ray(p->position, ray_angle, p->map, p);
		if (dist > 0)
		{
			w_line_height = (int)(HEIGHT_WIN / dist);
			w_start = (HEIGHT_WIN / 2) - (w_line_height / 2);
			if (w_start < 0) w_start = 0;
			w_end = (HEIGHT_WIN / 2) + (w_line_height / 2);
			if (w_end >= HEIGHT_WIN) w_end = HEIGHT_WIN - 1;
			color = get_distance_color(dist);
			j = w_start;
			while (j < w_end)
			{
				mlx_put_pixel(p->map->game->screen, i, j, color);
				j++;
			}
		}
		
		ray_angle += p->raycast_angle;
		//trace_ray(p->position, ray_angle, p->map);
		// // ray_angle += 0.02727f;
		// printf("ray_angle: %f\n", ray_angle);
	}
 	
	// str2 = ft_itoa(abs(p->looking_angle));
	// str = ft_strjoin("Looking angle: ", str2);
	// draw_menu_box(p->map->game->screen, (t_vec2){200, 50}, (t_vec2){WIDTH_WIN - 320, HEIGHT_WIN - 210});
	// mlx_put_string(p->map->game->mlx, str, WIDTH_WIN - 300, HEIGHT_WIN - 200);
	// draw_menu_box(p->map->game->screen, (t_vec2){200, 50}, (t_vec2){WIDTH_WIN - 320, HEIGHT_WIN - 210});	
	// free(str);
	// free(str2);
	//trace_ray(p->position, p->looking_angle, p->raycast, p->map);
	
	draw_player(p);
}

