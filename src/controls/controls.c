/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:08:21 by iostancu          #+#    #+#             */
/*   Updated: 2024/11/03 21:04:53 by settes           ###   ########.fr       */
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

void	rotate_vision(t_player *p, int key)
{
	if (key == MLX_KEY_RIGHT)
		p->looking_angle -= ROTATION_ANGLE;
	else
		p->looking_angle += ROTATION_ANGLE;
	p->looking_angle = set_360_rotation(p->looking_angle);
	printf("Rotating!\n");
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

