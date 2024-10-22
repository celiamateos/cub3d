/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:08:21 by iostancu          #+#    #+#             */
/*   Updated: 2024/10/22 22:43:54 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

double	set_360_rotation(double angle)
{
	if (angle > 359.00)
		angle -= 360.00;
	else if (angle < 0.00)
		angle += 360.00;
	return (angle);
}

void	rotate_vision(t_player *p, keys_t key)
{
	if (key == MLX_KEY_RIGHT)
	{
		p->looking_angle += ROTATION_ANGLE;
		p->looking_angle = set_360_rotation(p->looking_angle);
	}
	else if (key == MLX_KEY_LEFT)
	{
		p->looking_angle -= ROTATION_ANGLE;
		p->looking_angle = set_360_rotation(p->looking_angle);
	}
}

void player_move_minimap(void* param)
{
	t_player	*p;

	p = (t_player *)param;

	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(p->map->game->mlx);
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_UP))
	{
		p->position.y -= 0.1f;
		p->looking_angle = 90;
	}
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_DOWN))
	{
		p->position.y += 0.1f;
		p->looking_angle = 270;
	}
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_LEFT))
	{
		// p->position.x -= 0.1f;
		// p->looking_angle = 180;
		rotate_vision(p, MLX_KEY_LEFT);
	}
	if (mlx_is_key_down(p->map->game->mlx, MLX_KEY_RIGHT))
	{
		// p->position.x += 0.1f;
		// p->looking_angle = 360;
		rotate_vision(p, MLX_KEY_RIGHT);
	}
	draw_player(p);
}
