/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:08:21 by iostancu          #+#    #+#             */
/*   Updated: 2024/10/28 00:55:26 by settes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_menu_box(mlx_image_t *s, t_vec2 size, t_vec2 start);
int trace_ray(t_vec2 pos, double look_angle, t_raycast *r, t_map *map);

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
	rot->y = sin(look_angle * (PI_ / 180));
}

void	rotate_vision(t_player *p, keys_t key)
{
	if (key == MLX_KEY_RIGHT)
		p->looking_angle += ROTATION_ANGLE;
	else
		p->looking_angle -= ROTATION_ANGLE;
	p->looking_angle = set_360_rotation(p->looking_angle);
	set_rotation(&p->rotation, p->looking_angle);
}

void player_move_minimap(void* param)
{
	t_player	*p;
	// char		*str;
	// char		*str2;

	p = (t_player *)param;

	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(p->map->game->mlx);
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_UP))
	{
		p->position.x -= p->rotation.x * 0.1f;
        p->position.y -= p->rotation.y * 0.1f;
	}
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_DOWN))
	{
		p->position.x += p->rotation.x * 0.1f;
        p->position.y += p->rotation.y * 0.1f;
	}
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_LEFT))
		rotate_vision(p, MLX_KEY_LEFT);
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_RIGHT))
		rotate_vision(p, MLX_KEY_RIGHT);
	// str2 = ft_itoa(abs(p->looking_angle));
	// str = ft_strjoin("Looking angle: ", str2);
	// draw_menu_box(p->map->game->screen, (t_vec2){200, 50}, (t_vec2){WIDTH_WIN - 320, HEIGHT_WIN - 210});
	// mlx_put_string(p->map->game->mlx, str, WIDTH_WIN - 300, HEIGHT_WIN - 200);
	// draw_menu_box(p->map->game->screen, (t_vec2){200, 50}, (t_vec2){WIDTH_WIN - 320, HEIGHT_WIN - 210});	
	// free(str);
	// free(str2);
	trace_ray(p->position, p->looking_angle, p->raycast, p->map);
	printf("Looking angle: %i\n", (int)p->looking_angle);
	draw_player(p);
}
