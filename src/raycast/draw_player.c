/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:02:46 by iostancu          #+#    #+#             */
/*   Updated: 2024/10/24 22:48:55 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
	rayY = ((pY / 64) * 64) + (Y.line - pY);
	rayX = (pY - rayY) / -tan(looking angle) + pX;
*/
void	draw_my_first_ray(t_player *player)
{
	t_vec2	ray;
	t_vec2	pos;
	int		color;

	ray.y = ((player->position.y / SIZE) * SIZE) + (/* grid.line.y */ - player->position.y);
	ray.x = (player->position.y - ray.y) / -tan(player->looking_angle) + player->position.x;
	pos.x = ray.x * SIZE + SIZE;
	pos.y = ray.y * SIZE + SIZE;
}

void	draw_player(void *param)
{
	t_player	*p;
	t_vec2		pos;
	int			color;

	p = (t_player *)param;
	pos.x = p->position.x * SIZE + SIZE;
	pos.y = p->position.y * SIZE + SIZE;
	color = get_rgba(255, 0, 0, 255);
	draw_cube(p->map->game->screen, pos, color);
}
