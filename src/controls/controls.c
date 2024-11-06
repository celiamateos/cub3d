/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:08:21 by iostancu          #+#    #+#             */
/*   Updated: 2024/11/06 20:07:07 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_menu_box(mlx_image_t *s, t_vec2 size, t_vec2 start);

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

void	rotate_vision(t_player *p, int key)
{
	if (key == MLX_KEY_RIGHT)
		p->looking_angle -= p->rotation_speed;
	else
		p->looking_angle += p->rotation_speed;
	p->looking_angle = set_360_rotation(p->looking_angle);
	set_rotation(&p->rotation, p->looking_angle);
}

void my_keyhook(mlx_key_data_t k, void *param)
{
	t_player	*p;
	t_vec2		nxt_pos;

	p = (t_player *)param;
	if (k.key == MLX_KEY_ESCAPE)
		mlx_close_window(p->map->game->mlx);
	if ((k.key == MLX_KEY_LEFT || k.key == MLX_KEY_RIGHT) && (k.action == MLX_PRESS || k.action == MLX_REPEAT))
		rotate_vision(p, k.key);
	if (k.key == MLX_KEY_UP || k.key == MLX_KEY_W)
	{
		nxt_pos.x = p->position.x + (p->rotation.x * 0.1f);
		nxt_pos.y = p->position.y + (p->rotation.y * 0.1f);
		if (!is_wall(p->map, nxt_pos))
			p->position = nxt_pos;
	}
	if (k.key == MLX_KEY_DOWN || k.key == MLX_KEY_S)
	{
		nxt_pos.x = p->position.x - (p->rotation.x * 0.1f);
		nxt_pos.y = p->position.y - (p->rotation.y * 0.1f);
		if (!is_wall(p->map, nxt_pos))
			p->position = nxt_pos;
	}
}

void	player_controller(mlx_t *mlx, t_player *p)
{
	t_vec2	nxt_pos;

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
}
