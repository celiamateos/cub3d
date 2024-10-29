/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:08:21 by iostancu          #+#    #+#             */
/*   Updated: 2024/10/29 23:28:29 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_menu_box(mlx_image_t *s, t_vec2 size, t_vec2 start);
int trace_ray(t_vec2 pos, double look_angle, double r_angle, t_map *map);

double	set_360_rotation(double angle)
{
	if (angle > 359.00)
		angle -= 360.00;
	else if (angle < 0.00)
		angle += 360.00;
	return (angle);
}

void	set_rotation(t_vec2 *rot, double look_angle)
{
	rot->x = cos(look_angle * (PI_ / 180));
	rot->y = -sin(look_angle * (PI_ / 180));
}

void	rotate_vision(t_player *p, keys_t key)
{
	if (key == MLX_KEY_RIGHT)
		p->looking_angle -= ROTATION_ANGLE;
	else
		p->looking_angle += ROTATION_ANGLE;
	p->looking_angle = set_360_rotation(p->looking_angle);
	set_rotation(&p->rotation, p->looking_angle);
}

/**
 * @brief wall_height = (size * height) / ray_lenght
 * 
 * @param param 
 */
void player_move_minimap(void* param)
{
	t_player	*p;
	t_vec2		nxt_pos;
	double		ray_angle;
	double		angle_dist;
	double 		dist;
	int			i;
	int			j;
	int		w_start;
	int		w_end;
	int		w_line_height;
	uint32_t	color;
	// char		*str;
	// char		*str2;

	p = (t_player *)param;
	i = -1;
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(p->map->game->mlx);
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_UP) || mlx_is_key_down(p->map->game->mlx, MLX_KEY_W))
	{
		nxt_pos.x = p->position.x + (p->rotation.x * 0.1f);
        nxt_pos.y = p->position.y + (p->rotation.y * 0.1f);
		if (!is_wall(p->map, nxt_pos))
			p->position = nxt_pos;
	}
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_D)) // move to right
	{
		nxt_pos.x = p->position.x - (p->rotation.y * 0.1f);
		nxt_pos.y = p->position.y + (p->rotation.x * 0.1f);
		if (!is_wall(p->map, nxt_pos))
			p->position = nxt_pos;
	}
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_DOWN) || mlx_is_key_down(p->map->game->mlx, MLX_KEY_S))
	{
		nxt_pos.x = p->position.x - (p->rotation.x * 0.1f);
        nxt_pos.y = p->position.y - (p->rotation.y * 0.1f);
		if (!is_wall(p->map, nxt_pos))
			p->position = nxt_pos;
	}
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_A)) // move to left
	{
		nxt_pos.x = p->position.x + (p->rotation.y * 0.1f);
		nxt_pos.y = p->position.y - (p->rotation.x * 0.1f);
		if (!is_wall(p->map, nxt_pos))
			p->position = nxt_pos;
	}
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_LEFT))
		rotate_vision(p, MLX_KEY_LEFT);
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_RIGHT))
		rotate_vision(p, MLX_KEY_RIGHT);
	draw_background(p->map->game->screen);
	draw_2d_map(p->map);
	angle_dist = 60 / WIDTH_WIN;
	ray_angle = p->looking_angle - (FOV / 2);
	printf("ray_angle: %f\n", ray_angle);
	// check --> wall_height = (size * height) / ray_lenght
	int k = 0;
	color = get_rgba(1, 1, 1, 255);
	while (++i < WIDTH_WIN)
	{
		dist = trace_ray(p->position, p->looking_angle, ray_angle, p->map);
		if (dist > 0)
		{
			w_line_height = (int)(HEIGHT_WIN / dist);
			printf("w_line_height: %i\n", w_line_height);
			
			w_start = (HEIGHT_WIN / 2) - (w_line_height / 2);
			if (w_start < 0) w_start = 0;
			w_end = (HEIGHT_WIN / 2) + (w_line_height / 2);
			if (w_end >= HEIGHT_WIN) w_end = HEIGHT_WIN - 1;
			//color = get_distance_color(dist);
			j = w_start;
			while (j < w_end)
			{
				mlx_put_pixel(p->map->game->screen, i, j, color);
				j++;
			}
		}
		// while (++k < 200)
		// {
		// 	trace_ray(p->position, p->looking_angle, ray_angle, p->map);
		// 	ray_angle += angle_dist;
		// }
		trace_ray(p->position, p->looking_angle, ray_angle, p->map);
		ray_angle += p->raycast_angle;
		printf("ray_angle: %f\n", p->raycast_angle);
	}
	
	// str2 = ft_itoa(abs(p->looking_angle));
	// str = ft_strjoin("Looking angle: ", str2);
	// draw_menu_box(p->map->game->screen, (t_vec2){200, 50}, (t_vec2){WIDTH_WIN - 320, HEIGHT_WIN - 210});
	// mlx_put_string(p->map->game->mlx, str, WIDTH_WIN - 300, HEIGHT_WIN - 200);
	// draw_menu_box(p->map->game->screen, (t_vec2){200, 50}, (t_vec2){WIDTH_WIN - 320, HEIGHT_WIN - 210});	
	// free(str);
	// free(str2);
	//trace_ray(p->position, p->looking_angle, p->raycast, p->map);
	printf("Looking angle: %i\n", (int)p->looking_angle);
	printf("angle_dist: %f\n", angle_dist);
	
	draw_player(p);
}
